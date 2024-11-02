// BasicKing.cc

#include <vector>

#include "BasicKing.h"
#include "OldBoardMove.h"

// Basic ctor
BasicKing::BasicKing(Team team, PieceDirection pieceDirection, bool hasMoved) :
    ComplicatedCloneable<Piece, King, BasicKing>(PieceLevel::BASIC, team, pieceDirection, hasMoved) {}

// Copy ctor
BasicKing::BasicKing(BasicKing const &other) : 
    ComplicatedCloneable<Piece, King, BasicKing>(other) {}

// Move ctor
BasicKing::BasicKing(BasicKing &&other) noexcept : 
    ComplicatedCloneable<Piece, King, BasicKing>(std::move(other)) {}

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

std::vector<OldBoardMove> BasicKing::getMovesImpl(ChessBoard const &chessBoard, BoardSquare const &fromSquare, bool onlyAttackingMoves) const {
    return getStandardMoves(chessBoard, fromSquare, onlyAttackingMoves);
}
