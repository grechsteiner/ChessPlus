// Move.cc

#include <cctype>

#include "Constants.h"
#include "Move.h"

// Static
const Move Move::DEFAULT = Move("a1", "a2");

Move::Move(std::string const &from, std::string const &to, std::string const &promotion) : 
    Move(std::stoi(from.substr(1)), from[0], std::stoi(to.substr(1)), to[0], promotion) {}

Move::Move(int fromRow, char fromCol, int toRow, char toCol, std::string const &promotion) :
    fromRow(fromRow), fromCol(fromCol), toRow(toRow), toCol(toCol), promotionPieceType(stringToPieceType(promotion)) {}

Move::Move(int numVectorRows, int fromRow, int fromCol, int toRow, int toCol, PieceType promotionPieceType) :
    fromRow(getStandardRow(numVectorRows, fromRow)), 
    fromCol(getStandardCol(fromCol)), 
    toRow(getStandardRow(numVectorRows, toRow)), 
    toCol(getStandardCol(toCol)), 
    promotionPieceType(promotionPieceType) {}

// Static
bool Move::isValidMoveSyntax(std::string const &from, std::string const &to, std::string const &promotion) {

    // Check (from != to)
    if (from == to) {
        return false;
    }

    // Check that length of from and to are greater than or equal to 2
    if (from.length() < 2 || to.length() < 2) {
        return false;
    }

    // Both columns must be lowercase letters
    char fromCol = from[0];
    char toCol = to[0];
    if (!std::islower(fromCol) || !std::islower(toCol)) {
        return false;
    }

    std::string fromRow = from.substr(1);
    std::string toRow = to.substr(1);

    // Check that from row is a non negative number
    for (char const &c : fromRow) {
        if (!std::isdigit(c)) {
            return false;
        }
    }

    // Check that to row is a non negative number
    for (char const &c : toRow) {
        if (!std::isdigit(c)) {
            return false;
        }
    }

    // Check that both rows are non zero
    if (std::stoi(fromRow) <= 0 || std::stoi(toRow) <= 0) {
        return false;
    }

    // If promotion piece is entered, it must be Queen::'Q', Knight::'N', Rook::'R', Bishop'B'
    if (!promotion.empty()) {
        // Must be a single letter
        if (promotion.length() > 1) {
            return false;
        }
        // Must be one of the available letters
        if (promotion != "Q" && promotion != "N" && promotion != "R" && promotion != "B" && promotion != "q" && promotion != "n" && promotion != "r" && promotion != "b") {
            return false;
        }
    }

    // We're all good, valid syntax
    return true;
}


std::string Move::toString() const {
    std::string move = fromCol + fromRow + " " + toCol + toRow;
    if (promotionPieceType != PieceType::EMPTY) {
        move += pieceTypeToString(promotionPieceType);
    }
    return move;
}


#pragma mark - Getters

int Move::getFromRow() const {
    return fromRow;
}

char Move::getFromCol() const {
    return fromCol;
}

int Move::getToRow() const {
    return toRow;
}

char Move::getToCol() const {
    return toCol;
}

PieceType Move::getPromotionPieceType() const {
    return promotionPieceType;
}

int Move::getVectorRow(int numVectorRows, int moveRow) const {
    return numVectorRows - moveRow;
}

int Move::getVectorCol(char moveCol) const {
    return moveCol - 'a';
}

int Move::getStandardRow(int numVectorRows, int vectorRow) const {
    return numVectorRows - vectorRow;
}

char Move::getStandardCol(int vectorCol) const {
    return vectorCol + 'a';
}

bool Move::operator==(const Move& other) const {
    return 
        fromRow == other.fromRow &&
        fromCol == other.fromCol && 
        toRow == other.toRow &&
        toCol == other.toCol &&
        promotionPieceType == other.promotionPieceType;
}
