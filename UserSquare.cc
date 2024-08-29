// UserSquare.cc

#include <string>
#include <regex>
#include <utility>
#include <cassert>

#include "UserSquare.h"

// Static
std::regex const UserSquare::regexPattern("([a-z]+)([1-9]\\d*)");

UserSquare::UserSquare(std::string const &squareStr) : userSquare(squareStr) {}

// Static
bool UserSquare::isValidUserSquare(std::string const &squareStr) {
    std::smatch match;
    return std::regex_match(squareStr, match, regexPattern);
}

std::string UserSquare::toString() const {
    return userSquare;
}

int UserSquare::getUserRow() const { 
    std::smatch match;
    std::regex_match(userSquare, match, regexPattern);
    return std::stoi(match[2]);
}

std::string UserSquare::getUserCol() const { 
    std::smatch match;
    std::regex_match(userSquare, match, regexPattern);
    return match[1];
}

int UserSquare::getGridRow(int numRowsOnGrid) const {
    return numRowsOnGrid - getUserRow();
}

int UserSquare::getGridCol(int numColsOnGrid) const { 
    static int base = 26;
    int gridCol = 0;
    for (char c : getUserCol()) {
        gridCol = gridCol * base + (c - 'a');
    }
    return gridCol;
}
