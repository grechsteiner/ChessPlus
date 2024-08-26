// BoardPieceInterface.cc

#include <memory>

#include "BoardPieceInterface.h"
#include "Constants.h"
#include "Piece.h"

const std::unique_ptr<Piece>& BoardPieceInterface::getPieceAt(int row, int col) const {
    return getPieceAtImplementation(row, col);
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

bool BoardPieceInterface::lastMove() const {
    return lastMoveImplementation();
}

const CompletedMove& BoardPieceInterface::getLastMove() const {
    return getLastMoveImplementation();
}

int BoardPieceInterface::getNumRows() const {
    return getNumRowsImplementation();
}
int BoardPieceInterface::getNumCols() const {
    return getNumColsImplementation();
}
