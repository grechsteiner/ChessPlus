// TextObserver.cc

#include <iostream>

#include "TextObserver.h"
#include "Game.h"
#include "State.h"


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
    out << "   ________                       ____  __           " << std::endl;   
    out << "  / ____/ /_  ___  __________    / __ \\/ /_  _______ " << std::endl;
    out << " / /   / __ \\/ _ \\/ ___/ ___/   / /_/ / / / / / ___/ " << std::endl;
    out << "/ /___/ / / /  __(__  |__  )   / ____/ / /_/ (__  )  " << std::endl;
    out << "\\____/_/ /_/\\___/____/____/   /_/   /_/\\__,_/____/   " << std::endl;

    out << std::endl;
    out << "     __             ______                                       ____            __         __       _             " << std::endl;   
    out << "    / /_  __  __   / ____/________ ___  ___________  ____       / __ \\___  _____/ /_  _____/ /____  (_)___  ___  _____ " << std::endl;
    out << "   / __ \\/ / / /  / / __/ ___/ __ `/ / / / ___/ __ \\/ __ \\     / /_/ / _ \\/ ___/ __ \\/ ___/ __/ _ \\/ / __ \\/ _ \\/ ___/ " << std::endl;
    out << "  / /_/ / /_/ /  / /_/ / /  / /_/ / /_/ (__  ) /_/ / / / /    / _, _/  __/ /__/ / / (__  ) /_/  __/ / / / /  __/ /     " << std::endl;
    out << " /_.___/\\__, /   \\____/_/   \\__,_/\\__, /____/\\____/_/ /_/    /_/ |_|\\___/\\___/_/ /_/____/\\__/\\___/_/_/ /_/\\___/_/      " << std::endl;
    out << "       /____/                    /____/                                                                            " << std::endl;                                               
}

void TextObserver::printPiece(const std::string& str, Team team) {
    if (str == " ") {
        out << " ";
    } else if (team == Team::TEAM_TWO) {
        out << "\033[30m" << str << "\033[0m";
    } else {
        out << "\033[90m" << str << "\033[0m";
    }
}

void TextObserver::printBoard(ChessBoard const &chessBoard, int turn) {
    // Top line
    out << "|  ╔";
    for (int col = 0; col < chessBoard.getNumCols(); ++col) {
        out << "═";
    }
    out << "╗ |" << std::endl;

    for (int row = 0; row < chessBoard.getNumRows(); ++row) {
        out << "|" << chessBoard.getNumRows() - row;
        if (chessBoard.getNumRows() - row < 10) {
            out << " ";
        }
        out << "║";
        for (int col = 0; col < chessBoard.getNumCols(); ++col) {

            std::optional<PieceInfo> pieceInfo = chessBoard.getPieceInfoAt(BoardSquare(row, col));
            if (pieceInfo.has_value()) {
                printPiece(pieceInfo.value().image, chessBoard.getPieceDataAt(BoardSquare(row, col)).value().team);
            } else {
                out << " ";
            }

        }
        out << "║ |" << std::endl;
    }

    // Bottom line
    out << "|  ╚";
    for (int col = 0; col < chessBoard.getNumCols(); ++col) {
        out << "═";
    }
    out << "╝ |" << std::endl;

    std::string alphabet = "abcdefghijklmnopqrstuvwxyz";
    out << "|   ";
    for (int col = 0; col < chessBoard.getNumCols(); ++col) {
        out << alphabet[col];
    }
    out << "  |" << std::endl;

    if (turn == 0) {
        out << "|Turn: White";

    } else {
        out << "|Turn: Black";
    }

    for (int i = 0; i < (chessBoard.getNumCols() - 7); ++i) {
        out << " ";
    }
    out << " |" << std::endl;
}
