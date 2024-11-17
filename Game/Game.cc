// Game.cc

#include "Game.h"

#include <cctype>
#include <memory>
#include <optional>
#include <regex>
#include <string>
#include <utility>

#include "BoardMove.h"
#include "BoardSquare.h"
#include "ChessBoard.h"
#include "ChessBoardFactory.h"
#include "ChessBoardUtilities.h"
#include "CommandRetriever.h"
#include "ComputerPlayer.h"
#include "ComputerPlayerFactory.h"
#include "Constants.h"
#include "IllegalCommandReporter.h"
#include "MoveInputDetails.h"
#include "Player.h"
#include "PlayerFactory.h"
#include "State.h"
#include "Subject.h"
#include "Utilities.h"


/*
 * Basic ctor
 */
Game::Game(std::unique_ptr<CommandRetriever> const &commandRetriever, std::unique_ptr<IllegalCommandReporter> const &illegalCommandReporter) :
    Subject(),
    gameState(GameState::MAIN_MENU),
    chessBoard(ChessBoardFactory::createChessBoard(8, 8)),
    players(std::make_pair(
        PlayerFactory::createHumanPlayer(chessBoard->getTeamOne()),
        PlayerFactory::createHumanPlayer(chessBoard->getTeamTwo())
    )),
    currentTurn(chessBoard->getTeamOne()),
    commandRetriever(commandRetriever->clone()), 
    illegalCommandReporter(illegalCommandReporter->clone()) {
        
    ChessBoardUtilities::applyStandardSetup(chessBoard, PieceLevel::BASIC);
}

/*
 * Copy ctor
 */
Game::Game(Game const &other) :
    Subject(other),
    gameState(other.gameState),
    chessBoard(other.chessBoard->clone()),
    players(other.players),
    currentTurn(other.currentTurn),
    commandRetriever(other.commandRetriever->clone()),
    illegalCommandReporter(other.illegalCommandReporter->clone()) { }

/*
 * Move ctor
 */
Game::Game(Game &&other) noexcept :
    Subject(std::move(other)),
    gameState(other.gameState),
    chessBoard(std::move(other.chessBoard)),
    players(std::move(other.players)),
    currentTurn(other.currentTurn),
    commandRetriever(std::move(other.commandRetriever)),
    illegalCommandReporter(std::move(other.illegalCommandReporter)) { }

/*
 * Copy assignment
 */
Game& Game::operator=(Game &other) {
    if (this != &other) {
        Subject::operator=(other);

        gameState = other.gameState;
        chessBoard = other.chessBoard->clone();
        players = std::make_pair(
            Player(getPlayer(chessBoard->getTeamOne())), 
            Player(getPlayer(chessBoard->getTeamTwo()))
        );
        currentTurn = other.currentTurn;
        commandRetriever = other.commandRetriever->clone();
        illegalCommandReporter = other.illegalCommandReporter->clone();
    }
    return *this;
}

/*
 * Move assignment
 */
Game& Game::operator=(Game &&other) noexcept {
    if (this != &other) {
        Subject::operator=(std::move(other));
        
        gameState = other.gameState;
        chessBoard = std::move(other.chessBoard);
        players = std::move(other.players);
        currentTurn = other.currentTurn;
        commandRetriever = std::move(other.commandRetriever);
        illegalCommandReporter = std::move(other.illegalCommandReporter);  
    }
    return *this;
}

/*
 * Return reference to the Player associated with the Team arugment
 */
Player const& Game::getPlayer(Team team) const {
    if (team == chessBoard->getTeamOne()) {
        return players.first;
    } else {
        return players.second;
    }
}

/*
 * Switch the current turn
 */
void Game::switchTurn() {
    if (currentTurn == chessBoard->getTeamOne()) {
        currentTurn = chessBoard->getTeamTwo();
    } else {
        currentTurn = chessBoard->getTeamOne();
    }
}

