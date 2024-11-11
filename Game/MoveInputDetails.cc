// MoveInputDetails.cc

#include "MoveInputDetails.h"

#include <optional>
#include <string>


// Basic ctor
MoveInputDetails::MoveInputDetails(std::string const &fromSquareStr, std::string const &toSquareStr, std::optional<std::string> const &promotionPieceTypeStr) :
    fromSquareStr(fromSquareStr), toSquareStr(toSquareStr), promotionPieceTypeStr(promotionPieceTypeStr) {}

// Copy ctor
MoveInputDetails::MoveInputDetails(MoveInputDetails const &other) :
    fromSquareStr(other.fromSquareStr), toSquareStr(other.toSquareStr), promotionPieceTypeStr(other.promotionPieceTypeStr) {}

// Move ctor
MoveInputDetails::MoveInputDetails(MoveInputDetails &&other) noexcept :
    fromSquareStr(std::move(other.fromSquareStr)), toSquareStr(std::move(other.toSquareStr)), promotionPieceTypeStr(std::move(other.promotionPieceTypeStr)) {}

// Copy assignment
MoveInputDetails& MoveInputDetails::operator=(MoveInputDetails &other) {
    if (this != &other) {
        fromSquareStr = other.fromSquareStr;
        toSquareStr = other.toSquareStr;
        promotionPieceTypeStr = other.promotionPieceTypeStr;
    }
    return *this;
}

// Move assignment
MoveInputDetails& MoveInputDetails::operator=(MoveInputDetails &&other) noexcept {
    if (this != &other) {
        fromSquareStr = std::move(other.fromSquareStr);
        toSquareStr = std::move(other.toSquareStr);
        promotionPieceTypeStr = std::move(other.promotionPieceTypeStr);
    }
    return *this;
}
