// AdvancedRook.cc

#include <vector>

#include "AdvancedRook.h"
#include "BoardMove.h"
#include "BoardMoveFactory.h"
#include "ChessBoard.h"

// Basic ctor
AdvancedRook::AdvancedRook(Team team, PieceDirection pieceDirection, bool hasMoved) :
    ComplicatedCloneable<Piece, Rook, AdvancedRook>(PieceLevel::ADVANCED, team, pieceDirection, hasMoved, char32_t(U'♖')) {}

// Copy ctor
AdvancedRook::AdvancedRook(AdvancedRook const &other) : 
    ComplicatedCloneable<Piece, Rook, AdvancedRook>(other) {}

// Move ctor
AdvancedRook::AdvancedRook(AdvancedRook &&other) noexcept : 
    ComplicatedCloneable<Piece, Rook, AdvancedRook>(std::move(other)) {}

// Copy assignment
AdvancedRook& AdvancedRook::operator=(AdvancedRook const &other) {
    if (this != &other) {
        Rook::operator=(other);
    }
    return *this;
}

// Move assignment
AdvancedRook& AdvancedRook::operator=(AdvancedRook &&other) noexcept {
    if (this != &other) {
        Rook::operator=(std::move(other));
    }
    return *this;
}

std::vector<std::unique_ptr<BoardMove>> AdvancedRook::getMovesImpl(std::unique_ptr<ChessBoard> const &chessBoard, BoardSquare const &fromSquare, bool onlyAttackingMoves) const {
    std::vector<BoardSquare> const additionalToSquares = { 
        BoardSquare(fromSquare.boardRow + 1, fromSquare.boardCol + 1),
        BoardSquare(fromSquare.boardRow + 1, fromSquare.boardCol - 1),
        BoardSquare(fromSquare.boardRow - 1, fromSquare.boardCol + 1),
        BoardSquare(fromSquare.boardRow - 1, fromSquare.boardCol - 1)
    };

    std::vector<std::unique_ptr<BoardMove>> moves = getStandardMoves(chessBoard, fromSquare, onlyAttackingMoves);
    if (chessBoard->isSquareOnBoard(fromSquare)) {
        for (BoardSquare const &toSquare : additionalToSquares) {
            if (chessBoard->isSquareEmpty(toSquare) || chessBoard->isSquareOtherTeam(toSquare, pieceData.team)) {
                moves.emplace_back(BoardMoveFactory::createStandardMove(fromSquare, toSquare, toSquare, false, pieceData, chessBoard->getPieceDataAt(toSquare)));
            }
        }
    }
    return moves;
}
