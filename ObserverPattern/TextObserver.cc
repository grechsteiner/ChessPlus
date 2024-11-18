// TextObserver.cc

#include "TextObserver.h"

#include <boost/locale.hpp>

#include <iostream>
#include <memory>
#include <string>
#include <utility>

#include "ChessBoard.h"
#include "Constants.h"
#include "Game.h"
#include "Observer.h"
#include "Player.h"


/*
 * Basic ctor
 */
TextObserver::TextObserver(Game *game, std::ostream &out) : 
    Observer(), game(game), out(out) {

    game->attach(this);
}

/*
 * Copy ctor
 */
TextObserver::TextObserver(TextObserver const &other) : 
    Observer(other), game(other.game), out(other.out) {

    game->attach(this);       
}

/*
 * Move ctor
 */
TextObserver::TextObserver(TextObserver &&other) noexcept : 
    Observer(std::move(other)), game(other.game), out(other.out) {

    game->attach(this);
}

/*
 * Dtor
 */
TextObserver::~TextObserver() {
    game->detach(this);
}

/*
 * Logic that runs when a TestObserver instance is notified by a Subject
 */
void TextObserver::notifyImpl() {
    State const &state = game->getState();
    switch (state.gameState) {
        case GameState::MAIN_MENU:
            displayMainMenu();
            break;
        case GameState::SETUP:
            displaySetupMode(state.chessBoard, state.players, state.currentTurn);
            break;
        case GameState::GAME_ACTIVE:
            displayGame(state.chessBoard, state.players, state.currentTurn);
            break;
    }
    return;
}

/*
 * Display the Main Menu
 */
void TextObserver::displayMainMenu() {
    std::vector<std::u32string> mainMenuTextDisplay = buildMainMenuText();
    for (std::u32string const &str: mainMenuTextDisplay) {
        outputLine(str);
    }
}

/*
 * Display Setup Mode
 */
void TextObserver::displaySetupMode(std::unique_ptr<ChessBoard> const &chessBoard, std::pair<Player, Player> const &players, Team currentTurn) {
    outputLine(std::u32string(UR"(╔═════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╗)"));

    std::vector<std::u32string> chessBoardDisplay = buildChessBoard(chessBoard);
    std::vector<std::u32string> boardDataDisplay = buildBoardDataText(chessBoard, currentTurn);
    std::vector<std::u32string> setupTextDisplay = buildSetupText();

    // Iterate through each row of the ChessBoard display
    for (int row = 0; row < chessBoardDisplay.size(); ++row) {

        // Initialize the current line with the left boarder of the frame
        std::u32string currentLine = std::u32string(UR"(║ )");

        // Number of space characters to show between the last ChessBoard data text and the State Label
        int followingSpaces = 119;
        followingSpaces -= currentLine.length() * 2;

        // ChessBoard text
        currentLine += chessBoardDisplay[row];

        // Need to account for embedded color codes in the board row string, as well as the row label
        followingSpaces -= chessBoard->getNumRowsOnBoard() >= 10 
            ? 2
            : 1;
        followingSpaces -= chessBoard->getNumColsOnBoard();     // Number of cols on ChessBoard
        followingSpaces -= 2;                                   // Boarder of ChessBoard
        
        // Display a space character separate the ChessBoard and the BoardData
        currentLine += std::u32string(UR"( )");
        followingSpaces -= 1;

        // BoardData text
        if (row < boardDataDisplay.size()) {
            currentLine += boardDataDisplay[row];
            followingSpaces -= boardDataDisplay[row].length();
        }

        // Check length of State Label to determine number of space characters
        if (row < setupTextDisplay.size()) {
            followingSpaces -= setupTextDisplay[row].length();
        }
        
        // Display space characters
        currentLine += std::u32string(followingSpaces, char32_t(U' '));

        // State Label text
        if (row < setupTextDisplay.size()) {
            currentLine += setupTextDisplay[row];
        }

        // Right board of the frame
        currentLine += std::u32string(UR"( ║)");

        // Output the current line
        outputLine(currentLine);
    }

    outputLine(std::u32string(UR"(╚═════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╝)")); 
}

/*
 * Display the Active Game
 */
