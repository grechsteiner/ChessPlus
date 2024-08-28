// BoardPieceInterface.cc

#include <memory>

#include "BoardPieceInterface.h"
#include "Constants.h"
#include "Piece.h"
#include "FullMove.h"

Piece const& BoardPieceInterface::getPieceAt(int row, int col) const {
    return getPieceAtImpl(row, col);
}

bool BoardPieceInterface::isEmptySquareOnBoard(int row, int col) const {
    return isEmptySquareOnBoardImplementation(row, col);
}

bool BoardPieceInterface::isOpposingColorOnBoard(int row, int col, Color color) const {
    return isOpposingColorOnBoardImplementation(row, col, color);
}

bool BoardPieceInterface::isEmptySquareOrOpposingColorOnBoard(int row, int col, Color color) const {
    return isEmptySquareOrOpposingColorOnBoardImplementation(row, col, color);
}

bool BoardPieceInterface::isSquareCheckAttacked(int attackedRow, int attackedCol, Color color) const {
    return isSquareCheckAttackedImplementation(attackedRow, attackedCol, color);
}

bool BoardPieceInterface::hasMoveBeenMade() const {
    return hasMoveBeenMadeImplementation();
}

FullMove const& BoardPieceInterface::getLastMove() const {
    return getLastMoveImplementation();
}

int BoardPieceInterface::getNumRows() const {
    return getNumRowsImplementation();
}
int BoardPieceInterface::getNumCols() const {
    return getNumColsImplementation();
}
