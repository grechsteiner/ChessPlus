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

Player const& Game::getPlayer(Team team) const {
    if (team == chessBoard->getTeamOne()) {
        return players.first;
    } else {
        return players.second;
    }
}

void Game::switchTurn() {
    if (currentTurn == chessBoard->getTeamOne()) {
        currentTurn = chessBoard->getTeamTwo();
    } else {
        currentTurn = chessBoard->getTeamOne();
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

std::optional<std::string> Game::matchToOptionalString(std::smatch const& matches, int index) const {
    return index < matches.size() && matches[index].matched
        ? std::make_optional<std::string>(matches[index].str())
        : std::nullopt; 
}

State Game::getState() const {
    return State(gameState, chessBoard, players, currentTurn);
}

void Game::runGame() {
    notifyObservers();

    while (commandRetriever->isCommandAvailable()) {
        std::string input = commandRetriever->retrieveCommand();
        std::smatch matches;

        // Enter Setup Mode
        if (std::regex_match(input, matches, std::regex(R"(\s*setup\s*)", std::regex_constants::icase))) {
            processEnterSetupModeCommand();

        // Place Piece
        } else if (std::regex_match(input, matches, std::regex(R"(\s*+\s*([a-z]+[1-9][0-9]*)\s*([a-zA-Z])\s*(basic|advanced)?\s*(north|south|west|east)?\s*)", std::regex_constants::icase))) {
            processPlacePieceCommand(matches[1].str(), matches[2].str(), matchToOptionalString(matches, 3), matchToOptionalString(matches, 4));

        // Remove Piece
        } else if (std::regex_match(input, matches, std::regex(R"(\s*-\s*([a-z]+[1-9][0-9]*)\s*)", std::regex_constants::icase))) {
            processRemovePieceCommand(matches[1].str());
            
        // Swap First Turn
        } else if (std::regex_match(input, matches, std::regex(R"(\s*swap\s*)", std::regex_constants::icase))) {
            processSwapFirstTurnCommand();

        // Apply Standard Setup
        } else if (std::regex_match(input, matches, std::regex(R"(\s*standard\s*)", std::regex_constants::icase))) {
            processApplyStandardSetupCommand();

        // Set Board Size   
        } else if (std::regex_match(input, matches, std::regex(R"(\s*set\s*([1-9][0-9]*)\s*([1-9][0-9]*))", std::regex_constants::icase))) {
            processSetBoardSizeCommand(matches[1].str(), matches[2].str());

        // Exit Setup Mode  
        } else if (std::regex_match(input, matches, std::regex(R"(\s*done\s*)", std::regex_constants::icase))) {
            processExitSetupModeCommand();

        // Start Game
        } else if (std::regex_match(input, matches, std::regex(R"(\s*game\s*(human|computer[1-5])\s*(human|computer[1-5])\s*)", std::regex_constants::icase))) {
            processStartGameCommand(matches[1].str(), matches[2].str());

        // Make Move
        } else if (std::regex_match(input, matches, std::regex(R"(\s*move\s*(?:([a-z]+[1-9][0-9]*)\s*([a-z]+[1-9][0-9]*)\s*([a-z]?)\s*)?)", std::regex_constants::icase))) {
            if (matches[1].matched) {
                processMakeHumanMoveCommand(MoveInputDetails(matches[1].str(), matches[2].str(), matchToOptionalString(matches, 3)));
            } else {
                processMakeComputerMoveCommand();
            }

        // Undo Move
        } else if (std::regex_match(input, matches, std::regex(R"(\s*undo\s*)", std::regex_constants::icase))) {
            processUndoMoveCommand();

        // Resign Game
        } else if (std::regex_match(input, matches, std::regex(R"(\s*resign\s*)", std::regex_constants::icase))) {
            processResignGameCommand();

        // No Matching Commands
        } else {
            reportIllegalCommand("No valid command entered");
        }
    }
}

void Game::processEnterSetupModeCommand() {
    switch (gameState) {
        case GameState::GAME_ACTIVE:
            reportIllegalCommand("Can't enter setup mode when game is active");
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
    return;
}

void Game::processPlacePieceCommand(std::string const &boardSquareStr, std::string const &pieceTypeStr, std::optional<std::string> const &pieceLevelStr, std::optional<std::string> const &pieceDirectionStr) {
    switch (gameState) {
        case GameState::MAIN_MENU:
            reportIllegalCommand("Can't place piece in main menu");
            break;
        case GameState::GAME_ACTIVE:
            reportIllegalCommand("Can't place piece when game is active");
            break;
        case GameState::SETUP:
            std::optional<BoardSquare> boardSquare = BoardSquare::createBoardSquare(boardSquareStr, chessBoard->getNumRows(), chessBoard->getNumCols());
            if (!boardSquare.has_value() || !chessBoard->isSquareOnBoard(boardSquare.value())) {
                reportIllegalCommand("Input square is not valid");
                break;
            }

            std::optional<PieceType> pieceType = Utilities::stringToPieceType(pieceTypeStr);
            if (!pieceType.has_value()) {
                reportIllegalCommand("Input piece is not valid");
                break;
            }
            
            Team team = std::isupper(pieceTypeStr.front()) ? chessBoard->getTeamOne() : chessBoard->getTeamTwo();

            PieceLevel pieceLevel;
            if (pieceLevelStr.has_value()) {
                if (Utilities::stringToPieceLevel(pieceLevelStr.value()).has_value()) {
                    pieceLevel = Utilities::stringToPieceLevel(pieceLevelStr.value()).value();
                } else {
                    reportIllegalCommand("Input piece level is not valid");
                    break;
                }
            } else {
                pieceLevel = PieceLevel::BASIC;
            }

            PieceDirection pieceDirection;
            if (pieceDirectionStr.has_value()) {
                if (Utilities::stringToPieceDirection(pieceDirectionStr.value()).has_value()) {
                    pieceDirection = Utilities::stringToPieceDirection(pieceDirectionStr.value()).value();
                } else {
                    reportIllegalCommand("Input piece direction is not valid");
                    break;
                }
            } else {
                pieceDirection = team == chessBoard->getTeamOne()
                    ? PieceDirection::NORTH
                    : PieceDirection::SOUTH;
            }
            
            chessBoard->setPosition(boardSquare.value(), PieceData(pieceType.value(), pieceLevel, team, pieceDirection, false));
            notifyObservers();
            break;
    }    
    return;
}

void Game::processRemovePieceCommand(std::string const &boardSquareStr) {
    switch (gameState) {
        case GameState::MAIN_MENU:
            reportIllegalCommand("Can't remove piece in main menu");
            break;
        case GameState::GAME_ACTIVE:
            reportIllegalCommand("Can't remove piece when game is active");
            break;
        case GameState::SETUP:
            std::optional<BoardSquare> boardSquare = BoardSquare::createBoardSquare(boardSquareStr, chessBoard->getNumRows(), chessBoard->getNumCols());
            if (!boardSquare.has_value() || !chessBoard->isSquareOnBoard(boardSquare.value())) {
                reportIllegalCommand("Input square is not valid");
                break;
            } 
            
            if (chessBoard->clearPosition(boardSquare.value())) {
                notifyObservers();
            }
            break;
    }
    return;
}

void Game::processSwapFirstTurnCommand() {
    switch (gameState) {
        case GameState::MAIN_MENU:
            reportIllegalCommand("Can't swap first turn in main menu");
            break;
        case GameState::GAME_ACTIVE:
            reportIllegalCommand("Can't swap first turn when game is active");
            break;
        case GameState::SETUP:
            switchTurn();
            notifyObservers();
            break;
    }
    return;
}

void Game::processApplyStandardSetupCommand() {
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
    return;
}
void Game::processSetBoardSizeCommand(std::string const &numRowsStr, std::string const &numColsStr) {
    switch (gameState) {
        case GameState::MAIN_MENU:
            reportIllegalCommand("Can't set board size in main menu");
            break;
        case GameState::GAME_ACTIVE:
            reportIllegalCommand("Can't set board size when game is active");
            break;
        case GameState::SETUP:
            int numRows = std::stoi(numRowsStr);
            int numCols = std::stoi(numColsStr);

            if (numRows < 1 || numRows > 26) {
                reportIllegalCommand("Number of rows must be between 1 and 26 inclusive");
                break;
            } else if (numCols < 8 || numCols > 26) {
                reportIllegalCommand("Number of cols must be between 1 and 26 inclusive");
                break;
            }

            chessBoard = ChessBoardFactory::createChessBoard(numRows, numCols);
            notifyObservers();
            break;
    }
    return;
}

void Game::processExitSetupModeCommand() {
    switch (gameState) {
        case GameState::MAIN_MENU:
            reportIllegalCommand("Can't exit setup mode in main menu");
            break;
        case GameState::GAME_ACTIVE:
            reportIllegalCommand("Can't exit setup mode when game is active");
            break;
        case GameState::SETUP:
            if (!ChessBoardUtilities::isBoardInLegalSetupState(chessBoard)) {
                reportIllegalCommand("Can't exit setup mode when board is not in valid state");
                break;
            }

            setGameState(GameState::MAIN_MENU);
            notifyObservers();
            break;
    }
    return;
}

void Game::processStartGameCommand(std::string const &teamOneStr, std::string const &teamTwoStr) {
    switch (gameState) {
        case GameState::GAME_ACTIVE:
            reportIllegalCommand("Can't start game when game is active");
            break;
        case GameState::SETUP:
            reportIllegalCommand("Can't start game in setup mode");
            break;
        case GameState::MAIN_MENU:
            Team teamOne = chessBoard->getTeamOne();
            Team teamTwo = chessBoard->getTeamTwo();

            Player playerOne = Utilities::stringToPlayerType(teamOneStr).value() == PlayerType::HUMAN 
                ? PlayerFactory::createHumanPlayer(teamOne)
                : PlayerFactory::createComputerPlayer(teamOne, ComputerPlayerFactory::createComputerPlayer(Utilities::stringToComputerPlayerLevel(std::string(1, teamOneStr.back())).value(), teamOne));
            Player playerTwo = Utilities::stringToPlayerType(teamTwoStr).value() == PlayerType::HUMAN 
                ? PlayerFactory::createHumanPlayer(teamTwo)
                : PlayerFactory::createComputerPlayer(teamTwo, ComputerPlayerFactory::createComputerPlayer(Utilities::stringToComputerPlayerLevel(std::string(1, teamTwoStr.back())).value(), teamTwo));

            players = std::make_pair(std::move(playerOne), std::move(playerTwo));
            setGameState(GameState::GAME_ACTIVE);
            notifyObservers();
            break;  
    }
    return;
}

void Game::processMakeHumanMoveCommand(MoveInputDetails const &moveInputDetails) {
    switch (gameState) {
        case GameState::MAIN_MENU:
            reportIllegalCommand("Can't make move in main menu");
            break;
        case GameState::SETUP:
            reportIllegalCommand("Can't make move in setup mode");
            break;
        case GameState::GAME_ACTIVE:
            if (getPlayer(currentTurn).getPlayerType() == PlayerType::COMPUTER) {
                reportIllegalCommand("The current player is a computer, don't specify move details for computer players");
                break;
            }
            
            std::optional<BoardSquare> fromSquare = BoardSquare::createBoardSquare(moveInputDetails.fromSquareStr, chessBoard->getNumRows(), chessBoard->getNumCols());
            std::optional<BoardSquare> toSquare = BoardSquare::createBoardSquare(moveInputDetails.toSquareStr, chessBoard->getNumRows(), chessBoard->getNumCols());
            if (!fromSquare.has_value() || !toSquare.has_value() || !chessBoard->isSquareOnBoard(fromSquare.value()) || !chessBoard->isSquareOnBoard(toSquare.value())) {
                reportIllegalCommand("Input squares are not valid");
                break;
            }

            std::optional<PieceType> promotionPieceType;
            if (moveInputDetails.promotionPieceTypeStr.has_value()) {
                if (Utilities::stringToPieceType(moveInputDetails.promotionPieceTypeStr.value()).has_value()) {
                    promotionPieceType = Utilities::stringToPieceType(moveInputDetails.promotionPieceTypeStr.value()).value();
                } else {
                    reportIllegalCommand("Input promotion piece is not valid");
                    break;
                } 
            } else {
                promotionPieceType = std::nullopt;
            }

            std::optional<std::unique_ptr<BoardMove>> boardMove = chessBoard->createBoardMove(fromSquare.value(), toSquare.value(), promotionPieceType);
            if (!boardMove.has_value()) {
                reportIllegalCommand("Input move is not valid");
                break;
            }
            chessBoard->makeMove(boardMove.value());
            switchTurn();

            notifyObservers();
            if (ChessBoardUtilities::isGameOver(chessBoard)) {
                resetGame();
                notifyObservers();
            }
            break;
    }
    return;
}

void Game::processMakeComputerMoveCommand() {
    switch (gameState) {
        case GameState::MAIN_MENU:
            reportIllegalCommand("Can't make move in main menu");
            break;
        case GameState::SETUP:
            reportIllegalCommand("Can't make move in setup mode");
            break;
        case GameState::GAME_ACTIVE:
            if (getPlayer(currentTurn).getPlayerType() == PlayerType::HUMAN) {
                reportIllegalCommand("The current player is a human, you must specify move details for human players");
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
            break;
    }
    return;
}

void Game::processUndoMoveCommand() {
    switch (gameState) {
        case GameState::MAIN_MENU:
            reportIllegalCommand("Can't undo a move in main menu");
            break;
        case GameState::SETUP:
            reportIllegalCommand("Can't undo a move in setup mode");
            break;
        case GameState::GAME_ACTIVE:
            if (chessBoard->undoMove()) {
                switchTurn();
                notifyObservers();
            } else {
                reportIllegalCommand("There are no moves to undo");
            }
            break;
    }
    return;
}

void Game::processResignGameCommand() {
    switch (gameState) {
        case GameState::MAIN_MENU:
            reportIllegalCommand("Can't resign game in main menu");
            break;
        case GameState::SETUP:
            reportIllegalCommand("Can't resign game in setup mode");
            break;
        case GameState::GAME_ACTIVE:
            resetGame();
            notifyObservers();
            break;
    }  
    return; 
}
