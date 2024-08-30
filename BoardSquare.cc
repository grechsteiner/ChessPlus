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

int BoardSquare::getUserRow(int numRowsOnBoard) const { return numRowsOnBoard - boardRow; }
std::string BoardSquare::getUserCol(int numColsOnBoard) const { 
    static int base = 26;
    std::string userCol = "";
    int n = boardRow;
    while (n >= 0) {
        int remainder = n % base;
        userCol = static_cast<char>('a' + remainder) + userCol;
        n = n / base - 1;  // Subtract 1 to handle the 0-indexed system properly
    }
    return userCol;
}

bool BoardSquare::isEqualToUserSquare(UserSquare const &userSquare, int numRowsOnBoard, int numColsOnBoard) const {
    return 
        getUserRow(numRowsOnBoard) == userSquare.getUserRow() &&
        getUserCol(numColsOnBoard) == userSquare.getUserCol();
}

UserSquare BoardSquare::toUserSquare(int numRowsOnBoard, int numColOnBoard) const {
    return UserSquare(getUserCol(numColOnBoard) + std::to_string(getUserRow(numRowsOnBoard)));
}
