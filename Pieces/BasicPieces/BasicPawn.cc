// BasicPawn.cc

#include <vector>

#include "BasicPawn.h"
#include "BoardMove.h"

// Basic ctor
BasicPawn::BasicPawn(Team team, PieceDirection pieceDirection, bool hasMoved) :
    ComplicatedCloneable<Piece, Pawn, BasicPawn>(PieceLevel::BASIC, team, pieceDirection, hasMoved) {}

// Copy ctor
BasicPawn::BasicPawn(BasicPawn const &other) : 
    ComplicatedCloneable<Piece, Pawn, BasicPawn>(other) {}

// Move ctor
BasicPawn::BasicPawn(BasicPawn &&other) noexcept : 
    ComplicatedCloneable<Piece, Pawn, BasicPawn>(std::move(other)) {}

// Copy assignment
BasicPawn& BasicPawn::operator=(BasicPawn const &other) {
    if (this != &other) {
        Pawn::operator=(other);
    }
    return *this;
}

// Move assignment
BasicPawn& BasicPawn::operator=(BasicPawn &&other) noexcept {
    if (this != &other) {
        Pawn::operator=(std::move(other));
    }
    return *this;
}

std::vector<BoardMove> BasicPawn::getMovesImpl(ChessBoard const &chessBoard, BoardSquare const &fromSquare, bool onlyAttackingMoves) const {
    return getStandardMoves(chessBoard, fromSquare, onlyAttackingMoves);
}
