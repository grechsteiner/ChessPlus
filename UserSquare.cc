// UserSquare.cc

#include <string>
#include <regex>
#include <utility>

#include "UserSquare.h"


// Basic ctor
UserSquare::UserSquare(std::string const &squareStr) : userSquare(squareStr) {
    std::smatch match;
    std::regex_match(userSquare, match, getRegexPattern());
    userRow = std::stoi(match[2].str());
    userCol = match[1].str();
}

// Move ctor
UserSquare::UserSquare(UserSquare &&other) noexcept : 
    userSquare(std::move(other.userSquare)), userRow(other.userRow), userCol(std::move(other.userCol)) {}

// Move assignment
UserSquare& UserSquare::operator=(UserSquare &&other) noexcept {
    if (this != &other) {
        userSquare = std::move(other.userSquare);
        userRow = other.userRow;
        userCol = std::move(other.userCol);
    }
    return *this;
}

// Equality operator
bool UserSquare::operator==(UserSquare const &other) const {
    return userSquare == other.userSquare;
}

// Static
bool UserSquare::isValidUserSquare(std::string const &squareStr) {
    std::smatch match;
    return std::regex_match(squareStr, match, getRegexPattern());
}

// Static
std::regex UserSquare::getRegexPattern() { 
    std::regex const regexPattern("^([a-z]+)([1-9][0-9]*)$");
    return regexPattern;
}

std::string const& UserSquare::getUserSquare() const { return userSquare; }
int UserSquare::getUserRow() const { return userRow; }
std::string const& UserSquare::getUserCol() const { return userCol; }
