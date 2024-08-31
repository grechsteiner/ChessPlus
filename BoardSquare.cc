// BoardSquare.cc

#include <string>

#include "BoardSquare.h"
#include "UserSquare.h"

BoardSquare::BoardSquare(int boardRow, int boardCol) : boardRow(boardRow), boardCol(boardCol) {}

bool BoardSquare::operator==(BoardSquare const &other) const {
    return 
        boardRow == other.boardRow &&
        boardCol == other.boardCol;
}

int BoardSquare::getBoardRow() const { return boardRow; }
int BoardSquare::getBoardCol() const { return boardCol; }

