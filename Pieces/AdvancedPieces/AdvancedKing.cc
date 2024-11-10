// AdvancedKing.cc

#include <vector>

#include "AdvancedKing.h"
#include "BoardMove.h"
#include "BoardMoveFactory.h"
#include "ChessBoard.h"

// Basic ctor
AdvancedKing::AdvancedKing(Team team, PieceDirection pieceDirection, bool hasMoved) :
    ComplicatedCloneable<Piece, King, AdvancedKing>(PieceLevel::ADVANCED, team, pieceDirection, hasMoved) {}

// Copy ctor
AdvancedKing::AdvancedKing(AdvancedKing const &other) : 
    ComplicatedCloneable<Piece, King, AdvancedKing>(other) {}

// Move ctor
AdvancedKing::AdvancedKing(AdvancedKing &&other) noexcept : 
    ComplicatedCloneable<Piece, King, AdvancedKing>(std::move(other)) {}

// Copy assignment
AdvancedKing& AdvancedKing::operator=(AdvancedKing const &other) {
    if (this != &other) {
        King::operator=(other);
    }
    return *this;
}

// Move assignment
AdvancedKing& AdvancedKing::operator=(AdvancedKing &&other) noexcept {
    if (this != &other) {
        King::operator=(std::move(other));
    }
    return *this;
}

std::vector<std::unique_ptr<BoardMove>> AdvancedKing::getMovesImpl(std::unique_ptr<ChessBoard> const &chessBoard, BoardSquare const &fromSquare, bool onlyAttackingMoves) const {
    std::vector<BoardSquare> const additionalToSquares = { 
        BoardSquare(fromSquare.boardRow + 2, fromSquare.boardCol + 2),
        BoardSquare(fromSquare.boardRow + 2, fromSquare.boardCol - 2),
        BoardSquare(fromSquare.boardRow - 2, fromSquare.boardCol + 2),
        BoardSquare(fromSquare.boardRow - 2, fromSquare.boardCol - 2)
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
