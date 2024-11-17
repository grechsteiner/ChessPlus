// ChessBoardUtilities.h

#ifndef ChessBoardUtilities_h
#define ChessBoardUtilities_h

#include <memory>

#include "ChessBoard.h"
#include "Constants.h"


/**
 * Utility methods that operate on ChessBoard instances
 */
namespace ChessBoardUtilities {
    bool isBoardInLegalSetupState(std::unique_ptr<ChessBoard> const &chessBoard);
    bool applyStandardSetup(std::unique_ptr<ChessBoard> &chessBoard, PieceLevel pieceLevel);
    bool isGameOver(std::unique_ptr<ChessBoard> const &chessBoard, Team currentTurn);
    int getNumPiecesOnBoard(std::unique_ptr<ChessBoard> const &chessBoard, Team team);
}


#endif /* ChessBoardUtilities_h */
