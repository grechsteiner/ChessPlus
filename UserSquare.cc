// UserSquare.cc

#include <string>
#include <regex>
#include <utility>
#include <cassert>

#include "UserSquare.h"
#include "BoardSquare.h"

UserSquare::UserSquare(std::string const &squareStr) : userSquare(squareStr) {
    std::smatch match;
    std::regex_match(squareStr, match, std::regex("^([a-z]+)([1-9][0-9]*)$"));
    userRow = std::stoi(match[2].str());
    userCol = match[1].str();
}

bool UserSquare::operator==(UserSquare const &other) const {
    return userSquare == other.userSquare;
}

// Static
bool UserSquare::isValidUserSquare(std::string const &squareStr) {
    std::smatch match;
    return std::regex_match(squareStr, match, std::regex("^([a-z]+)([1-9][0-9]*)$"));
}

std::string UserSquare::toString() const {
    return userSquare;
}

int UserSquare::getUserRow() const { 
    return userRow;
}

std::string UserSquare::getUserCol() const { 
    return userCol;
}
