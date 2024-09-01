// UserMove.cc

#include <string>

#include "UserMove.h"
#include "BoardMove.h"
#include "Constants.h"
#include "UserSquare.h"

// ctor
UserMove::UserMove(UserSquare const &fromSquare, UserSquare const &toSquare, std::optional<PieceType> promotionPieceType) :
    fromSquare(fromSquare), toSquare(toSquare), promotionPieceType(promotionPieceType) {} 

// Copy ctor
UserMove::UserMove(UserMove const &other) : 
    fromSquare(other.fromSquare), toSquare(other.toSquare), promotionPieceType(other.promotionPieceType) {}

// Move ctor 
UserMove::UserMove(UserMove &&other) :
    fromSquare(std::move(other.fromSquare)), toSquare(std::move(other.toSquare)), promotionPieceType(std::move(other.promotionPieceType)) {}

// Copy Assignment
UserMove& UserMove::operator=(UserMove const &other) {
    if (this != &other) {
        fromSquare = other.fromSquare;
        toSquare = other.toSquare;
        promotionPieceType = other.promotionPieceType;
    }
    return *this;
}

// Move Assignment
UserMove& UserMove::operator=(UserMove &&other) {
    if (this != &other) {
        // Transfer data from the other object
        fromSquare = std::move(other.fromSquare);
        toSquare = std::move(other.toSquare);
        promotionPieceType = std::move(other.promotionPieceType);
    }
    return *this;
}

std::string UserMove::toString() const {
    std::string moveString = fromSquare.toString() + " " + toSquare.toString();
    if (promotionPieceType.has_value()) {
        moveString += " " + pieceTypeToString(promotionPieceType.value());
    }
    return moveString;
}

UserSquare UserMove::getFromSquare() const {
    return fromSquare;
}

UserSquare UserMove::getToSquare() const {
    return toSquare;
}

std::optional<PieceType> UserMove::getPromotionPieceType() const {
    return promotionPieceType;
}
