// BoardSquare.cc

#include "BoardSquare.h"

#include <cctype>
#include <optional>
#include <regex>
#include <string>


// Basic ctor
BoardSquare::BoardSquare(int boardRow, int boardCol) : 
    boardRow(boardRow), boardCol(boardCol) { }

// Copy ctor
BoardSquare::BoardSquare(BoardSquare const &other) : 
    boardRow(other.boardRow), boardCol(other.boardCol) { }

// Move ctor
BoardSquare::BoardSquare(BoardSquare &&other) noexcept :
    boardRow(other.boardRow), boardCol(other.boardCol) { }

// Copy assignment
BoardSquare& BoardSquare::operator=(BoardSquare const &other) {
    if (this != &other) {
        boardRow = other.boardRow;
        boardCol = other.boardCol;
    }
    return *this;
}

// Move assignment
BoardSquare& BoardSquare::operator=(BoardSquare &&other) noexcept {
    if (this != &other) {
        boardRow = other.boardRow;
        boardCol = other.boardCol;
    }
    return *this;
}

// Equality
bool BoardSquare::operator==(BoardSquare const &other) const {
    return 
        boardRow == other.boardRow &&
        boardCol == other.boardCol;
}

/*
 * Static
 *
 * Create Optional BoardSquare
 * - value if valid string representation
 * - nullopt if in-valid string representation
 */
std::optional<BoardSquare> BoardSquare::createBoardSquare(std::string const &squareStr, int numRowsOnBoard, int numColsOnBoard) {
    static std::regex const boardSquarePattern("^([a-z]+)([1-9][0-9]*)$", std::regex_constants::icase);
    
    std::smatch matches;
    if (std::regex_match(squareStr, matches, boardSquarePattern)) {
        int boardRow = numRowsOnBoard - std::stoi(matches[2].str());
        int boardCol = 0;
        for (char ch : matches[1].str()) {
            boardCol = boardCol * 26 + (std::tolower(ch) - 'a');
        }

        return std::make_optional<BoardSquare>(boardRow, boardCol);
    }
    return std::nullopt;
}
