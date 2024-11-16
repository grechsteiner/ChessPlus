// TextObserver.cc

#include <iostream>

#include "TextObserver.h"
#include "Game.h"
#include "State.h"
#include "ChessBoardUtilities.h"


TextObserver::TextObserver(Game *game, std::ostream &out) : Cloneable<Observer, TextObserver>(), game(game), out(out) {
    game->attach(this);
}

TextObserver::TextObserver(TextObserver const &other) : 
    Cloneable<Observer, TextObserver>(), game(other.game), out(other.out) {
    game->attach(this);       
}

TextObserver::TextObserver(TextObserver &&other) noexcept : 
    Cloneable<Observer, TextObserver>(), game(other.game), out(other.out) {
    game->attach(this);
}

TextObserver::~TextObserver() {
    game->detach(this);
}

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
}

void TextObserver::displayMainMenu() {
    outputLine(std::u32string(UR"(╔═════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╗)"));
    outputLine(std::u32string(UR"(║                                    ________                      ____  __                                           ║)"));
    outputLine(std::u32string(UR"(║                                   / ____/ /_  ___  __________   / __ \/ /_  _______                                 ║)"));
    outputLine(std::u32string(UR"(║                                  / /   / __ \/ _ \/ ___/ ___/  / /_/ / / / / / ___/                                 ║)"));
    outputLine(std::u32string(UR"(║                                 / /___/ / / /  __(__  |__  )  / ____/ / /_/ (__  )                                  ║)"));
    outputLine(std::u32string(UR"(║                                 \____/_/ /_/\___/____/____/  /_/   /_/\__,_/____/                                   ║)"));
    outputLine(std::u32string(UR"(║                                                                                                                     ║)"));
    outputLine(std::u32string(UR"(║     __             ______                                     ____            __         __       _                 ║)"));
    outputLine(std::u32string(UR"(║    / /_  __  __   / ____/________  __  ___________  ____     / __ \___  _____/ /_  _____/ /____  (_)___  ___  _____ ║)"));
    outputLine(std::u32string(UR"(║   / __ \/ / / /  / / __/ ___/ __ `/ / / / ___/ __ \/ __ \   / /_/ / _ \/ ___/ __ \/ ___/ __/ _ \/ / __ \/ _ \/ ___/ ║)"));
    outputLine(std::u32string(UR"(║  / /_/ / /_/ /  / /_/ / /  / /_/ / /_/ (__  ) /_/ / / / /  / _, _/  __/ /__/ / / (__  ) /_/  __/ / / / /  __/ /     ║)"));
    outputLine(std::u32string(UR"(║ /_.___/\__, /   \____/_/   \__,_/\__, /____/\____/_/ /_/  /_/ |_|\___/\___/_/ /_/____/\__/\___/_/_/ /_/\___/_/      ║)"));
    outputLine(std::u32string(UR"(║       /____/                    /____/                                                                              ║)"));
    outputLine(std::u32string(UR"(╚═════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╝)")); 
}

void TextObserver::displaySetupMode(std::unique_ptr<ChessBoard> const &chessBoard, std::pair<Player, Player> const &players, Team currentTurn) {
    outputLine(std::u32string(UR"(╔═════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╗)"));

    std::vector<std::u32string> chessBoardDisplay = buildChessBoard(chessBoard);
    std::vector<std::u32string> boardDataDisplay = buildBoardDataText(chessBoard, currentTurn);
    std::vector<std::u32string> setupTextDisplay = buildSetupText();

    for (int row = 0; row < chessBoardDisplay.size(); ++row) {
        std::u32string currentLine = std::u32string(UR"(║ )");
        int followingSpaces = 119;
        followingSpaces -= currentLine.length() * 2;

        // Need to account for embedded color codes in the board row string, and the row number
        currentLine += chessBoardDisplay[row];
        followingSpaces -= chessBoard->getNumRows() >= 10 
            ? 2
            : 1;
        followingSpaces -= chessBoard->getNumCols();    // Num cols
        followingSpaces -= 2;                           // Boarder of board
        
        currentLine += std::u32string(UR"( )");
        followingSpaces -= 1;
        if (row < boardDataDisplay.size()) {
            currentLine += boardDataDisplay[row];
            followingSpaces -= boardDataDisplay[row].length();
        }

        if (row < setupTextDisplay.size()) {
            followingSpaces -= setupTextDisplay[row].length();
        }
        
        currentLine += std::u32string(followingSpaces, char32_t(U' '));

        if (row < setupTextDisplay.size()) {
            currentLine += setupTextDisplay[row];
        }
        currentLine += std::u32string(UR"( ║)");

        outputLine(currentLine);
    }

    outputLine(std::u32string(UR"(╚═════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╝)")); 
}

