// BoardMoveInterface.cc

#include "BoardMoveInterface.h"
#include "Constants.h"
#include "FullMove.h"


Piece const& BoardMoveInterface::getPieceAt(int row, int col) const {
    return getPieceAtImpl(row, col);
}

void BoardMoveInterface::setPosition(int row, int col, Color pieceColor, PieceType pieceType, PieceDirection pieceDirection, bool hasMoved, int pieceScore) {
    setPositionImpl(row, col, pieceColor, pieceType, pieceDirection, hasMoved, pieceScore);
}

void BoardMoveInterface::clearPosition(int row, int col) {
    clearPositionImpl(row, col);
}

void BoardMoveInterface::swapPositions(int rowOne, int colOne, int rowTwo, int colTwo) {
    swapPositionsImpl(rowOne, colOne, rowTwo, colTwo);
}

void BoardMoveInterface::setHasMoved(int row, int col, bool hasMoved) {
    setHasMovedImpl(row, col, hasMoved);
}
