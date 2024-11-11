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
#include "ChessBoard.h"

#include "ChessBoardImpl.h"
#include "ChessBoardFactory.h"
#include "ChessBoardUtilities.h"
#include "Player.h"
#include "Utilities.h"
#include "PlayerFactory.h"


Game::Game(std::unique_ptr<CommandRetriever> commandRetriever, std::unique_ptr<IllegalCommandReporter> illegalCommandReporter) :
    gameState(GameState::MAIN_MENU),
    chessBoard(ChessBoardFactory::createChessBoard(8, 8)),
    commandRetriever(std::move(commandRetriever)), 
    illegalCommandReporter(std::move(illegalCommandReporter)),
    players(std::make_pair(
        PlayerFactory::createHumanPlayer(chessBoard->getTeamOne()),
        PlayerFactory::createHumanPlayer(chessBoard->getTeamTwo())
    )),
    currentTurn(chessBoard->getTeamOne()) {
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
            Player(getPlayer(chessBoard->getTeamOne())), 
            Player(getPlayer(chessBoard->getTeamTwo()))
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
    if (currentTurn == chessBoard->getTeamOne()) {
        currentTurn == chessBoard->getTeamTwo();
    } else {
        currentTurn == chessBoard->getTeamOne();
    }
}

Player const& Game::getPlayer(Team team) const {
    if (team == chessBoard->getTeamOne()) {
        return players.first;
    } else {
        return players.second;
    }
}