void TextObserver::displayGame(std::unique_ptr<ChessBoard> const &chessBoard, std::pair<Player, Player> const &players, Team currentTurn) {
    outputLine(std::u32string(UR"(╔═════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╗)"));

    std::vector<std::u32string> chessBoardDisplay = buildChessBoard(chessBoard);
    std::vector<std::u32string> boardDataDisplay = buildBoardDataText(chessBoard, currentTurn);
    std::vector<std::u32string> boardStatusDisplay = buildBoardStatusText(chessBoard, currentTurn);
    std::vector<std::u32string> gameOnTextDisplay = buildGameOnText();

    // Iterate through each row of the ChessBoard display
    for (int row = 0; row < chessBoardDisplay.size(); ++row) {
        
        // Initialize the current line with the left boarder of the frame
        std::u32string currentLine = std::u32string(UR"(║ )");

        // Number of space characters to show between the last ChessBoard data text and the State Label
        int followingSpaces = 119;
        followingSpaces -= currentLine.length() * 2;

        // ChessBoard text
        currentLine += chessBoardDisplay[row];

        // Need to account for embedded color codes in the board row string, as well as the row label
        followingSpaces -= chessBoard->getNumRowsOnBoard() >= 10 
            ? 2
            : 1;
        followingSpaces -= chessBoard->getNumColsOnBoard();     // Number of cols on ChessBoard
        followingSpaces -= 2;                                   // Boarder of ChessBoard
        
        // Display a space character separate the ChessBoard and the BoardData
        currentLine += std::u32string(UR"( )");
        followingSpaces -= 1;

        // BoardData text
        if (row < boardDataDisplay.size()) {
            currentLine += boardDataDisplay[row];
            followingSpaces -= boardDataDisplay[row].length();
        }

        // BoardStatus text
        if (row < boardStatusDisplay.size()) {
            currentLine += boardStatusDisplay[row];
            followingSpaces -= boardStatusDisplay[row].length();
        }

        // Check length of State Label to determine number of space characters
        if (row < gameOnTextDisplay.size()) {
            followingSpaces -= gameOnTextDisplay[row].length();
        }
        
        // Display space characters
        currentLine += std::u32string(followingSpaces, char32_t(U' '));

        // State Label text
        if (row < gameOnTextDisplay.size()) {
            currentLine += gameOnTextDisplay[row];
        }

        // Right board of the frame
        currentLine += std::u32string(UR"( ║)");

        // Output the current line
        outputLine(currentLine);
    }

    outputLine(std::u32string(UR"(╚═════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╝)")); 
}

/*
 * Build the text to display on the Main Menu
 */
std::vector<std::u32string> TextObserver::buildMainMenuText() {
    return std::vector<std::u32string> {
        std::u32string(UR"(╔═════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╗)"),
        std::u32string(UR"(║                                    ________                      ____  __                                           ║)"),
        std::u32string(UR"(║                                   / ____/ /_  ___  __________   / __ \/ /_  _______                                 ║)"),
        std::u32string(UR"(║                                  / /   / __ \/ _ \/ ___/ ___/  / /_/ / / / / / ___/                                 ║)"),
        std::u32string(UR"(║                                 / /___/ / / /  __(__  |__  )  / ____/ / /_/ (__  )                                  ║)"),
        std::u32string(UR"(║                                 \____/_/ /_/\___/____/____/  /_/   /_/\__,_/____/                                   ║)"),
        std::u32string(UR"(║                                                                                                                     ║)"),
        std::u32string(UR"(║     __             ______                                     ____            __         __       _                 ║)"),
        std::u32string(UR"(║    / /_  __  __   / ____/________  __  ___________  ____     / __ \___  _____/ /_  _____/ /____  (_)___  ___  _____ ║)"),
        std::u32string(UR"(║   / __ \/ / / /  / / __/ ___/ __ `/ / / / ___/ __ \/ __ \   / /_/ / _ \/ ___/ __ \/ ___/ __/ _ \/ / __ \/ _ \/ ___/ ║)"),
        std::u32string(UR"(║  / /_/ / /_/ /  / /_/ / /  / /_/ / /_/ (__  ) /_/ / / / /  / _, _/  __/ /__/ / / (__  ) /_/  __/ / / / /  __/ /     ║)"),
        std::u32string(UR"(║ /_.___/\__, /   \____/_/   \__,_/\__, /____/\____/_/ /_/  /_/ |_|\___/\___/_/ /_/____/\__/\___/_/_/ /_/\___/_/      ║)"),
        std::u32string(UR"(║       /____/                    /____/                                                                              ║)"),
        std::u32string(UR"(╚═════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╝)")
    };
}

