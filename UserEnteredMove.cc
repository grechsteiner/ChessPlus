// UserEnteredMove.cc

#include <string>
#include <utility>

#include "UserEnteredMove.h"
#include "Square.h"

UserEnteredMove::UserEnteredMove(std::string const &fromSquare, std::string const &toSquare, std::string const &promotionPiece) : 
    fromRow(Square::getRow(fromSquare)),
    fromCol(Square::getCol(fromSquare)),
    toRow(Square::getRow(toSquare)),
    toCol(Square::getCol(toSquare)),
    promotionPiece(promotionPiece) 
{} 

// Copy ctor
UserEnteredMove::UserEnteredMove(UserEnteredMove const &other) : 
    fromRow(other.fromRow), toRow(other.toRow), fromCol(other.fromCol), toCol(other.toCol), promotionPiece(other.promotionPiece) 
{}

// Move ctor 
UserEnteredMove::UserEnteredMove(UserEnteredMove &&other) :
    fromRow(other.fromRow), toRow(other.toRow), fromCol(std::move(other.fromCol)), toCol(std::move(other.toCol)), promotionPiece(std::move(other.promotionPiece)) 
{}

// Static
bool UserEnteredMove::isValidSyntax(std::string const &fromSquare, std::string const &toSquare, std::string const &promotionPiece) {
    return Square::isValidSquare(fromSquare) && Square::isValidSquare(toSquare);
}  

std::string UserEnteredMove::toString() const {
    std::string moveString = fromCol + std::to_string(fromRow) + " " + toCol + std::to_string(toRow);
    if (!promotionPiece.empty()) {
        moveString += " " + promotionPiece;
    }
    return moveString;
}


#pragma mark - Getters

// Squares
int UserEnteredMove::getFromRow() const { return fromRow; }
int UserEnteredMove::getToRow() const { return toRow; }
std::string const& UserEnteredMove::getFromCol() const { return fromCol;}
std::string const& UserEnteredMove::getToCol() const { return toCol; }

// General Info
std::string const& UserEnteredMove::getPromotionPiece() const { return promotionPiece; }