/*
 * Reset the state of the game
 */
void Game::resetGame() {
    setGameState(GameState::MAIN_MENU);
    currentTurn = chessBoard->getTeamOne();
    chessBoard = ChessBoardFactory::createChessBoard(8, 8);
    ChessBoardUtilities::applyStandardSetup(chessBoard, PieceLevel::BASIC);
    players = std::make_pair(
        PlayerFactory::createHumanPlayer(chessBoard->getTeamOne()),
        PlayerFactory::createHumanPlayer(chessBoard->getTeamTwo())
    );
}

/*
 * Set the GameState
 */
void Game::setGameState(GameState newGameState) {
    gameState = newGameState;
}

/*
 * Issue an illegal command report to the reporter
 */
void Game::reportIllegalCommand(std::string const &message) const {
    illegalCommandReporter->reportIllegalCommand(message);
}

/*
 * Convert potential match in regex to an optional string
 */
std::optional<std::string> Game::matchToOptionalString(std::smatch const& matches, int index) const {
    return index < matches.size() && matches[index].matched && !matches[index].str().empty()
        ? std::make_optional<std::string>(matches[index].str())
        : std::nullopt; 
}

/*
 * Observer Pattern: Return current State of game
 */
State Game::getState() const {
    return State(gameState, chessBoard, players, currentTurn);
}

/*
 * Run the game logic
 */
void Game::runGame() {
    notifyObservers();

    while (commandRetriever->isCommandAvailable()) {
        std::optional<std::string> potentialInput = commandRetriever->retrieveCommand();

        if (potentialInput.has_value()) {
            std::string input = potentialInput.value();
            std::smatch matches;

            // Enter Setup Mode
            if (std::regex_match(input, matches, std::regex(R"(\s*setup\s*)", std::regex_constants::icase))) {
                processEnterSetupModeCommand();

            // Place Piece
            } else if (std::regex_match(input, matches, std::regex(R"(\s*\+\s*([a-z]+[1-9][0-9]*)\s*([a-zA-Z])\s*(basic|advanced)?\s*(north|south|west|east)?\s*)", std::regex_constants::icase))) {
                processPlacePieceCommand(matches[1].str(), matches[2].str(), matchToOptionalString(matches, 3), matchToOptionalString(matches, 4));

            // Remove Piece
            } else if (std::regex_match(input, matches, std::regex(R"(\s*-\s*([a-z]+[1-9][0-9]*)\s*)", std::regex_constants::icase))) {
                processRemovePieceCommand(matches[1].str());
                
            // Swap First Turn
            } else if (std::regex_match(input, matches, std::regex(R"(\s*swap\s*)", std::regex_constants::icase))) {
                processSwapFirstTurnCommand();

            // Apply Standard Setup
            } else if (std::regex_match(input, matches, std::regex(R"(\s*standard\s*(basic|advanced)?\s*)", std::regex_constants::icase))) {
                processApplyStandardSetupCommand(matchToOptionalString(matches, 1));

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

            // Redo Move
            } else if (std::regex_match(input, matches, std::regex(R"(\s*redo\s*)", std::regex_constants::icase))) {
                processRedoMoveCommand();

            // Resign Game
            } else if (std::regex_match(input, matches, std::regex(R"(\s*resign\s*)", std::regex_constants::icase))) {
                processResignGameCommand();

            // No Matching Commands
            } else {
                reportIllegalCommand("Invalid command entered");
            }
        }
    }
}

/*
 * Process an "Enter Startup Mode" command
 */
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

/*
 * Process a "Place Piece" command
 */
