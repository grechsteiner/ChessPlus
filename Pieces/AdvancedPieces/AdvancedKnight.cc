// AdvancedKnight.cc

#include "AdvancedKnight.h"

#include <memory>
#include <utility>
#include <vector>

#include "BoardMove.h"
#include "BoardMoveFactory.h"
#include "BoardSquare.h"
#include "ChessBoard.h"
#include "Constants.h"
#include "Knight.h"
#include "Piece.h"


// Basic ctor
AdvancedKnight::AdvancedKnight(Team team, PieceDirection pieceDirection, bool hasMoved) :
    ComplicatedCloneable<Piece, Knight, AdvancedKnight>(PieceLevel::ADVANCED, team, pieceDirection, hasMoved, char32_t(U'♘')) { }

// Copy ctor
AdvancedKnight::AdvancedKnight(AdvancedKnight const &other) : 
    ComplicatedCloneable<Piece, Knight, AdvancedKnight>(other) { }

// Move ctor
AdvancedKnight::AdvancedKnight(AdvancedKnight &&other) noexcept : 
    ComplicatedCloneable<Piece, Knight, AdvancedKnight>(std::move(other)) { }

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

/*
 * Returns all pseudo legal moves for an AdvancedKnight Knight Piece
 */
std::vector<std::unique_ptr<BoardMove>> AdvancedKnight::getMovesImpl(std::unique_ptr<ChessBoard> const &chessBoard, BoardSquare const &fromSquare, bool onlyAttackingMoves) const {
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
    if (chessBoard->isSquareOnBoard(fromSquare)) {
        for (BoardSquare const &toSquare : additionalToSquares) {
            if (chessBoard->isSquareEmpty(toSquare) || chessBoard->isSquareOtherTeam(toSquare, pieceData.team)) {
                moves.emplace_back(BoardMoveFactory::createStandardMove(fromSquare, toSquare, toSquare, false, pieceData, chessBoard->getPieceDataAt(toSquare)));
            }
        }
    }
    return moves;
}
