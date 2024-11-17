// BasicPawn.cc

#include "BasicPawn.h"

#include <memory>
#include <utility>
#include <vector>

#include "BoardMove.h"
#include "BoardSquare.h"
#include "ChessBoard.h"
#include "Constants.h"
#include "Pawn.h"
#include "Piece.h"


// Basic ctor
BasicPawn::BasicPawn(Team team, PieceDirection pieceDirection, bool hasMoved) :
    ComplicatedCloneable<Piece, Pawn, BasicPawn>(PieceLevel::BASIC, team, pieceDirection, hasMoved, char32_t(U'♟')) { }

// Copy ctor
BasicPawn::BasicPawn(BasicPawn const &other) : 
    ComplicatedCloneable<Piece, Pawn, BasicPawn>(other) { }

// Move ctor
BasicPawn::BasicPawn(BasicPawn &&other) noexcept : 
    ComplicatedCloneable<Piece, Pawn, BasicPawn>(std::move(other)) { }

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

/*
 * Returns all pseudo legal moves for a BasicPawn Pawn Piece
 */
std::vector<std::unique_ptr<BoardMove>> BasicPawn::getMovesImpl(std::unique_ptr<ChessBoard> const &chessBoard, BoardSquare const &fromSquare, bool onlyAttackingMoves) const {
    return getStandardMoves(chessBoard, fromSquare, onlyAttackingMoves);
}
