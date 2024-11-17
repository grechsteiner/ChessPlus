// ChessBoardFactory.h

#ifndef ChessBoardFactory_h
#define ChessBoardFactory_h

#include <memory>

#include "ChessBoard.h"


/**
 * Factory for creating ChessBoard instances
 */
class ChessBoardFactory final {
public:
    static std::unique_ptr<ChessBoard> createChessBoard(int numRowsOnBoard, int numColsOnBoard);  
};


#endif /* ChessBoardFactory */
