// AdvancedPawn.cc

#include "AdvancedPawn.h"

#include <memory>
#include <utility>
#include <vector>

#include "BoardMove.h"
#include "BoardMoveFactory.h"
#include "BoardSquare.h"
#include "ChessBoard.h"
#include "Constants.h"
#include "MoveDirection.h"
#include "Pawn.h"
#include "Piece.h"


// Basic ctor
AdvancedPawn::AdvancedPawn(Team team, PieceDirection pieceDirection, bool hasMoved) :
    ComplicatedCloneable<Piece, Pawn, AdvancedPawn>(PieceLevel::ADVANCED, team, pieceDirection, hasMoved, char32_t(U'♙')) { }

// Copy ctor
AdvancedPawn::AdvancedPawn(AdvancedPawn const &other) : 
    ComplicatedCloneable<Piece, Pawn, AdvancedPawn>(other) { }

// Move ctor
AdvancedPawn::AdvancedPawn(AdvancedPawn &&other) noexcept : 
    ComplicatedCloneable<Piece, Pawn, AdvancedPawn>(std::move(other)) { }

// Copy assignment
AdvancedPawn& AdvancedPawn::operator=(AdvancedPawn const &other) {
    if (this != &other) {
        Pawn::operator=(other);
    }
    return *this;
}

// Move assignment
AdvancedPawn& AdvancedPawn::operator=(AdvancedPawn &&other) noexcept {
    if (this != &other) {
        Pawn::operator=(std::move(other));
    }
    return *this;
}

/*
 * Returns all pseudo legal moves for an AdvancedPawn Pawn Piece
 */
std::vector<std::unique_ptr<BoardMove>> AdvancedPawn::getMovesImpl(std::unique_ptr<ChessBoard> const &chessBoard, BoardSquare const &fromSquare, bool onlyAttackingMoves) const {
    std::vector<std::unique_ptr<BoardMove>> moves = getStandardMoves(chessBoard, fromSquare, onlyAttackingMoves);

    // Non Attacking Moves 
    if (!onlyAttackingMoves) {
        int fromRow = fromSquare.boardRow;
        int fromCol = fromSquare.boardCol;
        MoveDirection pawnMoveDirection = getPawnMoveDirection();
        
        // Triple starter move
        BoardSquare normalMoveToSquare(fromRow + pawnMoveDirection.rowDirection, fromCol + pawnMoveDirection.colDirection);
        BoardSquare doubleMoveToSquare(fromRow + 2 * pawnMoveDirection.rowDirection, fromCol + 2 * pawnMoveDirection.colDirection);
        BoardSquare tripleMoveToSquare(fromRow + 3 * pawnMoveDirection.rowDirection, fromCol + 3 * pawnMoveDirection.colDirection);
        if (!pieceData.hasMoved && chessBoard->isSquareEmpty(normalMoveToSquare) && chessBoard->isSquareEmpty(doubleMoveToSquare) && chessBoard->isSquareEmpty(tripleMoveToSquare)) {
            addMoves(moves, chessBoard, fromSquare, tripleMoveToSquare, tripleMoveToSquare, true);
        }
    }

    return moves;
}
