// BasicBishop.cc

#include "BasicBishop.h"

#include <memory>
#include <utility>
#include <vector>

#include "Bishop.h"
#include "BoardMove.h"
#include "BoardSquare.h"
#include "ChessBoard.h"
#include "Constants.h"
#include "Piece.h"


// Basic ctor
BasicBishop::BasicBishop(Team team, PieceDirection pieceDirection, bool hasMoved) :
    ComplicatedCloneable<Piece, Bishop, BasicBishop>(PieceLevel::BASIC, team, pieceDirection, hasMoved, char32_t(U'♝')) {}

// Copy ctor
BasicBishop::BasicBishop(BasicBishop const &other) : 
    ComplicatedCloneable<Piece, Bishop, BasicBishop>(other) {}

// Move ctor
BasicBishop::BasicBishop(BasicBishop &&other) noexcept : 
    ComplicatedCloneable<Piece, Bishop, BasicBishop>(std::move(other)) {}

// Copy assignment
BasicBishop& BasicBishop::operator=(BasicBishop const &other) {
    if (this != &other) {
        Bishop::operator=(other);
    }
    return *this;
}

// Move assignment
BasicBishop& BasicBishop::operator=(BasicBishop &&other) noexcept {
    if (this != &other) {
        Bishop::operator=(std::move(other));
    }
    return *this;
}

/*
 * Returns all pseudo legal moves for a BasicBishop Piece
 */
std::vector<std::unique_ptr<BoardMove>> BasicBishop::getMovesImpl(std::unique_ptr<ChessBoard> const &chessBoard, BoardSquare const &fromSquare, bool onlyAttackingMoves) const {
    return getStandardMoves(chessBoard, fromSquare, onlyAttackingMoves);
}
