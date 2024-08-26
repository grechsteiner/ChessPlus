// Piece.cc

#include <vector>
#include <memory>

#include "Board.h"
#include "Constants.h"
#include "Piece.h"


Piece::Piece(Color pieceColor, PieceType pieceType, PieceDirection pieceDirection, bool hasMoved, std::string const &image, std::string const &display, int pieceScore) :
    pieceColor(pieceColor), pieceType(pieceType), pieceDirection(pieceDirection), hasMoved(hasMoved), image(image), display(display), pieceScore(pieceScore) {}

std::vector<Move> Piece::getMoves(BoardPieceInterface const &board, int pieceRow, int pieceCol, bool attackingMoves) const {
    return getMovesImplementation(board, pieceRow, pieceCol, attackingMoves);
}


#pragma mark - Getters

Color Piece::getPieceColor() const {
    return pieceColor;
}

PieceType Piece::getPieceType() const {
    return pieceType;
}

PieceDirection Piece::getPieceDirection() const {
    return pieceDirection;
}

bool Piece::getHasMoved() const {
    return hasMoved;
}

void Piece::setHasMoved(bool newHasMoved) {
    hasMoved = newHasMoved;
}

int Piece::getPieceScore() const {
    return pieceScore;
}

const std::string& Piece::getImage() const {
    return image;
}

const std::string& Piece::getDisplay() const {
    return display;
}
