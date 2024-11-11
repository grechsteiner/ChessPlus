// ChessBoardUtilities.h

#ifndef ChessBoardUtilities_h
#define ChessBoardUtilities_h

#include <memory>

#include "ChessBoard.h"


namespace ChessBoardUtilities {
    bool isBoardInLegalSetupState(std::unique_ptr<ChessBoard> const &chessBoard);
    bool applyStandardSetup(std::unique_ptr<ChessBoard> &chessBoard);
    bool isGameOver(std::unique_ptr<ChessBoard> const &chessBoard);
}


#endif /* ChessBoardUtilities_h */
