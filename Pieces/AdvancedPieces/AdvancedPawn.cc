// AdvancedPawn.cc

#include <vector>

#include "AdvancedPawn.h"
#include "BoardMove.h"
#include "BoardMoveFactory.h"
#include "ChessBoard.h"


// Basic ctor
AdvancedPawn::AdvancedPawn(Team team, PieceDirection pieceDirection, bool hasMoved) :
    ComplicatedCloneable<Piece, Pawn, AdvancedPawn>(PieceLevel::ADVANCED, team, pieceDirection, hasMoved, char32_t(U'♙')) {}

// Copy ctor
AdvancedPawn::AdvancedPawn(AdvancedPawn const &other) : 
    ComplicatedCloneable<Piece, Pawn, AdvancedPawn>(other) {}

// Move ctor
AdvancedPawn::AdvancedPawn(AdvancedPawn &&other) noexcept : 
    ComplicatedCloneable<Piece, Pawn, AdvancedPawn>(std::move(other)) {}

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

std::vector<std::unique_ptr<BoardMove>> AdvancedPawn::getMovesImpl(std::unique_ptr<ChessBoard> const &chessBoard, BoardSquare const &fromSquare, bool onlyAttackingMoves) const {
    int fromRow = fromSquare.boardRow;
    int fromCol = fromSquare.boardCol;
    std::pair<int, int> pawnDirection = getPawnDirection();

    std::vector<std::unique_ptr<BoardMove>> moves = getStandardMoves(chessBoard, fromSquare, onlyAttackingMoves);

    // Non Attacking Moves 
    if (!onlyAttackingMoves) {
        
        // Triple starter move
        BoardSquare normalMoveToSquare(fromRow + pawnDirection.first, fromCol + pawnDirection.second);
        BoardSquare doubleMoveToSquare(fromRow + 2 * pawnDirection.first, fromCol + 2 * pawnDirection.second);
        BoardSquare tripleMoveToSquare(fromRow + 3 * pawnDirection.first, fromCol + 3 * pawnDirection.second);
        if (!pieceData.hasMoved && chessBoard->isSquareEmpty(normalMoveToSquare) && chessBoard->isSquareEmpty(doubleMoveToSquare) && chessBoard->isSquareEmpty(tripleMoveToSquare)) {
            addMoves(moves, chessBoard, fromSquare, tripleMoveToSquare, tripleMoveToSquare, true);
        }
    }

    return moves;
}
