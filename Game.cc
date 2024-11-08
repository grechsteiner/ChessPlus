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


Game::Game(std::unique_ptr<ChessBoard> chessBoard, std::unique_ptr<CommandRetriever> commandRetriever, std::unique_ptr<IllegalCommandReporter> illegalCommandReporter) :
    chessBoard(std::move(chessBoard)), commandRetriever(std::move(commandRetriever)), illegalCommandReporter(std::move(illegalCommandReporter)) {
    applyStandardSetup();
}

void Game::outputError(std::string const &errorMessage) const {
    illegalCommandReporter->reportIllegalCommand(errorMessage);
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

std::tuple<ChessBoard const&, const std::tuple<PlayerTuple, PlayerTuple>&, int> Game::getSetupState() const {
    return std::make_tuple(std::ref(*chessBoard), std::cref(players), currentTurn);
}

std::tuple<ChessBoard const&, const std::tuple<PlayerTuple, PlayerTuple>&, int, bool> Game::getActiveGameState() const {
    return std::make_tuple(std::ref(*chessBoard), std::cref(players), currentTurn, showingStandardOpenings);
}

void Game::resetComputerPlayers() {
    std::get<2>(std::get<0>(players)) = nullptr;
    std::get<2>(std::get<1>(players)) = nullptr;
}

void Game::applyStalematePoints() {
    std::get<1>(std::get<0>(players)) += 0.5;
    std::get<1>(std::get<1>(players)) += 0.5;
}
    
void Game::applyWinPoints(Team team) {
    if (team == Team::TEAM_ONE) {
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
    while (commandRetriever->isCommandAvailable()) {
        inputLine = commandRetriever->retrieveCommand();

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

                static std::regex const pattern("^(human|computer[1-5])$");

                if (!std::regex_match(tokens[1], pattern) || !std::regex_match(tokens[2], pattern)) {
                    outputError("Invalid syntax, expecting (human|computer[1-4])");
                } else {
                    std::get<2>(std::get<0>(players)) = (tokens[1] == "human") ? nullptr : ComputerPlayerFactory::createComputerPlayer(stringToComputerPlayerLevel(std::string(1, tokens[1].back())), *chessBoard, Team::TEAM_ONE);
                    std::get<2>(std::get<1>(players)) = (tokens[2] == "human") ? nullptr : ComputerPlayerFactory::createComputerPlayer(stringToComputerPlayerLevel(std::string(1, tokens[2].back())), *chessBoard, Team::TEAM_TWO);
                    setGameState(GameState::GAME_ACTIVE);
                    notifyObservers();
                    
                    if (chessBoard->isInStaleMate(Team::TEAM_ONE) || chessBoard->isInStaleMate(Team::TEAM_TWO)) {
                        applyStalematePoints();
                        chessBoard->clearBoard();
                        // board.setBoardSize(8, 8);
                        applyStandardSetup();

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
                chessBoard->clearBoard();
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
                        std::unique_ptr<BoardMove> compMove = std::get<2>(getPlayerWithTurn(currentTurn))->generateMove();
                        chessBoard->makeMove(compMove);
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
                        if (UserSquare::isValidUserSquare(fromSquare) && UserSquare::isValidUserSquare(toSquare) && isValidPieceType(promotionPiece)) {

                            BoardSquare fromBoardSquare = createBoardSquare(UserSquare(fromSquare), chessBoard->getNumRows(), chessBoard->getNumCols());
                            BoardSquare toBoardSquare = createBoardSquare(UserSquare(toSquare), chessBoard->getNumRows(), chessBoard->getNumCols());
                            std::optional<PieceType> promotion = promotionPiece == "" ? std::nullopt : std::make_optional(stringToPieceType(promotionPiece));
                            std::optional<std::unique_ptr<BoardMove>> boardMove = chessBoard->createBoardMove(fromBoardSquare, toBoardSquare, promotion);

                            // Nullptr if invalid move
                            if (boardMove.has_value()) {
                                chessBoard->makeMove(boardMove.value());
                                incrementTurn();
                                moveMade = true;
                            } else {
                                outputError("Invalid board move, try again ");
                            }
                            
                        } else {
                            outputError("Invalid user move, try again");
                        }
                    }
                } 

                if (moveMade) {
                    notifyObservers();

                    if (chessBoard->isInCheckMate(Team::TEAM_ONE) || chessBoard->isInCheckMate(Team::TEAM_TWO) || chessBoard->isInStaleMate(Team::TEAM_ONE) || chessBoard->isInStaleMate(Team::TEAM_TWO)) {
                        
                        // Update points
                        if (chessBoard->isInStaleMate(Team::TEAM_ONE) || chessBoard->isInStaleMate(Team::TEAM_TWO)) {
                            applyStalematePoints();
                        } else {
                            Team winner = currentTurn == 0 ? Team::TEAM_TWO : Team::TEAM_ONE;
                            applyWinPoints(winner);
                        }

                        // Reset board for next run through
                        chessBoard->clearBoard();
                        // board.setBoardSize(8, 8);
                        applyStandardSetup();

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
                    applyWinPoints(Team::TEAM_TWO);
                } else {
                    applyWinPoints(Team::TEAM_ONE);
                }

                // Reset board for next run through
                chessBoard->clearBoard();
                // board.setBoardSize(8, 8);
                applyStandardSetup();

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
                if (chessBoard->undoMove()) {
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
                } else if (!UserSquare::isValidUserSquare(square) || !chessBoard->isSquareOnBoard(createBoardSquare(UserSquare(square), chessBoard->getNumRows(), chessBoard->getNumCols()))) {
                    outputError("Input square is not valid on board");
                } else {

                    PieceType pieceType = stringToPieceType(piece);
                    Team team = std::isupper(piece.front()) ? Team::TEAM_ONE : Team::TEAM_TWO;
                    PieceDirection pieceDirection = team == Team::TEAM_ONE ? PieceDirection::NORTH : PieceDirection::SOUTH;

                    BoardSquare boardSquare = createBoardSquare(UserSquare(square), chessBoard->getNumRows(), chessBoard->getNumCols());
                    if (tokens.size() == 3) {
                        chessBoard->setPosition(boardSquare, PieceData(pieceType, PieceLevel::BASIC, team, pieceDirection, false));
                        notifyObservers();
                    } else if (tokens.size() == 4) {
                        if (isValidPieceDirection(tokens[3])) {
                            chessBoard->setPosition(boardSquare, PieceData(pieceType, PieceLevel::BASIC, team, stringToPieceDirection(tokens[3]), false));
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
                if (!UserSquare::isValidUserSquare(square) || chessBoard->isSquareOnBoard(createBoardSquare(UserSquare(square), chessBoard->getNumRows(), chessBoard->getNumCols()))) {
                    outputError("Input square is not valid on board");
                } else if (chessBoard->clearPosition(createBoardSquare(UserSquare(square), chessBoard->getNumRows(), chessBoard->getNumCols()))) {
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
            } else if (stringToColor(tokens[1]) == Team::TEAM_TWO) {
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
                if (!isBoardInProperSetup()) {
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
                applyStandardSetup();
                notifyObservers();
            }

        /*
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
        */
        } else if (tokens.size() != 0) {
            outputError("Invalid command entered");
        }
    }
    
}

void Game::applyStandardSetup() {
    chessBoard->clearBoard();
 
    int startCol = (chessBoard->getNumCols() - 8) / 2;

    int topRow = 0;                     // Black
    int bottomRow = chessBoard->getNumRows() - 1;    // White
    for (int col = startCol; col < startCol + 8; ++col) {
        
        // Normal Pieces
        PieceType pieceType;
        if (col == startCol || col == startCol + 8 - 1) {
            // Rook
            pieceType = PieceType::ROOK;
        } else if (col == startCol + 1 || col == startCol + 8 - 2) {
            // Knight
            pieceType = PieceType::KNIGHT;
        } else if (col == startCol + 2 || col == startCol + 8 - 3) {
            // Bishop
            pieceType = PieceType::BISHOP;
        } else if (col == startCol + 3) {
            // Queen
            pieceType = PieceType::QUEEN;
        } else if (col == startCol + 4) {
            // King
            pieceType = PieceType::KING;
        }
        BoardSquare blackPieceSquare(topRow, col);
        BoardSquare whitePieceSquare(bottomRow, col);
        chessBoard->setPosition(blackPieceSquare, PieceData(pieceType, PieceLevel::BASIC, Team::TEAM_TWO, PieceDirection::SOUTH, false));               // Black
        chessBoard->setPosition(whitePieceSquare, PieceData(pieceType, PieceLevel::BASIC, Team::TEAM_ONE, PieceDirection::NORTH, false));            // White

        // Pawns
        BoardSquare blackPawnSquare(topRow + 1, col);
        BoardSquare whitePawnSquare(bottomRow - 1, col);
        chessBoard->setPosition(blackPawnSquare, PieceData(PieceType::PAWN, PieceLevel::BASIC, Team::TEAM_TWO, PieceDirection::SOUTH, false));     // Black
        chessBoard->setPosition(whitePawnSquare, PieceData(PieceType::PAWN, PieceLevel::BASIC, Team::TEAM_ONE, PieceDirection::NORTH, false));  // Black
    }
}

bool Game::isBoardInProperSetup() const {
    int whiteKingCount = 0;
    int blackKingCount = 0;

    int topRow = 0;
    int bottomRow = chessBoard->getNumRows() - 1;

    for (ChessBoard::BoardSquareIterator it = chessBoard->begin(); it != chessBoard->end(); ++it) {
        std::optional<PieceData> pieceData = chessBoard->getPieceDataAt(*it);
        if (pieceData.has_value()) {
            if (pieceData.value().pieceType == PieceType::KING) {
                Team team = pieceData.value().team;
                if (chessBoard->isSquareAttacked(*it, team)) {
                    return false;
                }
                if (team == chessBoard->getTeamOne()) {
                    whiteKingCount++;
                } else if (team == chessBoard->getTeamTwo()) {
                    blackKingCount++;
                }
            }

            if (pieceData.value().pieceType == PieceType::PAWN && ((*it).boardRow == topRow || (*it).boardRow == bottomRow)) {
                return false;
            }
        }
        
    }

    return (whiteKingCount != 1 || blackKingCount != 1) ? false : true;
}

/*
bool Board::setBoardSizeImpl(int newNumRows, int newNumCols) { 
    static int const maxNumRows = 26;
    static int const maxNumCols = 26;
    static int const minNumRows = 4;
    static int const minNumCols = 8;
    if (newNumRows >= minNumRows && newNumRows <= maxNumRows && newNumCols >= minNumCols && newNumCols <= maxNumCols) {
        int oldNumRows = getNumRows();
        int oldNumCols = getNumCols();

        // Create new grid
        std::vector<std::vector<std::unique_ptr<Piece>>> newGrid(newNumRows);
        for (int boardRow = 0; boardRow < newNumRows; ++boardRow) {
            newGrid[boardRow].resize(newNumCols);
        }
        initializeBoard(newGrid);

        for (BoardSquare const &boardSquare : allBoardSquares()) {
            int oldRow = boardSquare.boardRow;
            int oldCol = boardSquare.boardCol;
            int newRow = oldRow + (newNumRows - oldNumRows);
            int newCol = oldCol;
            if (newRow >= 0 && newRow < newNumRows && newCol >= 0 && newCol < newNumCols) {
                newGrid[newRow][newCol] = std::move(grid[oldRow][oldCol]);
            }
        }

        // Replace the old grid with the new grid
        grid = std::move(newGrid);
    
        return true;
    } else {
        return false;
    }
}
*/
