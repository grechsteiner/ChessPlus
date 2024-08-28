// Square.cc

#include <string>
#include <regex>
#include <utility>
#include <cassert>

#include "Square.h"

// Static
std::regex const Square::regexPattern("([a-zA-Z]+)([1-9]\\d*)");

// Static
bool Square::isValidSquare(std::string const &squareStr) {
    std::smatch match;
    return std::regex_match(squareStr, match, regexPattern);
}

// Static
std::pair<int, std::string> Square::getRowAndCol(std::string const &squareStr) {
    std::smatch match;
    if (std::regex_match(squareStr, match, regexPattern)) {
        std::string col = match[1];
        int row = std::stoi(match[2]);
        return std::make_pair(row, col);
    } else {
        assert(false);
    }
}

// Static
int Square::getRow(std::string const &squareStr) {
    std::smatch match;
    if (std::regex_match(squareStr, match, regexPattern)) {
        return std::stoi(match[2]);
    } else {
        assert(false);
    }
}

// Static
std::string Square::getCol(std::string const &squareStr) {
    std::smatch match;
    if (std::regex_match(squareStr, match, regexPattern)) {
        return match[1];
    } else {
        assert(false);
    }
}

// Static
std::pair<int, int> Square::getGridRowAndCol(std::string const &squareStr, int numRows, int numCols) {
    std::smatch match;
    if (std::regex_match(squareStr, match, regexPattern)) {
        std::string squareCol = match[1];
        int squareRow = std::stoi(match[2]);

        int gridCol = 0;
        gridCol += (squareCol[0] - 'a'); 
        for (int i = 1; i < squareCol.size(); ++i) {
            gridCol += (squareCol[i] - 'a' + 1);
        }

        int gridRow = numRows - squareRow;

        return std::make_pair(gridRow, gridCol);
    } else {
        assert(false);
    }

}

// Static
int Square::getGridRow(int squareRow, int numRows) {
    return numRows - squareRow;
}

// Static
int Square::getGridCol(std::string const &squareCol, int numCols) {
    int gridCol = 0;
    gridCol += (squareCol[0] - 'a'); 
    for (int i = 1; i < squareCol.size(); ++i) {
        gridCol += (squareCol[i] - 'a' + 1);
    }
    return gridCol;
}