/*
 * Build the text to display in Setup Mode
 */
std::vector<std::u32string> TextObserver::buildSetupText() {
    return std::vector<std::u32string> {
        std::u32string(UR"(   _____      __            )"),       
        std::u32string(UR"(  / ___/___  / /___  ______ )"),
        std::u32string(UR"(  \__ \/ _ \/ __/ / / / __ \)"),
        std::u32string(UR"( ___/ /  __/ /_/ /_/ / /_/ /)"),
        std::u32string(UR"(/____/\___/\__/\__,_/ .___/ )"),
        std::u32string(UR"(                   /_/      )")
    };
}

/*
 * Build the text to display during an Active Game
 */
std::vector<std::u32string> TextObserver::buildGameOnText() {
    return std::vector<std::u32string> {
        std::u32string(UR"(   ______                       ____        __)"),
        std::u32string(UR"(  / ____/___  ____ ___  ___    / __ \____  / /)"),
        std::u32string(UR"( / / __/ __ `/ __ `__ \/ _ \  / / / / __ \/ / )"),
        std::u32string(UR"(/ /_/ / /_/ / / / / / /  __/ / /_/ / / / /_/  )"),
        std::u32string(UR"(\____/\__,_/_/ /_/ /_/\___/  \____/_/ /_(_)   )")                                         
    };
}

/*
 * Build the ChessBoard text
 */
std::vector<std::u32string> TextObserver::buildChessBoard(std::unique_ptr<ChessBoard> const &chessBoard) {
    int numRows = chessBoard->getNumRowsOnBoard();
    int numCols = chessBoard->getNumColsOnBoard();

    // Determines the amount of spacing prior to the row label
    bool extraSpaceForNumber = chessBoard->getNumRowsOnBoard() >= 10;

    // Accumulate the rows to display
    std::vector<std::u32string> chessBoardDisplay;

    // Build the top boarder of the ChessBoard
    std::u32string topBoarder = extraSpaceForNumber 
        ? std::u32string(UR"(  ╔)") 
        : std::u32string(UR"( ╔)"); 
    topBoarder += std::u32string(numCols, char32_t(U'═'));
    topBoarder += std::u32string(UR"(╗)");
    chessBoardDisplay.emplace_back(std::move(topBoarder));

    // Build each row of the ChessBoard, including the boarder
    for (int row = 0; row < numRows; ++row) {

        // Left boarder and row label
        std::u32string currentLine = extraSpaceForNumber && chessBoard->getNumRowsOnBoard() - row < 10 
            ? std::u32string(UR"( )") 
            : std::u32string(UR"()");
        currentLine += stringToU32(std::to_string(numRows - row));
        currentLine += std::u32string(UR"(║)");

        for (int col = 0; col < numCols; ++col) {
            BoardSquare boardSquare(row, col);

            // Check if a Piece exists at the current BoardSquare
            std::optional<PieceInfo> pieceInfo = chessBoard->getPieceInfoAt(boardSquare);
            if (pieceInfo.has_value()) {
                char32_t pieceImage = pieceInfo.value().image;
                Team team = chessBoard->getPieceDataAt(boardSquare).value().team;

                static std::u32string const white = std::u32string(U"\033[90m");
                static std::u32string const black = std::u32string(U"\033[30m");
                static std::u32string const reset = std::u32string(U"\033[0m");
                
                // Encode Piece coloring into the string
                currentLine += team == chessBoard->getTeamOne()
                    ? white
                    : black;
                currentLine += pieceImage;
                currentLine += reset;
            } else {
                currentLine += std::u32string(UR"( )");
            }
        }

        // Right boarder, and append to accumulated rows
        currentLine += std::u32string(UR"(║)");;
        chessBoardDisplay.emplace_back(std::move(currentLine));
    }

    // Build the bottom boarder of the ChessBoard
    std::u32string bottomBoarder = extraSpaceForNumber 
        ? std::u32string(UR"(  ╚)") 
        : std::u32string(UR"( ╚)"); 
    bottomBoarder += std::u32string(numCols, char32_t(U'═'));
    bottomBoarder += std::u32string(UR"(╝)");
    chessBoardDisplay.emplace_back(std::move(bottomBoarder));

    // Build the column labels
    static std::u32string const alphabet = std::u32string(UR"(abcdefghijklmnopqrstuvwxyz)");
    std::u32string columnLabels = extraSpaceForNumber ? std::u32string(UR"(   )") : std::u32string(UR"(  )");
    columnLabels += alphabet.substr(0, numCols);
    columnLabels += std::u32string(UR"( )");
    chessBoardDisplay.emplace_back(std::move(columnLabels));

    return chessBoardDisplay;
}

