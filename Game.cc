// Game.cc

#include <iostream>
#include <utility>
#include <tuple>
#include <memory>
#include <cassert>
#include <sstream>
#include <regex>
#include <vector>
#include <algorithm>
#include <thread> 
#include <optional>


#include "Constants.h"
#include "Game.h"
#include "CommandRetriever.h"
#include "IllegalCommandReporter.h"

#include "ComputerPlayerFactory.h"
#include "ComputerPlayer.h"

#include "BoardMove.h"
#include "UserSquare.h"
#include "ChessBoard.h"

#include "ChessBoardImpl.h"
#include "ChessBoardFactory.h"
#include "ChessBoardUtilities.h"
#include "Player.h"


Game::Game(std::unique_ptr<CommandRetriever> commandRetriever, std::unique_ptr<IllegalCommandReporter> illegalCommandReporter) :
    gameState(GameState::MAIN_MENU),
    chessBoard(ChessBoardFactory::createChessBoard(8, 8)),
    commandRetriever(std::move(commandRetriever)), 
    illegalCommandReporter(std::move(illegalCommandReporter)),
    players(std::make_pair(
        Player(Team::TEAM_ONE, nullptr), 
        Player(Team::TEAM_TWO, nullptr)
    )),
    currentTurn(Team::TEAM_ONE) {
    ChessBoardUtilities::applyStandardSetup(chessBoard);
}

// Copy ctor
Game::Game(Game const &other) :
    gameState(other.gameState),
    chessBoard(other.chessBoard->clone()),
    commandRetriever(other.commandRetriever->clone()),
    illegalCommandReporter(other.illegalCommandReporter->clone()),
    players(other.players),
    currentTurn(other.currentTurn) {}

// Move ctor
Game::Game(Game &&other) noexcept :
    gameState(other.gameState),
    chessBoard(std::move(other.chessBoard)),
    commandRetriever(std::move(other.commandRetriever)),
    illegalCommandReporter(std::move(other.illegalCommandReporter)),
    players(std::move(other.players)),
    currentTurn(other.currentTurn) {}

// Copy ctor
Game& Game::operator=(Game &other) {
    if (this != &other) {
        gameState = other.gameState;
        chessBoard = other.chessBoard->clone();
        commandRetriever = other.commandRetriever->clone();
        illegalCommandReporter = other.illegalCommandReporter->clone();
        players = std::make_pair(
            Player(getPlayer(Team::TEAM_ONE)), 
            Player(getPlayer(Team::TEAM_TWO))
        ),
        currentTurn = other.currentTurn;
    }
    return *this;
}

// Move ctor
Game& Game::operator=(Game &&other) noexcept {
    if (this != &other) {
        gameState = other.gameState;
        chessBoard = std::move(other.chessBoard);
        commandRetriever = std::move(other.commandRetriever);
        illegalCommandReporter = std::move(other.illegalCommandReporter);
        players = std::move(other.players);
        currentTurn = other.currentTurn;
    }
    return *this;
}

void Game::switchTurn() {
    if (currentTurn == Team::TEAM_ONE) {
        currentTurn == Team::TEAM_TWO;
    } else {
        currentTurn == Team::TEAM_ONE;
    }
}

Player const& Game::getPlayer(Team team) const {
    if (team == Team::TEAM_ONE) {
        return players.first;
    } else {
        return players.second;
    }
}

void Game::resetGame() {
    setGameState(GameState::MAIN_MENU);
    currentTurn = Team::TEAM_ONE;
    chessBoard = ChessBoardFactory::createChessBoard(8, 8);
    ChessBoardUtilities::applyStandardSetup(chessBoard);
    players.first.setComputerPlayer(nullptr);
    players.second.setComputerPlayer(nullptr);
}

void Game::setGameState(GameState newGameState) {
    gameState = newGameState;
}

void Game::reportIllegalCommand(std::string const &message) const {
    illegalCommandReporter->reportIllegalCommand(message);
}

Game::State Game::getGameState() const {
    return std::tie(gameState, chessBoard, players, currentTurn);
}

