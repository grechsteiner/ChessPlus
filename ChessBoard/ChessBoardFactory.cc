// ChessBoardFactory.cc

#include "ChessBoardFactory.h"

#include <memory>

#include "ChessBoard.h"
#include "ChessBoardImpl.h"


/*
 * Static
 *
 * Return a ChessBoard instance
 */
std::unique_ptr<ChessBoard> ChessBoardFactory::createChessBoard(int numRowsOnBoard, int numColsOnBoard) {
    return std::make_unique<ChessBoardImpl>(numRowsOnBoard, numColsOnBoard);
}
