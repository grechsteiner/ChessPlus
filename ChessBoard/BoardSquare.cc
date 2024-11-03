// BoardSquare.cc

#include "BoardSquare.h"


// Basic ctor
BoardSquare::BoardSquare(int boardRow, int boardCol) : boardRow(boardRow), boardCol(boardCol) {}

// Equality operator
bool BoardSquare::operator==(BoardSquare const &other) const {
    return 
        boardRow == other.boardRow &&
        boardCol == other.boardCol;
}
