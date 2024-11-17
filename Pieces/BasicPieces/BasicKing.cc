// BasicKing.cc

#include "BasicKing.h"

#include <memory>
#include <utility>
#include <vector>

#include "BoardMove.h"
#include "BoardSquare.h"
#include "ChessBoard.h"
#include "Constants.h"
#include "King.h"
#include "Piece.h"


// Basic ctor
BasicKing::BasicKing(Team team, PieceDirection pieceDirection, bool hasMoved) :
    ComplicatedCloneable<Piece, King, BasicKing>(PieceLevel::BASIC, team, pieceDirection, hasMoved, char32_t(U'♚')) { }

// Copy ctor
BasicKing::BasicKing(BasicKing const &other) : 
    ComplicatedCloneable<Piece, King, BasicKing>(other) { }

// Move ctor
BasicKing::BasicKing(BasicKing &&other) noexcept : 
    ComplicatedCloneable<Piece, King, BasicKing>(std::move(other)) { }

// Copy assignment
BasicKing& BasicKing::operator=(BasicKing const &other) {
    if (this != &other) {
        King::operator=(other);
    }
    return *this;
}

// Move assignment
BasicKing& BasicKing::operator=(BasicKing &&other) noexcept {
    if (this != &other) {
        King::operator=(std::move(other));
    }
    return *this;
}

/*
 * Returns all pseudo legal moves for a BasicBishop Piece
 */
std::vector<std::unique_ptr<BoardMove>> BasicKing::getMovesImpl(std::unique_ptr<ChessBoard> const &chessBoard, BoardSquare const &fromSquare, bool onlyAttackingMoves) const {
    return getStandardMoves(chessBoard, fromSquare, onlyAttackingMoves);
}