void Game::resetGame() {
    setGameState(GameState::MAIN_MENU);
    currentTurn = chessBoard->getTeamOne();
    chessBoard = ChessBoardFactory::createChessBoard(8, 8);
    ChessBoardUtilities::applyStandardSetup(chessBoard);
    players = std::make_pair(
        PlayerFactory::createHumanPlayer(chessBoard->getTeamOne()),
        PlayerFactory::createHumanPlayer(chessBoard->getTeamTwo())
    );
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
        std::string input = commandRetriever->retrieveCommand();
        std::smatch matches;

        // Start Game
        if (std::regex_match(input, matches, std::regex(R"(\s*game\s*(human|computer[1-5])\s*(human|computer[1-5])\s*)", std::regex_constants::icase))) {
            switch (gameState) {
                case GameState::GAME_ACTIVE:
                    reportIllegalCommand("Can't start a game when a game is already running");
                    break;
                case GameState::SETUP:
                    reportIllegalCommand("Can't start a game from within setup mode");
                    break;
                case GameState::MAIN_MENU:
                    Team teamOne = chessBoard->getTeamOne();
                    Player playerOne = Utilities::stringToPlayerType(matches[1].str()).value() == PlayerType::HUMAN 
                        ? PlayerFactory::createHumanPlayer(teamOne)
                        : PlayerFactory::createComputerPlayer(teamOne, ComputerPlayerFactory::createComputerPlayer(Utilities::stringToComputerPlayerLevel(std::string(1, matches[1].str().back())).value(), teamOne));

                    Team teamTwo = chessBoard->getTeamTwo();
                    Player playerTwo = Utilities::stringToPlayerType(matches[2].str()).value() == PlayerType::HUMAN 
                        ? PlayerFactory::createHumanPlayer(teamTwo)
                        : PlayerFactory::createComputerPlayer(teamTwo, ComputerPlayerFactory::createComputerPlayer(Utilities::stringToComputerPlayerLevel(std::string(1, matches[2].str().back())).value(), teamTwo));

                    players = std::make_pair(std::move(playerOne), std::move(playerTwo));
                    setGameState(GameState::GAME_ACTIVE);
                    notifyObservers();
                    break;  
            }

        // Enter Setup Mode
        } else if (std::regex_match(input, matches, std::regex(R"(\s*setup\s*)", std::regex_constants::icase))) {
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

        // Make Move
        } else if (std::regex_match(input, matches, std::regex(R"(\s*move\s*(?:([a-z]+[1-9][0-9]*)\s*([a-z]+[1-9][0-9]*)\s*([a-z]?)\s*)?)", std::regex_constants::icase))) {
            switch (gameState) {
                case GameState::MAIN_MENU:
                    reportIllegalCommand("You're on the main menu page, cannot enter a move when game is not active");
                    break;
                case GameState::SETUP:
                    reportIllegalCommand("You're in setup mode, cannot enter a move when game is not active");
                    break;
                case GameState::GAME_ACTIVE:
                    if (matches[1].matched) {
                        if (getPlayer(currentTurn).getPlayerType() == PlayerType::COMPUTER) {
                            reportIllegalCommand("The current player is not a human, don't specify move details for computer player");
                            break;
                        }
                        
                        std::optional<BoardSquare> fromSquare = BoardSquare::createBoardSquare(matches[1].str(), chessBoard->getNumRows(), chessBoard->getNumCols());
                        std::optional<BoardSquare> toSquare = BoardSquare::createBoardSquare(matches[2].str(), chessBoard->getNumRows(), chessBoard->getNumCols());
                        if (!fromSquare.has_value() || !toSquare.has_value() || !chessBoard->isSquareOnBoard(fromSquare.value()) || !chessBoard->isSquareOnBoard(toSquare.value())) {
                            reportIllegalCommand("Invalid squares");
                            break;
                        }

                        std::optional<PieceType> promotionPieceType;
                        if (matches[3].matched && !Utilities::stringToPieceType(matches[3].str()).has_value()) {
                            reportIllegalCommand("Invalid promotion piece");
                            break;
                        } else {
                            promotionPieceType = Utilities::stringToPieceType(matches[3].str());
                        }
                        
                        std::optional<std::unique_ptr<BoardMove>> boardMove = chessBoard->createBoardMove(fromSquare.value(), toSquare.value(), promotionPieceType);
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
                        if (getPlayer(currentTurn).getPlayerType() == PlayerType::HUMAN) {
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

        // Undo Move
        } else if (std::regex_match(input, matches, std::regex(R"(\s*undo\s*)", std::regex_constants::icase))) {
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

        // Resign Game
        } else if (std::regex_match(input, matches, std::regex(R"(\s*resign\s*)", std::regex_constants::icase))) {
            switch (gameState) {
                case GameState::MAIN_MENU:
                    reportIllegalCommand("No game is running, you are in the main menu");
                    break;
                case GameState::SETUP:
                    reportIllegalCommand("No game is running, you are in setup mode");
                    break;
                case GameState::GAME_ACTIVE:
                    resetGame();
                    notifyObservers();
                    break;
            }

        // Place Piece
        } else if (std::regex_match(input, matches, std::regex(R"(\s*+\s*([a-z]+[1-9][0-9]*)\s*([a-zA-Z])\s*(basic|advanced)?\s*(north|south|west|east)?\s*)", std::regex_constants::icase))) {
            switch (gameState) {
                case GameState::MAIN_MENU:
                    reportIllegalCommand("Can't set piece in main menu");
                    break;
                case GameState::GAME_ACTIVE:
                    reportIllegalCommand("Can't set piece when game is active");
                    break;
                case GameState::SETUP:
                    std::optional<BoardSquare> boardSquare = BoardSquare::createBoardSquare(matches[1].str(), chessBoard->getNumRows(), chessBoard->getNumCols());
                    if (!boardSquare.has_value() || !chessBoard->isSquareOnBoard(boardSquare.value())) {
                        reportIllegalCommand("Input square is not valid on board");
                        break;
                    }

                    PieceType pieceType;
                    if (Utilities::stringToPieceType(matches[2].str()).has_value()) {
                        pieceType = Utilities::stringToPieceType(matches[2].str()).value();
                    } else {
                        reportIllegalCommand("Invalid piece");
                        break;
                    }
                    
                    Team team = std::isupper(matches[2].str().front()) ? chessBoard->getTeamOne() : chessBoard->getTeamTwo();

                    PieceLevel pieceLevel;
                    if (matches[3].matched) {
                        if (Utilities::stringToPieceLevel(matches[3].str()).has_value()) {
                            pieceLevel = Utilities::stringToPieceLevel(matches[3].str()).value();
                        } else {
                            reportIllegalCommand("Invalid piece level");
                            break;
                        }
                    } else {
                        pieceLevel == PieceLevel::BASIC;
                    }

                    PieceDirection pieceDirection;
                    if (matches[4].matched) {
                        if (Utilities::stringToPieceDirection(matches[4].str()).has_value()) {
                            pieceDirection = Utilities::stringToPieceDirection(matches[4].str()).value();
                        } else {
                            reportIllegalCommand("Invalid piece direction");
                            break;
                        }
                    } else {
                        pieceDirection = team == chessBoard->getTeamOne()
                            ? PieceDirection::NORTH
                            : PieceDirection::SOUTH;
                    }
                    
                    chessBoard->setPosition(boardSquare.value(), PieceData(pieceType, pieceLevel, team, pieceDirection, false));
                    notifyObservers();
                    break;
            }       
            
        // Remove Piece
        } else if (std::regex_match(input, matches, std::regex(R"(\s*-\s*([a-z]+[1-9][0-9]*)\s*)", std::regex_constants::icase))) {
            switch (gameState) {
                case GameState::MAIN_MENU:
                    reportIllegalCommand("Can't clear piece in main menu");
                    break;
                case GameState::GAME_ACTIVE:
                    reportIllegalCommand("Can't clear piece when game is active");
                    break;
                case GameState::SETUP:
                    std::optional<BoardSquare> boardSquare = BoardSquare::createBoardSquare(matches[1].str(), chessBoard->getNumRows(), chessBoard->getNumCols());
                    if (!boardSquare.has_value() || !chessBoard->isSquareOnBoard(boardSquare.value())) {
                        reportIllegalCommand("Input square is not valid on board");
                        break;
                    } 
                    
                    if (chessBoard->clearPosition(boardSquare.value())) {
                        notifyObservers();
                    }
                    break;
            }
            
        // Set First Turn
        } else if (std::regex_match(input, matches, std::regex(R"(\s*switch\s*)", std::regex_constants::icase))) {
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

        // Exit Setup Mode  
        } else if (std::regex_match(input, matches, std::regex(R"(\s*done\s*)", std::regex_constants::icase))) {
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

        // Apply Standard Setup
        } else if (std::regex_match(input, matches, std::regex(R"(\s*standard\s*)", std::regex_constants::icase))) {
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

        // Set Board Size   
        } else if (std::regex_match(input, matches, std::regex(R"(\s*set\s*([1-9][0-9]*)\s*([1-9][0-9]*))", std::regex_constants::icase))) {
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
