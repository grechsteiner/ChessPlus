// BoardSquare.cc

#include <optional>
#include <regex>

#include "BoardSquare.h"


// Basic ctor
BoardSquare::BoardSquare(int boardRow, int boardCol) : boardRow(boardRow), boardCol(boardCol) {}

// Equality operator
bool BoardSquare::operator==(BoardSquare const &other) const {
    return 
        boardRow == other.boardRow &&
        boardCol == other.boardCol;
}

// Static
std::optional<BoardSquare> BoardSquare::createBoardSquare(std::string const &squareStr, int numRowsOnBoard, int numColsOnBoard) {
    static std::regex const boardSquarePattern("^([a-z]+)([1-9][0-9]*)$");
    
    std::smatch matches;
    if (std::regex_match(squareStr, matches, boardSquarePattern)) {
        int boardRow = numRowsOnBoard - std::stoi(matches[2].str());
        int boardCol = 0;
        for (char ch : matches[1].str()) {
            boardCol = boardCol * 26 + (ch - 'a');
        }

        return std::make_optional<BoardSquare>(boardRow, boardCol);
    }
    return std::nullopt;
}