/*
 * Build the ChessBoard data text
 * - Current Turn
 * - Pieces remaining per Team
 */
std::vector<std::u32string> TextObserver::buildBoardDataText(std::unique_ptr<ChessBoard> const &chessBoard, Team currentTurn) {

    // Current turn
    std::u32string turn = std::u32string(UR"(● Turn: )");
    turn += currentTurn == chessBoard->getTeamOne()
        ? std::u32string(UR"(White)")
        : std::u32string(UR"(Black)");

    // Piece remaining per Team
    std::u32string remaining = std::u32string(UR"(● Pieces:)");
    std::u32string whiteRemaining = std::u32string(UR"(  ◈ White: )") + stringToU32(std::to_string(ChessBoardUtilities::getNumPiecesOnBoard(chessBoard, chessBoard->getTeamOne())));
    std::u32string blackRemaining = std::u32string(UR"(  ◈ Black: )") + stringToU32(std::to_string(ChessBoardUtilities::getNumPiecesOnBoard(chessBoard, chessBoard->getTeamTwo())));

    // Build the output
    return std::vector<std::u32string> {
        std::u32string(UR"()"),
        std::move(turn),
        std::move(remaining),
        std::move(whiteRemaining),
        std::move(blackRemaining)
    };
}

/*
 * Build the ChessBoard status text (Checkmate, Check, Stalemate, etc)
 */
std::vector<std::u32string> TextObserver::buildBoardStatusText(std::unique_ptr<ChessBoard> const &chessBoard, Team currentTurn) {
    std::u32string statusString;
    Team teamOne = chessBoard->getTeamOne();
    Team teamTwo = chessBoard->getTeamTwo();
    if (currentTurn == teamOne) { 
        if (chessBoard->isInCheckMate(teamOne)) {
            statusString = std::u32string(UR"(● Checkmate! Black wins!)");
        } else if (chessBoard->isInCheck(teamOne)) {
            statusString = std::u32string(UR"(● White is in check)");
        } else if (chessBoard->isInStaleMate(teamOne)) {
            statusString = std::u32string(UR"(● Stalemate!)");
        } else {
            statusString = std::u32string(UR"()");
        }

    } else {
        if (chessBoard->isInCheckMate(teamTwo)) {
            statusString = std::u32string(UR"(● Checkmate! White wins!)");
        } else if (chessBoard->isInCheck(teamTwo)) {
            statusString = std::u32string(UR"(● Black is in check)");
        } else if (chessBoard->isInStaleMate(teamTwo)) {
            statusString = std::u32string(UR"(● Stalemate!)");
        } else {
            statusString = std::u32string(UR"()");
        }
    }

    // Build the output
    return std::vector<std::u32string> {
        std::move(statusString)
    };
}

/*
 * Convert std::string to std::u32string
 */
std::u32string TextObserver::stringToU32(std::string const &str) const {
    return boost::locale::conv::utf_to_utf<char32_t>(str);
}

/*
 * Convert std::u32string to std::string
 */
std::string TextObserver::u32ToString(std::u32string const &str) const {
    return boost::locale::conv::utf_to_utf<char>(str);
}

/*
 * Output a line of text
 */
void TextObserver::outputLine(std::u32string const &line) const {
    out << u32ToString(line) << std::endl;
}
