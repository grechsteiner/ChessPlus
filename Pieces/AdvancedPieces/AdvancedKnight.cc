// AdvancedKnight.cc

#include <vector>

#include "AdvancedKnight.h"
#include "BoardMove.h"
#include "BoardMoveFactory.h"
#include "ChessBoard.h"

// Basic ctor
AdvancedKnight::AdvancedKnight(Team team, PieceDirection pieceDirection, bool hasMoved) :
    ComplicatedCloneable<Piece, Knight, AdvancedKnight>(PieceLevel::BASIC, team, pieceDirection, hasMoved) {}

// Copy ctor
AdvancedKnight::AdvancedKnight(AdvancedKnight const &other) : 
    ComplicatedCloneable<Piece, Knight, AdvancedKnight>(other) {}

// Move ctor
AdvancedKnight::AdvancedKnight(AdvancedKnight &&other) noexcept : 
    ComplicatedCloneable<Piece, Knight, AdvancedKnight>(std::move(other)) {}

// Copy assignment
AdvancedKnight& AdvancedKnight::operator=(AdvancedKnight const &other) {
    if (this != &other) {
        Knight::operator=(other);
    }
    return *this;
}

// Move assignment
AdvancedKnight& AdvancedKnight::operator=(AdvancedKnight &&other) noexcept {
    if (this != &other) {
        Knight::operator=(std::move(other));
    }
    return *this;
}

std::vector<std::unique_ptr<BoardMove>> AdvancedKnight::getMovesImpl(ChessBoard const &chessBoard, BoardSquare const &fromSquare, bool onlyAttackingMoves) const {
    std::vector<BoardSquare> const additionalToSquares = { 
        BoardSquare(fromSquare.boardRow + 1, fromSquare.boardCol + 3),
        BoardSquare(fromSquare.boardRow + 1, fromSquare.boardCol - 3),
        BoardSquare(fromSquare.boardRow - 1, fromSquare.boardCol + 3),
        BoardSquare(fromSquare.boardRow - 1, fromSquare.boardCol - 3),
        BoardSquare(fromSquare.boardRow + 3, fromSquare.boardCol + 1),
        BoardSquare(fromSquare.boardRow + 3, fromSquare.boardCol - 1),
        BoardSquare(fromSquare.boardRow - 3, fromSquare.boardCol + 1),
        BoardSquare(fromSquare.boardRow - 3, fromSquare.boardCol - 1)
    };

    std::vector<std::unique_ptr<BoardMove>> moves = getStandardMoves(chessBoard, fromSquare, onlyAttackingMoves);
    if (chessBoard.isSquareOnBoard(fromSquare)) {
        for (BoardSquare const &toSquare : additionalToSquares) {
            if (chessBoard.isSquareEmpty(toSquare) || chessBoard.isSquareOtherTeam(toSquare, pieceData.team)) {
                moves.emplace_back(BoardMoveFactory::createStandardMove(fromSquare, toSquare, toSquare, false, pieceData, chessBoard.getPieceDataAt(toSquare)));
            }
        }
    }
    return moves;
}