void Game::processPlacePieceCommand(std::string const &boardSquareStr, std::string const &pieceTypeStr, std::optional<std::string> const &pieceLevelStr, std::optional<std::string> const &pieceDirectionStr) {
    switch (gameState) {
        case GameState::MAIN_MENU:
            reportIllegalCommand("Can't place piece in main menu");
            break;
        case GameState::GAME_ACTIVE:
            reportIllegalCommand("Can't place piece when game is active");
            break;
        case GameState::SETUP:
            // BoardSquare
            std::optional<BoardSquare> boardSquare = BoardSquare::createBoardSquare(boardSquareStr, chessBoard->getNumRowsOnBoard(), chessBoard->getNumColsOnBoard());
            if (!boardSquare.has_value() || !chessBoard->isSquareOnBoard(boardSquare.value())) {
                reportIllegalCommand("Input square is not valid");
                break;
            }

            // PieceType
            std::optional<PieceType> pieceType = Utilities::stringToPieceType(pieceTypeStr);
            if (!pieceType.has_value()) {
                reportIllegalCommand("Input piece is not valid");
                break;
            }
            
            // Team
            Team team = std::isupper(pieceTypeStr.front()) ? chessBoard->getTeamOne() : chessBoard->getTeamTwo();

            // PieceLevel
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

            // PieceDirection
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
            
            // Place the piece
            chessBoard->setPosition(boardSquare.value(), PieceData(pieceType.value(), pieceLevel, team, pieceDirection, false));
            notifyObservers();
            break;
    }    
    return;
}

/*
 * Process a "Remove Piece" command
 */
void Game::processRemovePieceCommand(std::string const &boardSquareStr) {
    switch (gameState) {
        case GameState::MAIN_MENU:
            reportIllegalCommand("Can't remove piece in main menu");
            break;
        case GameState::GAME_ACTIVE:
            reportIllegalCommand("Can't remove piece when game is active");
            break;
        case GameState::SETUP:
            // BoardSquare
            std::optional<BoardSquare> boardSquare = BoardSquare::createBoardSquare(boardSquareStr, chessBoard->getNumRowsOnBoard(), chessBoard->getNumColsOnBoard());
            if (!boardSquare.has_value() || !chessBoard->isSquareOnBoard(boardSquare.value())) {
                reportIllegalCommand("Input square is not valid");
                break;
            } 
            
            // Remove the piece
            chessBoard->clearPosition(boardSquare.value());
            notifyObservers();
            break;
    }
    return;
}

/*
 * Process a "Swap Turn" command
 */
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

/*
 * Process an "Apply Standard Setup" command
 */
void Game::processApplyStandardSetupCommand(std::optional<std::string> const &pieceLevelStr) {
    switch (gameState) {
        case GameState::MAIN_MENU:
            reportIllegalCommand("Can't apply standard setup in main menu");
            break;
        case GameState::GAME_ACTIVE:
            reportIllegalCommand("Can't apply standard setup when game is active");
            break;
        case GameState::SETUP:
            std::unique_ptr<ChessBoard> newChessBoard = ChessBoardFactory::createChessBoard(chessBoard->getNumRowsOnBoard(), chessBoard->getNumColsOnBoard());
            PieceLevel pieceLevel = pieceLevelStr.has_value()
                ? Utilities::stringToPieceLevel(pieceLevelStr.value()).value()
                : PieceLevel::BASIC;
            if (!ChessBoardUtilities::applyStandardSetup(newChessBoard, pieceLevel)) {
                reportIllegalCommand("Board is too small to apply standard setup");
                break;
            }

            chessBoard = std::move(newChessBoard);
            notifyObservers();
            break;
    }
    return;
}

/*
 * Process a "Set Board Size" command
 */
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

            if (numRows < 4 || numRows > 26) {
                reportIllegalCommand("Number of rows must be between 4 and 26 inclusive");
                break;
            } else if (numCols < 4 || numCols > 26) {
                reportIllegalCommand("Number of cols must be between 4 and 26 inclusive");
                break;
            }

            chessBoard = ChessBoardFactory::createChessBoard(numRows, numCols);
            notifyObservers();
            break;
    }
    return;
}

