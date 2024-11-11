// Constants.cc

#include <string>
#include <unordered_map>
#include <cassert>
#include <algorithm>

#include "Constants.h"
#include "BoardSquare.h"
#include "BoardMove.h"


#pragma mark - Color

ComputerPlayerLevel stringToComputerPlayerLevel(std::string const &str) {
    if (str == "1") {
        return ComputerPlayerLevel::ONE;
    } else if (str == "2") {
        return ComputerPlayerLevel::TWO;
    } else if (str == "3") {
        return ComputerPlayerLevel::THREE;
    } else if (str == "4") {
        return ComputerPlayerLevel::FOUR;
    } else if (str == "5") {
        return ComputerPlayerLevel::FIVE;
    } else {
        assert(false);
    }
}


// Static
const std::vector<std::pair<Team, std::string>> colorStringMap = {
    { Team::TEAM_ONE, "WHITE" },
    { Team::TEAM_TWO, "BLACK" },
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

Team stringToColor(std::string const &str) {
    std::string upperStr = toUpper(str);
    for (auto const &pair : colorStringMap) {
        if (pair.second == upperStr) {
            return pair.first;
        }
    }
    assert(false);
}

std::string colorToString(Team color) {
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
    { PieceType::KING,      "K" }
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
    assert(false);
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
    assert(false);
}

std::string pieceDirectionToString(PieceDirection pieceDirection) {
    for (auto const &pair : pieceDirectionStringMap) {
        if (pair.first == pieceDirection) {
            return pair.second;
        }
    }
    return "";
}

