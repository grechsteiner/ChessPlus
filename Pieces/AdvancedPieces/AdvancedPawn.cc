// AdvancedPawn.cc

#include <vector>

#include "AdvancedPawn.h"
#include "BoardMove.h"
#include "ChessBoard.h"


// Basic ctor
AdvancedPawn::AdvancedPawn(Team team, PieceDirection pieceDirection, bool hasMoved) :
    ComplicatedCloneable<Piece, Pawn, AdvancedPawn>(PieceLevel::ADVANCED, team, pieceDirection, hasMoved) {}

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

std::vector<BoardMove> AdvancedPawn::getMovesImpl(ChessBoard const &chessBoard, BoardSquare const &fromSquare, bool onlyAttackingMoves) const {
    int fromRow = fromSquare.getBoardRow();
    int fromCol = fromSquare.getBoardCol();
    std::pair<int, int> pawnDirection = getPawnDirection();

    std::vector<BoardMove> additionalMoves;

    // Non Attacking Moves 
    if (!onlyAttackingMoves) {
        
        // Triple starter move
        BoardSquare normalMoveToSquare(fromRow + pawnDirection.first, fromCol + pawnDirection.second);
        BoardSquare doubleMoveToSquare(fromRow + 2 * pawnDirection.first, fromCol + 2 * pawnDirection.second);
        BoardSquare tripleMoveToSquare(fromRow + 3 * pawnDirection.first, fromCol + 3 * pawnDirection.second);
        if (!pieceInfo.pieceData.hasMoved && chessBoard.isSquareEmpty(normalMoveToSquare) && chessBoard.isSquareEmpty(doubleMoveToSquare) && chessBoard.isSquareEmpty(tripleMoveToSquare)) {
            additionalMoves.emplace_back(BoardMove::createBasicMove(MoveType::STANDARD, pieceInfo.pieceData, fromSquare, tripleMoveToSquare, tripleMoveToSquare));
        }
    }

    std::vector<BoardMove> moves = getStandardMoves(chessBoard, fromSquare, onlyAttackingMoves);
    moves.insert(moves.end(), additionalMoves.begin(), additionalMoves.end());
    return moves;
}