/*
 * Process an "Exit Setup Mode" command
 */
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

/*
 * Process a "Start Game" command
 */
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

/*
 * Process a "Make Human Move" command
 */
void Game::processMakeHumanMoveCommand(MoveInputDetails const &moveInputDetails) {
    switch (gameState) {
        case GameState::MAIN_MENU:
            reportIllegalCommand("Can't make move in main menu");
            break;
        case GameState::SETUP:
            reportIllegalCommand("Can't make move in setup mode");
            break;
        case GameState::GAME_ACTIVE:
            // Check current turn
            if (getPlayer(currentTurn).getPlayerType() == PlayerType::COMPUTER) {
                reportIllegalCommand("The current player is a computer, don't specify move details for computer players");
                break;
            }
            
            // BoardSqaures
            std::optional<BoardSquare> fromSquare = BoardSquare::createBoardSquare(moveInputDetails.fromSquareStr, chessBoard->getNumRowsOnBoard(), chessBoard->getNumColsOnBoard());
            std::optional<BoardSquare> toSquare = BoardSquare::createBoardSquare(moveInputDetails.toSquareStr, chessBoard->getNumRowsOnBoard(), chessBoard->getNumColsOnBoard());
            if (!fromSquare.has_value() || !toSquare.has_value() || !chessBoard->isSquareOnBoard(fromSquare.value()) || !chessBoard->isSquareOnBoard(toSquare.value())) {
                reportIllegalCommand("Input squares are not valid");
                break;
            }

            // Promotion PieceType
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

            // The BoardMove itself
            std::optional<std::unique_ptr<BoardMove>> boardMove = chessBoard->createBoardMove(fromSquare.value(), toSquare.value(), promotionPieceType);
            if (!boardMove.has_value()) {
                reportIllegalCommand("Input move is not valid");
                break;
            }

            // Apply the move
            chessBoard->makeMove(boardMove.value());
            switchTurn();

            notifyObservers();
            if (ChessBoardUtilities::isGameOver(chessBoard, currentTurn)) {
                resetGame();
                notifyObservers();
            }
            break;
    }
    return;
}

/*
 * Process a "Make Computer Move" command
 */
void Game::processMakeComputerMoveCommand() {
    switch (gameState) {
        case GameState::MAIN_MENU:
            reportIllegalCommand("Can't make move in main menu");
            break;
        case GameState::SETUP:
            reportIllegalCommand("Can't make move in setup mode");
            break;
        case GameState::GAME_ACTIVE:
            // Check current turn
            if (getPlayer(currentTurn).getPlayerType() == PlayerType::HUMAN) {
                reportIllegalCommand("The current player is a human, you must specify move details for human players");
                break;
            }
                
            // Gauranteed to get valid move
            std::unique_ptr<BoardMove> computerMove = getPlayer(currentTurn).getComputerPlayer()->generateMove(chessBoard);

            // Applys the move
            chessBoard->makeMove(computerMove);
            switchTurn();

            notifyObservers();
            if (ChessBoardUtilities::isGameOver(chessBoard, currentTurn)) {
                resetGame();
                notifyObservers();
            }
            break;
    }
    return;
}

/*
 * Process an "Undo Move" command
 */
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
                break;
            }
            break;
    }
    return;
}

/*
 * Process a "Redo Move" command
 */
void Game::processRedoMoveCommand() {
    switch (gameState) {
        case GameState::MAIN_MENU:
            reportIllegalCommand("Can't redo a move in main menu");
            break;
        case GameState::SETUP:
            reportIllegalCommand("Can't redo a move in setup mode");
            break;
        case GameState::GAME_ACTIVE:
            if (chessBoard->redoMove()) {
                switchTurn();
                notifyObservers();
            } else {
                reportIllegalCommand("There are no moves to redo");
                break;
            }
            break;
    }
    return;
}

/*
 * Process a "Resign Game" command
 */
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