void TextObserver::displayGame(std::unique_ptr<ChessBoard> const &chessBoard, std::pair<Player, Player> const &players, Team currentTurn) {
    outputLine(std::u32string(UR"(╔═════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╗)"));

    std::vector<std::u32string> chessBoardDisplay = buildChessBoard(chessBoard);
    std::vector<std::u32string> boardDataDisplay = buildBoardDataText(chessBoard, currentTurn);
    std::vector<std::u32string> boardStatusDisplay = buildBoardStatusText(chessBoard, currentTurn);
    std::vector<std::u32string> gameOnTextDisplay = buildGameOnText();

    for (int row = 0; row < chessBoardDisplay.size(); ++row) {
        std::u32string currentLine = std::u32string(UR"(║ )");
        int followingSpaces = 119;
        followingSpaces -= currentLine.length() * 2;

        // Need to account for embedded color codes in the board row string, and the row number
        currentLine += chessBoardDisplay[row];
        followingSpaces -= chessBoard->getNumRows() >= 10 
            ? 2
            : 1;
        followingSpaces -= chessBoard->getNumCols();    // Num cols
        followingSpaces -= 2;                           // Boarder of board
        
        currentLine += std::u32string(UR"( )");
        followingSpaces -= 1;
        if (row < boardDataDisplay.size()) {
            currentLine += boardDataDisplay[row];
            followingSpaces -= boardDataDisplay[row].length();
        }
        if (row < boardStatusDisplay.size()) {
            currentLine += boardStatusDisplay[row];
            followingSpaces -= boardStatusDisplay[row].length();
        }

        if (row < gameOnTextDisplay.size()) {
            followingSpaces -= gameOnTextDisplay[row].length();
        }
        
        currentLine += std::u32string(followingSpaces, char32_t(U' '));

        if (row < gameOnTextDisplay.size()) {
            currentLine += gameOnTextDisplay[row];
        }
        currentLine += std::u32string(UR"( ║)");

        outputLine(currentLine);
    }

    outputLine(std::u32string(UR"(╚═════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╝)")); 
}

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

std::vector<std::u32string> TextObserver::buildGameOnText() {
    return std::vector<std::u32string> {
        std::u32string(UR"(   ______                       ____        __)"),
        std::u32string(UR"(  / ____/___  ____ ___  ___    / __ \____  / /)"),
        std::u32string(UR"( / / __/ __ `/ __ `__ \/ _ \  / / / / __ \/ / )"),
        std::u32string(UR"(/ /_/ / /_/ / / / / / /  __/ / /_/ / / / /_/  )"),
        std::u32string(UR"(\____/\__,_/_/ /_/ /_/\___/  \____/_/ /_(_)   )")                                         
    };
}

