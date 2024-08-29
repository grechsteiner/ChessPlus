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


#include "Constants.h"
#include "Game.h"
#include "CommandLineInput.h"
#include "CommandLineErrorReporter.h"

#include "ComputerPlayerFactory.h"
#include "ComputerPlayer.h"

#include "FullMove.h"
#include "UserEnteredMove.h"

#include "ChessBoard.h"

#include "Board.h"

Game::Game(ChessBoard &board, std::istream &in, std::ostream &out, std::ostream &errorOut) : 
    board(board),
    input(std::make_unique<CommandLineInput>(in)), 
    errorReporter(std::make_unique<CommandLineErrorReporter>(errorOut)),
    out(out)
    {
        board.applyStandardSetup();
    }

void Game::outputError(std::string const &errorMessage) const {
    errorReporter->reportError(errorMessage);
}

void Game::incrementTurn() {
    if (currentTurn == 0) {
        ++currentTurn;
    } else {
        --currentTurn;
    }
}

void Game::decrementTurn() {
    if (currentTurn == 0) {
        ++currentTurn;
    } else {
        --currentTurn;
    }
}

void Game::setGameState(GameState newGameState) {
    gameState = newGameState;
}

bool Game::isInMainMenu() const {
    return gameState == GameState::MAIN_MENU;
}

bool Game::isInSetupMode() const {
    return gameState == GameState::SETUP;
}

bool Game::isGameActive() const {
    return gameState == GameState::GAME_ACTIVE;
}

GameState Game::getGameState() const {
    return gameState;
}

const std::tuple<PlayerTuple, PlayerTuple>& Game::getMainMenuState() const {
    return players;
}

std::tuple<const ChessBoard&, const std::tuple<PlayerTuple, PlayerTuple>&, int> Game::getSetupState() const {
    return std::make_tuple(board, std::cref(players), currentTurn);
}

std::tuple<const ChessBoard&, const std::tuple<PlayerTuple, PlayerTuple>&, int, bool> Game::getActiveGameState() const {
    return std::make_tuple(board, std::cref(players), currentTurn, showingStandardOpenings);
}

void Game::resetComputerPlayers() {
    std::get<2>(std::get<0>(players)) = nullptr;
    std::get<2>(std::get<1>(players)) = nullptr;
}

void Game::applyStalematePoints() {
    std::get<1>(std::get<0>(players)) += 0.5;
    std::get<1>(std::get<1>(players)) += 0.5;
}
    
void Game::applyWinPoints(Color color) {
    if (color == Color::WHITE) {
        std::get<1>(std::get<0>(players)) += 1;
    } else {
        std::get<1>(std::get<1>(players)) += 1;
    }
}

PlayerTuple& Game::getPlayerWithTurn(int i) {
    if (i == 0) {
        return std::get<0>(players);
    } else {
        return std::get<1>(players);
    }
}