void Game::runGame() {
    notifyObservers();

    while (commandRetriever->isCommandAvailable()) {
        std::string inputLine = commandRetriever->retrieveCommand();
        std::vector<std::string> tokens;

        std::smatch matches;
        if (std::regex_match(inputLine, matches, commandPatterns[CommandType::START_GAME])) {
            switch (gameState) {
                case GameState::GAME_ACTIVE:
                    reportIllegalCommand("Can't start a game when a game is already running");
                    break;
                case GameState::SETUP:
                    reportIllegalCommand("Can't start a game from within setup mode");
                    break;
                case GameState::MAIN_MENU:
                    players = std::make_pair(
                        Player(Team::TEAM_ONE, (matches[1] == "human") ? nullptr : ComputerPlayerFactory::createComputerPlayer(stringToComputerPlayerLevel(std::string(1, matches[1].str().back())), Team::TEAM_ONE)),
                        Player(Team::TEAM_TWO, (matches[2] == "human") ? nullptr : ComputerPlayerFactory::createComputerPlayer(stringToComputerPlayerLevel(std::string(1, matches[2].str().back())), Team::TEAM_TWO))

                    );
                    setGameState(GameState::GAME_ACTIVE);
                    notifyObservers();
                    break;  
            }

        } else if (std::regex_match(inputLine, matches, commandPatterns[CommandType::ENTER_SETUP_MODE])) {
            switch (gameState) {
                case GameState::GAME_ACTIVE:
                    reportIllegalCommand("Can't enter setup mode from within an active game");
                    break;
                case GameState::SETUP:
                    reportIllegalCommand("Already in setup mode");
                    break;
                case GameState::MAIN_MENU:
                    chessBoard->clearBoard();
                    setGameState(GameState::SETUP);
                    notifyObservers();
                    break;         
            }

        } else if (std::regex_match(inputLine, matches, commandPatterns[CommandType::MAKE_MOVE])) {
            switch (gameState) {
                case GameState::MAIN_MENU:
                    reportIllegalCommand("You're on the main menu page, cannot enter a move when game is not active");
                    break;
                case GameState::SETUP:
                    reportIllegalCommand("You're in setup mode, cannot enter a move when game is not active");
                    break;
                case GameState::GAME_ACTIVE:
                    if (matches[1].matched) {
                        if (getPlayer(currentTurn).getComputerPlayer() != nullptr) {
                            reportIllegalCommand("The current player is not a human, don't specify move details for computer player");
                            break;
                        }
                        
                        BoardSquare fromBoardSquare = createBoardSquare(UserSquare(matches[1].str()), chessBoard->getNumRows(), chessBoard->getNumCols());
                        BoardSquare toBoardSquare = createBoardSquare(UserSquare(matches[2].str()), chessBoard->getNumRows(), chessBoard->getNumCols());

                        std::string promotionPiece = matches[3].matched ? matches[3].str() : "";
                        if (!isValidPieceType(promotionPiece)) {
                            reportIllegalCommand("Invalid promotion piece");
                            break;
                        }
                        
                        std::optional<PieceType> promotion = promotionPiece == "" ? std::nullopt : std::make_optional(stringToPieceType(promotionPiece));
                        std::optional<std::unique_ptr<BoardMove>> boardMove = chessBoard->createBoardMove(fromBoardSquare, toBoardSquare, promotion);
                        if (!boardMove.has_value()) {
                            reportIllegalCommand("Invalid board move, try again ");
                            break;
                        }

                        chessBoard->makeMove(boardMove.value());
                        switchTurn();

                        notifyObservers();
                        if (ChessBoardUtilities::isGameOver(chessBoard)) {
                            resetGame();
                            notifyObservers();
                        }
                    } else {
                        if (getPlayer(currentTurn).getComputerPlayer() == nullptr) {
                            reportIllegalCommand("The current player is not a computer, specify move details for human player");
                            break;
                        }
                            
                        // Gauranteed to get valid move
                        std::unique_ptr<BoardMove> computerMove = getPlayer(currentTurn).getComputerPlayer()->generateMove(chessBoard);
                        chessBoard->makeMove(computerMove);
                        switchTurn();

                        notifyObservers();
                        if (ChessBoardUtilities::isGameOver(chessBoard)) {
                            resetGame();
                            notifyObservers();
                        }
                    }
                    break;
            }

        } else if (std::regex_match(inputLine, matches, commandPatterns[CommandType::UNDO_MOVE])) {
            switch (gameState) {
                case GameState::MAIN_MENU:
                    reportIllegalCommand("No game is running, you are in the main menu");
                    break;
                case GameState::SETUP:
                    reportIllegalCommand("No game is running, you are in setup mode");
                    break;
                case GameState::GAME_ACTIVE:
                    if (chessBoard->undoMove()) {
                        switchTurn();
                        notifyObservers;
                    } else {
                        reportIllegalCommand("There are no moves to undo");
                    }
                    break;
            }

        } else if (std::regex_match(inputLine, matches, commandPatterns[CommandType::RESIGN_GAME])) {
            switch (gameState) {
                case GameState::MAIN_MENU:
                    reportIllegalCommand("No game is running, you are in the main menu");
                    break;
                case GameState::SETUP:
                    reportIllegalCommand("No game is running, you are in setup mode");
                    break;
                case GameState::GAME_ACTIVE:
                    notifyObservers();
                    resetGame();
                    break;
            }

       } else if (std::regex_match(inputLine, matches, commandPatterns[CommandType::PLACE_PIECE])) {
            switch (gameState) {
                case GameState::MAIN_MENU:
                    reportIllegalCommand("Can't set piece in main menu");
                    break;
                case GameState::GAME_ACTIVE:
                    reportIllegalCommand("Can't set piece when game is active");
                    break;
                case GameState::SETUP:
                    std::string square = matches[1].str();
                    if (!chessBoard->isSquareOnBoard(createBoardSquare(UserSquare(square), chessBoard->getNumRows(), chessBoard->getNumCols()))) {
                        reportIllegalCommand("Input square is not valid on board");
                        break;
                    }
                    
                    std::string piece = matches[2].str();
                    if (!isValidPieceType(piece)) {
                        reportIllegalCommand("Input piece is not valid");
                        break;
                    }

                    BoardSquare boardSquare = createBoardSquare(UserSquare(square), chessBoard->getNumRows(), chessBoard->getNumCols());
                    PieceType pieceType = stringToPieceType(piece);
                    PieceLevel pieceLevel = matches[3].matched ? stringToPieceLevel(matches[3].str()) : PieceLevel::BASIC;
                    Team team = std::isupper(piece.front()) ? Team::TEAM_ONE : Team::TEAM_TWO;
                    PieceDirection pieceDirection = matches[4].matched ? stringToPieceDirection(matches[4]) :
                        (team == Team::TEAM_ONE ? PieceDirection::NORTH : PieceDirection::SOUTH);
                    
                    chessBoard->setPosition(boardSquare, PieceData(pieceType, pieceLevel, team, stringToPieceDirection(tokens[3]), false));
                    notifyObservers();
                    break;
            }       
            
        } else if (std::regex_match(inputLine, matches, commandPatterns[CommandType::REMOVE_PIECE])) {
            switch (gameState) {
                case GameState::MAIN_MENU:
                    reportIllegalCommand("Can't clear piece in main menu");
                    break;
                case GameState::GAME_ACTIVE:
                    reportIllegalCommand("Can't clear piece when game is active");
                    break;
                case GameState::SETUP:
                    std::string square = matches[1];
                    if (!chessBoard->isSquareOnBoard(createBoardSquare(UserSquare(square), chessBoard->getNumRows(), chessBoard->getNumCols()))) {
                        reportIllegalCommand("Input square is not valid on board");
                        break;
                    } 
                    
                    if (chessBoard->clearPosition(createBoardSquare(UserSquare(square), chessBoard->getNumRows(), chessBoard->getNumCols()))) {
                        notifyObservers();
                    }
                    break;
            }
            
        } else if (std::regex_match(inputLine, matches, commandPatterns[CommandType::SWITCH_TURN])) {
            switch (gameState) {
                case GameState::MAIN_MENU:
                    reportIllegalCommand("Can't set first turn in main menu");
                    break;
                case GameState::GAME_ACTIVE:
                    reportIllegalCommand("Can't set first turn when game is active");
                    break;
                case GameState::SETUP:
                    switchTurn();
                    notifyObservers();
                    break;
            }
            
        } else if (std::regex_match(inputLine, matches, commandPatterns[CommandType::EXIT_SETUP_MODE])) {
            switch (gameState) {
                case GameState::MAIN_MENU:
                    reportIllegalCommand("Can't leave setup mode in main menu");
                    break;
                case GameState::GAME_ACTIVE:
                    reportIllegalCommand("Can't leave setup mode when game is active");
                    break;
                case GameState::SETUP:
                    if (!ChessBoardUtilities::isBoardInLegalSetupState(chessBoard)) {
                        reportIllegalCommand("Board is not in valid state, can't leave setup mode");
                        break;
                    }

                    setGameState(GameState::MAIN_MENU);
                    notifyObservers();
                    break;
            }

        } else if (std::regex_match(inputLine, matches, commandPatterns[CommandType::APPLY_STANDARD_SETUP])) {
            switch (gameState) {
                case GameState::MAIN_MENU:
                    reportIllegalCommand("Can't apply standard setup in main menu");
                    break;
                case GameState::GAME_ACTIVE:
                    reportIllegalCommand("Can't apply standard setup when game is active");
                    break;
                case GameState::SETUP:
                    std::unique_ptr<ChessBoard> newChessBoard = ChessBoardFactory::createChessBoard(chessBoard->getNumRows(), chessBoard->getNumCols());
                    if (!ChessBoardUtilities::applyStandardSetup(newChessBoard)) {
                        reportIllegalCommand("Board is too small to apply standard setup");
                        break;
                    }

                    chessBoard = std::move(newChessBoard);
                    notifyObservers();
            }
                    
        } else if (std::regex_match(inputLine, matches, commandPatterns[CommandType::CREATE_BOARD])) {
            switch (gameState) {
                case GameState::MAIN_MENU:
                    reportIllegalCommand("Can't set board size in main menu");
                    break;
                case GameState::GAME_ACTIVE:
                    reportIllegalCommand("Can't set board size when game is active");
                    break;
                case GameState::SETUP:
                    int numRows = std::stoi(matches[1].str());
                    int numCols = std::stoi(matches[2].str());

                    if (numRows < 1 || numRows > 26) {
                        reportIllegalCommand("Rows must be between 1 and 26 inclusive");
                        break;
                    } else if (numCols < 8 || numCols > 26) {
                        reportIllegalCommand("Cols must be between 1 and 26 inclusive");
                        break;
                    }

                    chessBoard = ChessBoardFactory::createChessBoard(numRows, numCols);
                    notifyObservers();
                    break;
            }

        } else {
            reportIllegalCommand("Invalid command entered");
        }
    }
}
