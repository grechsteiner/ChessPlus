// Constants.cc

#include <string>
#include <unordered_map>
#include <cassert>
#include <algorithm>

#include "Constants.h"
#include "BoardSquare.h"
#include "UserSquare.h"
#include "UserMove.h"
#include "BoardMove.h"


#pragma mark - Color

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


// static
int const base = 26;

BoardSquare createBoardSquare(UserSquare const &userSquare, int numRowsOnBoard, int numColsOnBoard) {
    int boardRow = numRowsOnBoard - userSquare.getUserRow();
    int boardCol = 0;
    for (char c : userSquare.getUserCol()) {
        boardCol = boardCol * base + (c - 'a');
    }
    return BoardSquare(boardRow, boardCol);
}

UserSquare createUserSquare(BoardSquare const &boardSquare, int numRowsOnBoard, int numColsOnBoard) {
    std::string userRow = std::to_string(numRowsOnBoard - boardSquare.getBoardRow());
    
    std::string userCol = "";
    int n = boardSquare.getBoardCol();
    while (n >= 0) {
        int remainder = n % base;
        userCol = static_cast<char>('a' + remainder) + userCol;
        n = n / base - 1;  // Subtract 1 to handle the 0-indexed system properly
    }

    return UserSquare(userCol + userRow);
}

bool areEqual(UserSquare const &userSquare, BoardSquare const &boardSquare, int numRowsOnBoard, int numColsOnBoard) {
    return createBoardSquare(userSquare, numRowsOnBoard, numColsOnBoard) == boardSquare;
}

bool areEqual(UserMove const &userMove, std::unique_ptr<BoardMove> const &boardMove, int numRowsOnBoard, int numColsOnBoard) {
    return 
        createBoardSquare(userMove.getFromSquare(), numRowsOnBoard, numColsOnBoard) == boardMove->getFromSquare() &&
        createBoardSquare(userMove.getToSquare(), numRowsOnBoard, numColsOnBoard) == boardMove->getToSquare() &&
        userMove.getPromotionPieceType() == boardMove->getPromotionPieceType();
}