void Game::runGame() {
    notifyObservers();

    std::string inputLine;
    while (input->isInputAvailable()) {
        inputLine = input->getInput();

        // Parse into tokens
        std::istringstream lineStream(inputLine);
        std::string token;
        std::vector<std::string> tokens;
        while (lineStream >> token) {
            tokens.push_back(token);
        }

        if (tokens.empty()) {
            continue;
        }

        std::string firstToken = tokens[0];
        if (firstToken == "game") {
            if (isGameActive()) {
                outputError("Can't start a game when a game is already running");
            } else if (isInSetupMode()) {
                outputError("Can't start a game from within setup mode");
            } else if (tokens.size() < 3) {
                outputError("Must specify a player type for each player");
            } else if (tokens.size() > 3) {
                outputError("Too many input tokens on line");            
            } else {

                static std::regex const pattern("^(human|computer[1-4])$");

                if (!std::regex_match(tokens[1], pattern) || !std::regex_match(tokens[2], pattern)) {
                    outputError("Invalid syntax, expecting (human|computer[1-4])");
                } else {
                    std::get<2>(std::get<0>(players)) = (tokens[1] == "human") ? nullptr : ComputerPlayerFactory::createComputerPlayer(std::stoi(std::string(1, tokens[1].back())));
                    std::get<2>(std::get<1>(players)) = (tokens[2] == "human") ? nullptr : ComputerPlayerFactory::createComputerPlayer(std::stoi(std::string(1, tokens[2].back())));
                    setGameState(GameState::GAME_ACTIVE);
                    notifyObservers();
                    
                    if (board.isInStaleMate()) {
                        applyStalematePoints();
                        board.clearBoard();
                        board.setBoardSize(8, 8);
                        board.applyStandardSetup();

                        // Reset players for next run through
                        resetComputerPlayers();

                        setGameState(GameState::MAIN_MENU);
                        notifyObservers();
                    }
                }
            }

        } else if (firstToken == "setup") {
            if (isGameActive()) {
                outputError("Can't enter setup mode from within an active game");
            } else if (isInSetupMode()) {
                outputError("Already in setup mode");
            } else if (tokens.size() >= 2) {
                outputError("Too many input tokens on line");
            } else {
                gameState = GameState::SETUP;
                board.clearBoard();
                notifyObservers();
            }

        } else if (firstToken == "move") {
            if (isInMainMenu()) {
                outputError("You're on the main menu page, cannot enter a move when game is not active");
            } else if (isInSetupMode()) {
                outputError("You're in setup mode, cannot enter a move when game is not active");
            } else if (tokens.size() == 2) {
                outputError("You need to specify a square to move to");
            } else if (tokens.size() >= 5) {
                outputError("Too many input tokens on line");
            } else {

                bool moveMade = false;
                if (tokens.size() == 1) {
                    // Computer move
                    if (std::get<2>(getPlayerWithTurn(currentTurn)) == nullptr) {
                        outputError("The current player is not a computer, specify move details for human player");
                    } else {
                        // Gauranteed to get valid move
                        FullMove compMove = std::get<2>(getPlayerWithTurn(currentTurn))->getMove(board, std::get<0>(getPlayerWithTurn(currentTurn)));
                        board.makeMove(compMove);
                        incrementTurn();
                        moveMade = true;
                    }
                } else {
                    // Player move
                    if (std::get<2>(getPlayerWithTurn(currentTurn)) != nullptr) {
                        outputError("The current player is not a human, don't specify move details for computer player");
                    } else {
                        std::string fromSquare = tokens[1];
                        std::string toSquare = tokens[2];
                        std::string promotionPiece = tokens.size() == 3 ? "" : tokens[3];
                        if (UserSquare::isValidChessBoardSquare(fromSquare) && UserSquare::isValidChessBoardSquare(toSquare) && isValidPieceType(promotionPiece)) {
                            std::unique_ptr<FullMove> fullMove = board.generateFullMove(UserMove(UserSquare(fromSquare), UserSquare(toSquare), stringToPieceType(promotionPiece)));
                            // Nullptr if invalid move
                            if (fullMove != nullptr) {
                                board.makeMove(*fullMove);
                                incrementTurn();
                                moveMade = true;
                            }
                            
                        } else {
                            outputError("Invalid move, try again");
                        }
                    }
                } 

                if (moveMade) {
                    notifyObservers();

                    if (board.hasGameFinished()) {
                        
                        // Update points
                        if (board.isInStaleMate()) {
                            applyStalematePoints();
                        } else {
                            Color winner = currentTurn == 0 ? Color::BLACK : Color::WHITE;
                            applyWinPoints(winner);
                        }

                        // Reset board for next run through
                        board.clearBoard();
                        board.setBoardSize(8, 8);
                        board.applyStandardSetup();

                        // Reset players for next run through
                        resetComputerPlayers();

                        setGameState(GameState::MAIN_MENU);
                        notifyObservers();
                        currentTurn = 0;
                    }
                }
            }
            
        } else if (firstToken == "resign") {
            if (isInMainMenu()) {
                outputError("No game is running, you are in the main menu");
            } else if (isInSetupMode()) {
                outputError("No game is running, you are in setup mode");
            } else if (tokens.size() >= 2) {
                outputError("Too many input tokens on line");
            } else {


                if (currentTurn == 0) {
                    applyWinPoints(Color::BLACK);
                } else {
                    applyWinPoints(Color::WHITE);
                }

                // Reset board for next run through
                board.clearBoard();
                board.setBoardSize(8, 8);
                board.applyStandardSetup();

                // Reset players for next run through
                resetComputerPlayers();

                setGameState(GameState::MAIN_MENU);
                notifyObservers();
                currentTurn = 0;
            }


        } else if (firstToken == "undo") {
            if (isInMainMenu()) {
                outputError("No game is running, you are in the main menu");
            } else if (isInSetupMode()) {
                outputError("No game is running, you are in setup mode");
            } else if (tokens.size() >= 2) {
                outputError("Too many input tokens on line");
            } else {
                if (board.undoMove()) {
                    decrementTurn();
                    notifyObservers();
                }
            }

        } else if (firstToken == "show") {
            if (isInMainMenu()) {
                outputError("No game is running, you are in the main menu");
            } else if (isInSetupMode()) {
                outputError("No game is running, you are in setup mode");
            } else if (tokens.size() != 1) {
                outputError("Too many input tokens on line, expected show");
            } else {
                showingStandardOpenings = true;
                notifyObservers();
                showingStandardOpenings = false;
            }

        } else if (firstToken == "+") {
            if (isInMainMenu()) {
                outputError("Can't set piece in main menu");
            } else if (isGameActive()) {
                outputError("Can't set piece when game is active");
            } else if (tokens.size() == 1) {
                outputError("Not enough input tokens on line, must specify piece and square to place piece at");
            } else if (tokens.size() == 2) {
                outputError("Not enough input tokens on line, must specify square to place piece at");
            } else {
                std::string piece = tokens[1];
                std::string square = tokens[2];

                if (!isValidPieceType(piece)) {
                    outputError("Input piece is not valid");
                } else if (square.size() < 2 || !isInt(square.substr(1)) || !board.isSquareOnBoard(std::stoi(square.substr(1)), square.front())) {
                    outputError("Input square is not valid on board");
                } else {

                    PieceType pieceType = stringToPieceType(piece);
                    Color pieceColor = std::isupper(piece.front()) ? Color::WHITE : Color::BLACK;
                    PieceDirection pieceDirection = pieceColor == Color::WHITE ? PieceDirection::NORTH : PieceDirection::SOUTH;

                    if (tokens.size() == 3) {
                        board.setPosition(std::stoi(square.substr(1)), square.front(), pieceColor, pieceType, pieceDirection, false);
                        notifyObservers();
                    } else if (tokens.size() == 4) {
                        if (isValidPieceDirection(tokens[3])) {
                            board.setPosition(std::stoi(square.substr(1)), square.front(), pieceColor, pieceType, stringToPieceDirection(tokens[3]), false);
                            notifyObservers();
                        } else {
                            outputError("Invalid direction");
                        }
                    } else {
                        outputError("Too many input tokens on line");
                    }
                }
            }
            
        } else if (firstToken == "-") {
            if (isInMainMenu()) {
                outputError("Can't clear piece in main menu");
            } else if (isGameActive()) {
                outputError("Can't clear piece when game is active");
            } else if (tokens.size() == 1) {
                outputError("Not enough input tokens on line, must specify square to remove piece from");
            } else if (tokens.size() > 2) {
                outputError("Too many input tokens on line");
            } else {
                std::string square = tokens[1];
                if (square.size() < 2 || !board.isSquareOnBoard(!isInt(square.substr(1)) || std::stoi(square.substr(1)), square.front())) {
                    outputError("Input square is not valid on board");
                } else if (board.clearPosition(std::stoi(square.substr(1)), square.front())) {
                    notifyObservers();
                }
            }
            
        } else if (firstToken == "=") {
            if (isInMainMenu()) {
                outputError("Can't set first turn in main menu");
            } else if (isGameActive()) {
                outputError("Can't set first turn when game is active");
            } else if (tokens.size() == 1) {
                outputError("Not enough input tokens on line, must specify color to go first");
            } else if (tokens.size() > 2) {
                outputError("Too many input tokens on line");
            } else if (!isValidColor(tokens[1])) {
                outputError("Must specify color to go first");
            } else if (stringToColor(tokens[1]) == Color::BLACK) {
                currentTurn = 1;
                notifyObservers();
            } else {
                currentTurn = 0;
                notifyObservers();
            }
            
        } else if (firstToken == "done") {
            if (isInMainMenu()) {
                outputError("Can't leave setup mode in main menu");
            } else if (isGameActive()) {
                outputError("Can't leave setup mode when game is active");
            } else if (tokens.size() >= 2) {
                outputError("Too many input tokens on line");
            } else {
                if (!board.isBoardInValidState()) {
                    outputError("Board is not in valid state, can't leave setup mode");
                } else {
                    gameState = GameState::MAIN_MENU;
                    notifyObservers();
                }
            }

        } else if (firstToken == "basic") {

            if (isInMainMenu()) {
                outputError("Can't apply basic setup in main menu");
            } else if (isGameActive()) {
                outputError("Can't apply basic setup when game is active");
            } else if (tokens.size() > 1) {
                outputError("Too many input tokens on line");
            } else {
                board.applyStandardSetup();
                notifyObservers();
            }

        } else if (firstToken == "set") {
            if (isInMainMenu()) {
                outputError("Can't set board size in main menu");
            } else if (isGameActive()) {
                outputError("Can't set board size when game is active");
            } else if (tokens.size() >= 1 && tokens.size() < 3) {
                outputError("Not enough input tokens on line, expecting set rows cols");
            } else if (tokens.size() > 3) {
                outputError("Too many input tokens on line");
            } else {
                if (!isInt(tokens[1]) || std::stoi(tokens[1]) < 8 || std::stoi(tokens[1]) > 26) {
                    outputError("Rows must be between 8 and 26 inclusive");
                } else if (!isInt(tokens[2]) || std::stoi(tokens[2]) < 8 || std::stoi(tokens[2]) > 26) {
                    outputError("Cols must be between 8 and 26 inclusive");
                } else {
                    board.setBoardSize(std::stoi(tokens[1]), std::stoi(tokens[2]));
                    notifyObservers();
                }
            }
        } else if (tokens.size() != 0) {
            outputError("Invalid command entered");
        }
    }

    if (std::cin.eof()) {
        out << "Exiting Game Interface" << std::endl;
        out << std::endl;
        out << "Final Score:" << std::endl;
        out << "White: " << std::get<1>(std::get<0>(players)) << std::endl;
        out << "Black: " << std::get<1>(std::get<1>(players)) << std::endl;
    }
    
}
