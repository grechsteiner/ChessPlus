// UserSquare.cc

#include <string>
#include <regex>
#include <utility>
#include <cassert>

#include "UserSquare.h"

// Static
std::regex const UserSquare::regexPattern("([a-zA-Z]+)([1-9]\\d*)");

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
    std::string userCol = getUserCol();
    int gridCol = 0;
    gridCol += (userCol[0] - 'a'); 
    for (int i = 1; i < userCol.size(); ++i) {
        gridCol += (userCol[i] - 'a' + 1);
    }
    return gridCol;
}
