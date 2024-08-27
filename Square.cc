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
