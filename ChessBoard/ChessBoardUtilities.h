// ChessBoardUtilities.h

#ifndef ChessBoardUtilities_h
#define ChessBoardUtilities_h

#include <memory>

#include "ChessBoard.h"


class ChessBoardUtilities final {
public:
    static std::vector<PieceType> const standardBackrowSetupOrder;
    static bool isBoardInLegalSetupState(std::unique_ptr<ChessBoard> const &chessBoard);
    static bool applyStandardSetup(std::unique_ptr<ChessBoard> &chessBoard);
};


#endif /* ChessBoardUtilities_h */
