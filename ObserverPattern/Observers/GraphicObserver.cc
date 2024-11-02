// GraphicObserver.cc

#include "GraphicObserver.h"
#include "Game.h"

GraphicObserver::GraphicObserver(Game *game) : game(game), window() {
    game->attach(this);
}

GraphicObserver::~GraphicObserver() {
    game->detach(this);
}

void GraphicObserver::notifyImpl() {
    /*
    GameState gameState = game->getGameState();

    if (gameState == GameState::MAIN_MENU) {
        window.fillRectangle(0, 0, 600, 600, 0); // Clear the window with white color
        window.drawString(50, 50, "Main Menu"); // Center the "Main Menu" text
    } else if (gameState == GameState::SETUP) {
        auto state = game->getSetupState();
        const ChessBoard& board = std::get<0>(state);

        window.fillRectangle(0, 0, 600, 600, 0); // Clear the window with white color
        printBoard(board, std::get<2>(state));
    } else {
        auto state = game->getActiveGameState();
        const ChessBoard& board = std::get<0>(state);

        window.fillRectangle(0, 0, 600, 600, 0); // Clear the window with white color
        printBoard(board, std::get<2>(state));
    }
    */
}

void GraphicObserver::printPiece(const std::string& str, Team team, int x, int y) {
    int pieceColor = (team == Team::TEAM_TWO) ? 1 : 0; // Use predefined colors
    window.drawString(x, y, str, pieceColor);
}

void GraphicObserver::printBoard(const IChessBoard& chessBoard, int turn) {
    int numRows = chessBoard.getNumRows();
    int numCols = chessBoard.getNumCols();
    int windowWidth = 600;  // Width of the window
    int windowHeight = 600; // Height of the window

    int squareSize = std::min(windowWidth / numCols, windowHeight / numRows);

    for (int row = 0; row < numRows; ++row) {
        for (int col = 0; col < numCols; ++col) {
            int x = col * squareSize;
            int y = row * squareSize;
            int color = ((row + col) % 2 == 0) ? 3 : 4; // Alternate colors for squares
            window.fillRectangle(x, y, squareSize, squareSize, color);

            std::optional<PieceInfo> pieceInfo = chessBoard.getPieceInfoAt(BoardSquare(row, col));
            if (pieceInfo.has_value()) {
                printPiece(pieceInfo.value().display, pieceInfo.value().pieceData.team, x + squareSize / 2, y + squareSize / 2);
            }            
        }
    }
}