std::vector<std::u32string> TextObserver::buildChessBoard(std::unique_ptr<ChessBoard> const &chessBoard) {
    int numRows = chessBoard->getNumRows();
    int numCols = chessBoard->getNumCols();
    bool extraSpaceForNumber = chessBoard->getNumRows() >= 10;

    std::vector<std::u32string> chessBoardDisplay;

    std::u32string topBoarder = extraSpaceForNumber 
        ? std::u32string(UR"(  ╔)") 
        : std::u32string(UR"( ╔)"); 
    topBoarder += std::u32string(numCols, char32_t(U'═'));
    topBoarder += std::u32string(UR"(╗)");
    chessBoardDisplay.emplace_back(std::move(topBoarder));

    for (int row = 0; row < numRows; ++row) {
        std::u32string currentLine = extraSpaceForNumber && chessBoard->getNumRows() - row < 10 
            ? std::u32string(UR"( )") 
            : std::u32string(UR"()");
        currentLine += stringToU32(std::to_string(numRows - row));
        currentLine += std::u32string(UR"(║)");

        for (int col = 0; col < numCols; ++col) {
            BoardSquare boardSquare(row, col);

            std::optional<PieceInfo> pieceInfo = chessBoard->getPieceInfoAt(boardSquare);
            if (pieceInfo.has_value()) {
                std::u32string pieceImage = stringToU32(pieceInfo.value().image);
                Team team = chessBoard->getPieceDataAt(boardSquare).value().team;

                static std::u32string const white = std::u32string(U"\033[90m");
                static std::u32string const black = std::u32string(U"\033[30m");
                static std::u32string const reset = std::u32string(U"\033[0m");
                
                currentLine += team == chessBoard->getTeamOne()
                    ? white
                    : black;
                currentLine += pieceImage;
                currentLine += reset;
            } else {
                currentLine += std::u32string(UR"( )");
            }
        }
        currentLine += std::u32string(UR"(║)");;
        chessBoardDisplay.emplace_back(std::move(currentLine));
    }

    std::u32string bottomBoarder = extraSpaceForNumber 
        ? std::u32string(UR"(  ╚)") 
        : std::u32string(UR"( ╚)"); 
    bottomBoarder += std::u32string(numCols, char32_t(U'═'));
    bottomBoarder += std::u32string(UR"(╝)");
    chessBoardDisplay.emplace_back(std::move(bottomBoarder));

    static std::u32string const alphabet = std::u32string(UR"(abcdefghijklmnopqrstuvwxyz)");
    std::u32string columnLabels = extraSpaceForNumber ? std::u32string(UR"(   )") : std::u32string(UR"(  )");
    columnLabels += alphabet.substr(0, numCols);
    columnLabels += std::u32string(UR"( )");
    chessBoardDisplay.emplace_back(std::move(columnLabels));

    return chessBoardDisplay;
}

std::vector<std::u32string> TextObserver::buildBoardDataText(std::unique_ptr<ChessBoard> const &chessBoard, Team currentTurn) {
    std::u32string turn = std::u32string(UR"(● Turn: )");
    turn += currentTurn == chessBoard->getTeamOne()
        ? std::u32string(UR"(White)")
        : std::u32string(UR"(Black)");

    std::u32string remaining = std::u32string(UR"(● Pieces:)");
    std::u32string whiteRemaining = std::u32string(UR"(  ◈ White: )") + stringToU32(std::to_string(ChessBoardUtilities::getNumPiecesOnBoard(chessBoard, chessBoard->getTeamOne())));
    std::u32string blackRemaining = std::u32string(UR"(  ◈ Black: )") + stringToU32(std::to_string(ChessBoardUtilities::getNumPiecesOnBoard(chessBoard, chessBoard->getTeamTwo())));

    return std::vector<std::u32string> {
        std::u32string(UR"()"),
        std::move(turn),
        std::move(remaining),
        std::move(whiteRemaining),
        std::move(blackRemaining)
    };
}

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

    return std::vector<std::u32string> {
        std::move(statusString)
    };
}

std::u32string TextObserver::stringToU32(std::string const &str) const {
    return boost::locale::conv::utf_to_utf<char32_t>(str);
}

std::string TextObserver::u32ToString(std::u32string const &str) const {
    return boost::locale::conv::utf_to_utf<char>(str);
}

void TextObserver::outputLine(std::u32string const &line) const {
    out << u32ToString(line) << std::endl;
}
