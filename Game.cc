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
#include "UserMove.h"

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

bool Game::isInMainMenuGameState() const {
    return gameState == GameState::MAIN_MENU;
}

bool Game::isInSetupGameState() const {
    return gameState == GameState::SETUP;
}

bool Game::isInActiveGameState() const {
    return gameState == GameState::GAME_ACTIVE;
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

        std::string token;
        std::istringstream lineStream(inputLine);
        while (lineStream >> token) {
            tokens.emplace_back(token);
        }

        if (tokens.empty()) {
            continue;
        }
        std::string firstToken = tokens[0];

        #pragma mark - Commands legal from main menu game state
        if (firstToken == "game") {
            static std::regex const pattern("^(human|computer[1-5])$");
            switch (gameState) {
                case GameState::GAME_ACTIVE:
                    reportIllegalCommand("Can't start a game when a game is already running");
                    break;
                case GameState::SETUP:
                    reportIllegalCommand("Can't start a game from within setup mode");
                    break;
                case GameState::MAIN_MENU:
                    if (tokens.size() < 3) {
                        reportIllegalCommand("Must specify a player type for both players");
                        break;
                    } else if (tokens.size() > 3) {
                        reportIllegalCommand("Too many input tokens on line");
                        break;   
                    } else if (!std::regex_match(tokens[1], pattern) || !std::regex_match(tokens[2], pattern)) {
                        reportIllegalCommand("Invalid syntax, expecting (human|computer[1-4])");
                        break;
                    }

                    players = std::make_pair(
                        Player(Team::TEAM_ONE, (tokens[1] == "human") ? nullptr : ComputerPlayerFactory::createComputerPlayer(stringToComputerPlayerLevel(std::string(1, tokens[1].back())), Team::TEAM_ONE)),
                        Player(Team::TEAM_TWO, (tokens[2] == "human") ? nullptr : ComputerPlayerFactory::createComputerPlayer(stringToComputerPlayerLevel(std::string(1, tokens[2].back())), Team::TEAM_TWO))

                    );
                    setGameState(GameState::GAME_ACTIVE);
                    notifyObservers();
                    break;    
            }

        } else if (firstToken == "setup") {
            switch (gameState) {
                case GameState::GAME_ACTIVE:
                    reportIllegalCommand("Can't enter setup mode from within an active game");
                    break;
                case GameState::SETUP:
                    reportIllegalCommand("Already in setup mode");
                    break;
                case GameState::MAIN_MENU:
                    if (tokens.size() >= 2) {
                        reportIllegalCommand("Too many input tokens on line");
                        break;
                    }

                    chessBoard->clearBoard();
                    setGameState(GameState::SETUP);
                    notifyObservers();
                    break;         
            }

        #pragma mark - Commands legal from active game state
        } else if (firstToken == "move") {
            switch (gameState) {
                case GameState::MAIN_MENU:
                    reportIllegalCommand("You're on the main menu page, cannot enter a move when game is not active");
                    break;
                case GameState::SETUP:
                    reportIllegalCommand("You're in setup mode, cannot enter a move when game is not active");
                    break;
                case GameState::GAME_ACTIVE:
                    if (tokens.size() == 2) {
                        reportIllegalCommand("You need to specify a square to move to");
                        break;
                    } else if (tokens.size() >= 5) {
                        reportIllegalCommand("Too many input tokens on line");
                        break;
                    }
            
                    if (tokens.size() == 1) {   // Computer move
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
                    } else {    // Player move
                        if (getPlayer(currentTurn).getComputerPlayer() != nullptr) {
                            reportIllegalCommand("The current player is not a human, don't specify move details for computer player");
                            break;
                        }
                        
                        std::string fromSquare = tokens[1];
                        std::string toSquare = tokens[2];
                        std::string promotionPiece = tokens.size() == 3 ? "" : tokens[3];
                        if (!UserSquare::isValidUserSquare(fromSquare) || !UserSquare::isValidUserSquare(toSquare) || !isValidPieceType(promotionPiece)) {
                            reportIllegalCommand("Invalid user move, try again");
                            break;
                        }
                        
                        BoardSquare fromBoardSquare = createBoardSquare(UserSquare(fromSquare), chessBoard->getNumRows(), chessBoard->getNumCols());
                        BoardSquare toBoardSquare = createBoardSquare(UserSquare(toSquare), chessBoard->getNumRows(), chessBoard->getNumCols());
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
                    } 
                    break;
            }
            
        } else if (firstToken == "resign") {
            switch (gameState) {
                case GameState::MAIN_MENU:
                    reportIllegalCommand("No game is running, you are in the main menu");
                    break;
                case GameState::SETUP:
                    reportIllegalCommand("No game is running, you are in setup mode");
                    break;
                case GameState::GAME_ACTIVE:
                    if (tokens.size() >= 2) {
                        reportIllegalCommand("Too many input tokens on line");
                        break;
                    }

                    notifyObservers();
                    resetGame();
                    break;
            }

        } else if (firstToken == "undo") {
            switch (gameState) {
                case GameState::MAIN_MENU:
                    reportIllegalCommand("No game is running, you are in the main menu");
                    break;
                case GameState::SETUP:
                    reportIllegalCommand("No game is running, you are in setup mode");
                    break;
                case GameState::GAME_ACTIVE:
                    if (tokens.size() >= 2) {
                        reportIllegalCommand("Too many input tokens on line");
                        break;
                    }

                    if (chessBoard->undoMove()) {
                        switchTurn();
                        notifyObservers;
                    } else {
                        reportIllegalCommand("There are no moves to undo");
                    }
                    break;
            }
           
        } else if (firstToken == "show") {
            switch (gameState) {
                case GameState::MAIN_MENU:
                    reportIllegalCommand("No game is running, you are in the main menu");
                    break;
                case GameState::SETUP:
                    reportIllegalCommand("No game is running, you are in setup mode");
                    break;
                case GameState::GAME_ACTIVE:
                    if (tokens.size() != 1) {
                        reportIllegalCommand("Too many input tokens on line, expected show");
                        break;
                    }

                    showingStandardOpenings = true;
                    notifyObservers();
                    showingStandardOpenings = false;
                    break;

            }

        #pragma mark - Commands legal from setup game state
        } else if (firstToken == "+") {
            switch (gameState) {
                case GameState::MAIN_MENU:
                    reportIllegalCommand("Can't set piece in main menu");
                    break;
                case GameState::GAME_ACTIVE:
                    reportIllegalCommand("Can't set piece when game is active");
                    break;
                case GameState::SETUP:
                    if (tokens.size() == 1) {
                        reportIllegalCommand("Not enough input tokens on line, must specify piece and square to place piece at");
                        break;
                    } else if (tokens.size() == 2) {
                        reportIllegalCommand("Not enough input tokens on line, must specify square to place piece at");
                        break;
                    }

                    std::string piece = tokens[1];
                    if (!isValidPieceType(piece)) {
                        reportIllegalCommand("Input piece is not valid");
                        break;
                    }
                    
                    std::string square = tokens[2];
                    if (!UserSquare::isValidUserSquare(square) || !chessBoard->isSquareOnBoard(createBoardSquare(UserSquare(square), chessBoard->getNumRows(), chessBoard->getNumCols()))) {
                        reportIllegalCommand("Input square is not valid on board");
                        break;
                    }

                    PieceType pieceType = stringToPieceType(piece);
                    Team team = std::isupper(piece.front()) ? Team::TEAM_ONE : Team::TEAM_TWO;
                    PieceDirection pieceDirection = team == Team::TEAM_ONE ? PieceDirection::NORTH : PieceDirection::SOUTH;
                    BoardSquare boardSquare = createBoardSquare(UserSquare(square), chessBoard->getNumRows(), chessBoard->getNumCols());

                    if (tokens.size() == 3) {
                        chessBoard->setPosition(boardSquare, PieceData(pieceType, PieceLevel::BASIC, team, pieceDirection, false));
                        notifyObservers();
                        break;
                    }

                    if (tokens.size() == 4) {
                        if (!isValidPieceDirection(tokens[3])) {
                            reportIllegalCommand("Invalid direction");
                            break;
                        }

                        chessBoard->setPosition(boardSquare, PieceData(pieceType, PieceLevel::BASIC, team, stringToPieceDirection(tokens[3]), false));
                        notifyObservers();
                    }

                    reportIllegalCommand("Too many input tokens on line");
                    break;
            }       
            
        } else if (firstToken == "-") {
            switch (gameState) {
                case GameState::MAIN_MENU:
                    reportIllegalCommand("Can't clear piece in main menu");
                    break;
                case GameState::GAME_ACTIVE:
                    reportIllegalCommand("Can't clear piece when game is active");
                    break;
                case GameState::SETUP:
                    if (tokens.size() == 1) {
                        reportIllegalCommand("Not enough input tokens on line, must specify square to remove piece from");
                        break;
                    } else if (tokens.size() > 2) {
                        reportIllegalCommand("Too many input tokens on line");
                        break;
                    }

                    std::string square = tokens[1];
                    if (!UserSquare::isValidUserSquare(square) || chessBoard->isSquareOnBoard(createBoardSquare(UserSquare(square), chessBoard->getNumRows(), chessBoard->getNumCols()))) {
                        reportIllegalCommand("Input square is not valid on board");
                        break;
                    } 
                    
                    if (chessBoard->clearPosition(createBoardSquare(UserSquare(square), chessBoard->getNumRows(), chessBoard->getNumCols()))) {
                        notifyObservers();
                    }
                    break;
            }
            
        } else if (firstToken == "=") {
            switch (gameState) {
                case GameState::MAIN_MENU:
                    reportIllegalCommand("Can't set first turn in main menu");
                    break;
                case GameState::GAME_ACTIVE:
                    reportIllegalCommand("Can't set first turn when game is active");
                    break;
                case GameState::SETUP:
                    if (tokens.size() == 1) {
                        reportIllegalCommand("Not enough input tokens on line, must specify color to go first");
                        break;
                    } else if (tokens.size() > 2) {
                        reportIllegalCommand("Too many input tokens on line");
                        break;
                    } else if (!isValidColor(tokens[1])) {
                        reportIllegalCommand("Must specify color to go first");
                        break;
                    }
                    
                    if (stringToColor(tokens[1]) != currentTurn) {
                        switchTurn();
                        notifyObservers();
                    }
                    break;
            }
            
        } else if (firstToken == "done") {
            switch (gameState) {
                case GameState::MAIN_MENU:
                    reportIllegalCommand("Can't leave setup mode in main menu");
                    break;
                case GameState::GAME_ACTIVE:
                    reportIllegalCommand("Can't leave setup mode when game is active");
                    break;
                case GameState::SETUP:
                    if (tokens.size() >= 2) {
                        reportIllegalCommand("Too many input tokens on line");
                        break;
                    } else if (!ChessBoardUtilities::isBoardInLegalSetupState(chessBoard)) {
                        reportIllegalCommand("Board is not in valid state, can't leave setup mode");
                        break;
                    }

                    setGameState(GameState::MAIN_MENU);
                    notifyObservers();
                    break;
            }

        } else if (firstToken == "basic") {
            switch (gameState) {
                case GameState::MAIN_MENU:
                    reportIllegalCommand("Can't apply basic setup in main menu");
                    break;
                case GameState::GAME_ACTIVE:
                    reportIllegalCommand("Can't apply basic setup when game is active");
                    break;
                case GameState::SETUP:
                    if (tokens.size() > 1) {
                        reportIllegalCommand("Too many input tokens on line");
                        break;
                    }

                    chessBoard->clearBoard();
                    ChessBoardUtilities::applyStandardSetup(chessBoard);
                    notifyObservers();
            }
                    
        } else if (firstToken == "set") {
            switch (gameState) {
                case GameState::MAIN_MENU:
                    reportIllegalCommand("Can't set board size in main menu");
                    break;
                case GameState::GAME_ACTIVE:
                    reportIllegalCommand("Can't set board size when game is active");
                    break;
                case GameState::SETUP:
                    if (tokens.size() >= 1 && tokens.size() < 3) {
                        reportIllegalCommand("Not enough input tokens on line, expecting set rows cols");
                        break;
                    } else if (tokens.size() > 3) {
                        reportIllegalCommand("Too many input tokens on line");
                        break;
                    } else if (!isInt(tokens[1]) || std::stoi(tokens[1]) < 8 || std::stoi(tokens[1]) > 26) {
                        reportIllegalCommand("Rows must be between 8 and 26 inclusive");
                        break;
                    } else if (!isInt(tokens[2]) || std::stoi(tokens[2]) < 8 || std::stoi(tokens[2]) > 26) {
                        reportIllegalCommand("Cols must be between 8 and 26 inclusive");
                        break;
                    }

                    chessBoard = ChessBoardFactory::createChessBoard(std::stoi(tokens[1]), std::stoi(tokens[2]));
                    notifyObservers();
                    break;
            }
                    
        } else {
            reportIllegalCommand("Invalid command entered");
        }
    }
}
