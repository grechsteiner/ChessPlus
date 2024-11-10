// ChessBoardFactory.h

#ifndef ChessBoardFactory_h
#define ChessBoardFactory_h

#include <memory>

#include "ChessBoard.h"


class ChessBoardFactory final {
public:
    static std::unique_ptr<ChessBoard> createChessBoard(int numRows, int numCols);  
};


#endif /* ChessBoardFactory */
