// Constants.cc

#include <string>
#include <unordered_map>
#include <cassert>
#include <algorithm>

#include "Constants.h"


#pragma mark - Color

// Static
const std::vector<std::pair<Color, std::string>> colorStringMap = {
    { Color::WHITE, "WHITE" },
    { Color::BLACK, "BLACK" },
};

bool isValidColor(std::string const &str) {
    std::string upperStr = toUpper(str);
    for (auto const &pair : colorStringMap) {
        if (pair.second == upperStr) {
            return true;
        }
    }
    return false;
}

Color stringToColor(std::string const &str) {
    std::string upperStr = toUpper(str);
    for (auto const &pair : colorStringMap) {
        if (pair.second == upperStr) {
            return pair.first;
        }
    }
    return Color::NONE;
}

std::string colorToString(Color color) {
    for (auto const &pair : colorStringMap) {
        if (pair.first == color) {
            return pair.second;
        }
    }
    return "";
}


#pragma mark - PieceType

// Static
const std::vector<std::pair<PieceType, std::string>> pieceTypeStringMap = {
    { PieceType::PAWN,      "P" },
    { PieceType::KNIGHT,    "N" },
    { PieceType::BISHOP,    "B" },
    { PieceType::ROOK,      "R" },
    { PieceType::QUEEN,     "Q" },
    { PieceType::KING,      "K" },
    { PieceType::EMPTY,     ""  }
};

bool isValidPieceType(std::string const &str) {
    std::string upperStr = toUpper(str);
    for (auto const &pair : pieceTypeStringMap) {
        if (pair.second == upperStr) {
            return true;
        }
    }
    return false;
}

PieceType stringToPieceType(std::string const &str) {
    std::string upperStr = toUpper(str);
    for (auto const &pair : pieceTypeStringMap) {
        if (pair.second == upperStr) {
            return pair.first;
        }
    }
    return PieceType::EMPTY;
}

std::string pieceTypeToString(PieceType pieceType) {
    for (auto const &pair : pieceTypeStringMap) {
        if (pair.first == pieceType) {
            return pair.second;
        }
    }
    return "";
}


#pragma mark - PieceDirection

// Static
const std::vector<std::pair<PieceDirection, std::string>> pieceDirectionStringMap = {
    { PieceDirection::NORTH,    "NORTH" },
    { PieceDirection::SOUTH,    "SOUTH" },
    { PieceDirection::EAST,     "EAST" },
    { PieceDirection::WEST,     "WEST" },
};

bool isValidPieceDirection(std::string const &str) {
    std::string upperStr = toUpper(str);
    for (auto const &pair : pieceDirectionStringMap) {
        if (pair.second == upperStr) {
            return true;
        }
    }
    return false;
}

PieceDirection stringToPieceDirection(std::string const &str) {
    std::string upperStr = toUpper(str);
    for (auto const &pair : pieceDirectionStringMap) {
        if (pair.second == upperStr) {
            return pair.first;
        }
    }
    return PieceDirection::BLANK;
}

std::string pieceDirectionToString(PieceDirection pieceDirection) {
    for (auto const &pair : pieceDirectionStringMap) {
        if (pair.first == pieceDirection) {
            return pair.second;
        }
    }
    return "";
}


#pragma mark - General

std::string toLower(std::string const &str) {
    std::string lowerStr = str;
    std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    return lowerStr;
}

std::string toUpper(std::string const &str) {
    std::string upperStr = str;
    std::transform(upperStr.begin(), upperStr.end(), upperStr.begin(),
                   [](unsigned char c) { return std::toupper(c); });
    return upperStr;
}

bool isInt(std::string const &str) {
    for (char ch : str) {
        if (!std::isdigit(ch)) {
            return false;
        }
    }
    return true;
}

int min(int a, int b) {
    return (a < b) ? a : b;
}
