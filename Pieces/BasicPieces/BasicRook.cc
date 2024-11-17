// BasicRook.cc

#include "BasicRook.h"

#include <memory>
#include <utility>
#include <vector>

#include "BoardMove.h"
#include "BoardSquare.h"
#include "ChessBoard.h"
#include "Constants.h"
#include "Piece.h"
#include "Rook.h"


// Basic ctor
BasicRook::BasicRook(Team team, PieceDirection pieceDirection, bool hasMoved) :
    ComplicatedCloneable<Piece, Rook, BasicRook>(PieceLevel::BASIC, team, pieceDirection, hasMoved, char32_t(U'♜')) { }

// Copy ctor
BasicRook::BasicRook(BasicRook const &other) : 
    ComplicatedCloneable<Piece, Rook, BasicRook>(other) { }

// Move ctor
BasicRook::BasicRook(BasicRook &&other) noexcept : 
    ComplicatedCloneable<Piece, Rook, BasicRook>(std::move(other)) { }

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

/*
 * Returns all pseudo legal moves for a BasicBishop Piece
 */
std::vector<std::unique_ptr<BoardMove>> BasicRook::getMovesImpl(std::unique_ptr<ChessBoard> const &chessBoard, BoardSquare const &fromSquare, bool onlyAttackingMoves) const {
    return getStandardMoves(chessBoard, fromSquare, onlyAttackingMoves);
}
