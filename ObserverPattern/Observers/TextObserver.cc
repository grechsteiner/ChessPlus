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

    // displayMainMenu();
    
    // GameState gameState = std::get<4>(state);


    /*
    if (gameState == GameState::MAIN_MENU) {
        out << "+---------+" << std::endl;
        out << "|Main Menu|" << std::endl;
        out << "+---------+" << std::endl;
    } else if (gameState == GameState::SETUP) {

        const ChessBoard& chessBoard = std::get<0>(state);


        out << "+";
        for (int col = 0; col < chessBoard.getNumCols(); ++col) {
            out << "-";
        }
        out << "-----+" << std::endl;

        out << "|  Setup";

        for (int i = 0; i < chessBoard.getNumCols() - 3; ++i) {
            out << " ";
        }
        out << " |" << std::endl;
        
        printBoard(std::get<0>(state), std::get<2>(state));

        out << "+";
        for (int col = 0; col < chessBoard.getNumCols(); ++col) {
            out << "-";
        }
        out << "-----+" << std::endl;

    } else {
        

        const ChessBoard& chessBoard = std::get<0>(state);

        out << "+";
        for (int col = 0; col < chessBoard.getNumCols(); ++col) {
            out << "-";
        }
        out << "-----+" << std::endl;

        out << "|  Active Game";

        for (int i = 0; i < chessBoard.getNumCols() - 8; ++i) {
            out << " ";
        }
        out << "|" << std::endl;
        
        
        printBoard(std::get<0>(state), std::get<2>(state));
        
        Team teamOne = chessBoard.getTeamOne();
        Team teamTwo = chessBoard.getTeamTwo();
        if (std::get<2>(state) == 0) { 
            if (chessBoard.isInCheckMate(teamOne)) {
                out << "Checkmate! Black wins!" << std::endl;
            } else if (chessBoard.isInCheck(teamOne)) {
                out << "White is in check" << std::endl;
            } else if (chessBoard.isInStaleMate(teamOne)) {
                out << "Stalemate!" << std::endl;
            }

        } else {
            if (chessBoard.isInCheckMate(teamTwo)) {
                out << "Checkmate! White wins!" << std::endl;
            } else if (chessBoard.isInCheck(teamTwo)) {
                out << "Black is in check" << std::endl;
            } else if (chessBoard.isInStaleMate(teamTwo)) {
                out << "Stalemate!" << std::endl;
            }
        }

        out << "+";
        for (int col = 0; col < chessBoard.getNumCols(); ++col) {
            out << "-";
        }
        out << "-----+" << std::endl;


        
        if (std::get<3>(state) == true) {
            std::vector<std::pair<std::string, std::string>> openings = board.getMatchingOpenings();
            for (size_t i = 0; i < openings.size(); ++i) {
                out << "Name: " << openings[i].first << std::endl;
            }
        }
        
    }
    */
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

    std::vector<std::string> chessBoardDisplay = buildChessBoard(chessBoard);
    std::vector<std::string> boardDataDisplay = buildBoardDataText(chessBoard, currentTurn);
    std::vector<std::string> setupTextDisplay = buildSetupText();

    for (int row = 0; row < chessBoardDisplay.size(); ++row) {
        int followingSpaces = 117 - 1 - (chessBoard->getNumRows() >= 10 ? 2 : 1) - 1 - chessBoard->getNumCols() - 1 - 1;

        out << "║ ";
        out << chessBoardDisplay[row];
        out << " ";

        if (row < boardDataDisplay.size()) {
            followingSpaces -= boardDataDisplay[row].size();
            if (!boardDataDisplay[row].empty()) {
                followingSpaces += 2;
            }
            out << boardDataDisplay[row];
        }

        if (row < setupTextDisplay.size()) {
            followingSpaces -= 29;
        }

        out << std::string(followingSpaces, ' ');

        if (row < setupTextDisplay.size()) {
            out << setupTextDisplay[row];
        }

        out << "║" << std::endl;
    }

    out << "╚═════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╝" << std::endl;
}

void TextObserver::displayGame(std::unique_ptr<ChessBoard> const &chessBoard, std::pair<Player, Player> const &players, Team currentTurn) {

}

std::vector<std::string> TextObserver::buildChessBoard(std::unique_ptr<ChessBoard> const &chessBoard) {
    int numRows = chessBoard->getNumRows();
    int numCols = chessBoard->getNumCols();

    bool extraSpaceForNumber = chessBoard->getNumRows() >= 10;

    std::vector<std::string> chessBoardDisplay;

    std::string topBoarder = extraSpaceForNumber ? "  ╔" : " ╔";
    for (int col = 0; col < numCols; ++col) {
        topBoarder += "═";
    }
    topBoarder += "╗";
    chessBoardDisplay.emplace_back(topBoarder);

    for (int row = 0; row < numRows; ++row) {
        std::string currentLine = extraSpaceForNumber && chessBoard->getNumRows() - row < 10 ? " " : "";
        currentLine += std::to_string(numRows - row) + "║";

        for (int col = 0; col < numCols; ++col) {
            BoardSquare boardSquare(row, col);
            if (chessBoard->getPieceInfoAt(boardSquare)) {
                std::string pieceImage = chessBoard->getPieceInfoAt(boardSquare).value().image;
                Team team = chessBoard->getPieceDataAt(boardSquare).value().team;

                static std::string const white = "\033[90m";
                static std::string const black = "\033[30m";
                static std::string const reset = "\033[0m";
                std::string stringColor = team == chessBoard->getTeamOne()
                    ? white
                    : black;

                currentLine += (stringColor + pieceImage + reset);
            } else {
                currentLine += " ";
            }
        }
        currentLine += "║";
        chessBoardDisplay.emplace_back(currentLine);
    }
    
    std::string bottomBoarder = extraSpaceForNumber ? "  ╚" : " ╚";
    for (int col = 0; col < numCols; ++col) {
        bottomBoarder += "═";
    }
    bottomBoarder += "╝";
    chessBoardDisplay.emplace_back(bottomBoarder);


    static std::string const alphabet = "abcdefghijklmnopqrstuvwxyz";
    std::string colLabels = extraSpaceForNumber ? "   " : "  ";
    colLabels += alphabet.substr(0, numCols) + " ";
    chessBoardDisplay.emplace_back(colLabels);

    return chessBoardDisplay;
}


std::vector<std::string> TextObserver::buildSetupText() {
    return std::vector<std::string> {
        "   _____      __             ",       
        "  / ___/___  / /___  ______  ",
        "  \\__ \\/ _ \\/ __/ / / / __ \\ ",
        " ___/ /  __/ /_/ /_/ / /_/ / ",
        "/____/\\___/\\__/\\__,_/ .___/  ",
        "                   /_/       "
    };
}

std::vector<std::string> TextObserver::buildBoardDataText(std::unique_ptr<ChessBoard> const &chessBoard, Team currentTurn) {
    std::string turn = "● Turn: ";
    turn += currentTurn == chessBoard->getTeamOne()
        ? "White"
        : "Black";

    std::string remaining = "● Pieces:";
    std::string whiteRemaining = "  ◈ White: " + std::to_string(ChessBoardUtilities::getNumPiecesOnBoard(chessBoard, chessBoard->getTeamOne()));
    std::string blackRemaining = "  ◈ Black: " + std::to_string(ChessBoardUtilities::getNumPiecesOnBoard(chessBoard, chessBoard->getTeamTwo()));

    return std::vector<std::string> {
        "",
        std::move(turn),
        std::move(remaining),
        std::move(whiteRemaining),
        std::move(blackRemaining)
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
