// ChessBoardFactory.cc

#include <memory>

#include "ChessBoardFactory.h"
#include "ChessBoard.h"
#include "ChessBoardImpl.h"


// Static
std::unique_ptr<ChessBoard> ChessBoardFactory::createChessBoard(int numRows, int numCols) {
    return std::make_unique<ChessBoardImpl>(numRows, numCols);
}
