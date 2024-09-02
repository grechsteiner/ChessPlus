// UserMove.cc

#include <string>
#include <utility>

#include "UserMove.h"
#include "Constants.h"
#include "UserSquare.h"


// Basic ctor
UserMove::UserMove(UserSquare const &fromSquare, UserSquare const &toSquare, std::optional<PieceType> promotionPieceType) :
    fromSquare(fromSquare), toSquare(toSquare), promotionPieceType(promotionPieceType) {} 

// Move ctor 
UserMove::UserMove(UserMove &&other) noexcept :
    fromSquare(std::move(other.fromSquare)), toSquare(std::move(other.toSquare)), promotionPieceType(std::move(other.promotionPieceType)) {}

// Move assignment
UserMove& UserMove::operator=(UserMove &&other) noexcept {
    if (this != &other) {
        fromSquare = std::move(other.fromSquare);
        toSquare = std::move(other.toSquare);
        promotionPieceType = std::move(other.promotionPieceType);
    }
    return *this;
}

// Equality operator
bool UserMove::operator==(UserMove const &other) const {
    return 
        fromSquare == other.fromSquare &&
        toSquare == other.toSquare &&
        promotionPieceType == other.promotionPieceType;
}

std::string UserMove::toString() const {
    std::string userMoveString = fromSquare.getUserSquare() + " " + toSquare.getUserSquare();
    if (promotionPieceType.has_value()) {
        userMoveString += " " + pieceTypeToString(promotionPieceType.value());
    }
    return userMoveString;
}

UserSquare const& UserMove::getFromSquare() const { return fromSquare; }
UserSquare const& UserMove::getToSquare() const { return toSquare; }
std::optional<PieceType> UserMove::getPromotionPieceType() const { return promotionPieceType; }
