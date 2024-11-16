// BasicRook.cc

#include <vector>

#include "BasicRook.h"
#include "BoardMove.h"

// Basic ctor
BasicRook::BasicRook(Team team, PieceDirection pieceDirection, bool hasMoved) :
    ComplicatedCloneable<Piece, Rook, BasicRook>(PieceLevel::BASIC, team, pieceDirection, hasMoved, char32_t(U'♜')) {}

// Copy ctor
BasicRook::BasicRook(BasicRook const &other) : 
    ComplicatedCloneable<Piece, Rook, BasicRook>(other) {}

// Move ctor
BasicRook::BasicRook(BasicRook &&other) noexcept : 
    ComplicatedCloneable<Piece, Rook, BasicRook>(std::move(other)) {}

// Copy assignment
BasicRook& BasicRook::operator=(BasicRook const &other) {
    if (this != &other) {
        Rook::operator=(other);
    }
    return *this;
}

// Move assignment
BasicRook& BasicRook::operator=(BasicRook &&other) noexcept {
    if (this != &other) {
        Rook::operator=(std::move(other));
    }
    return *this;
}

std::vector<std::unique_ptr<BoardMove>> BasicRook::getMovesImpl(std::unique_ptr<ChessBoard> const &chessBoard, BoardSquare const &fromSquare, bool onlyAttackingMoves) const {
    return getStandardMoves(chessBoard, fromSquare, onlyAttackingMoves);
}
