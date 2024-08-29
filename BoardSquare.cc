// BoardSquare.cc

#include <string>

#include "BoardSquare.h"

BoardSquare::BoardSquare(int boardRow, int boardCol) : boardRow(boardRow), boardCol(boardCol) {}

std::string BoardSquare::toString() const { return std::to_string(boardRow) + std::to_string(boardCol); }
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
