// Knight.cc

#include "Knight.h"

#include <memory>
#include <utility>
#include <vector>

#include "BoardMove.h"
#include "BoardMoveFactory.h"
#include "BoardSquare.h"
#include "ChessBoard.h"
#include "Constants.h"
#include "MoveDirection.h"
#include "Piece.h"


/*
 * Static
 *
 * The directions a Knight Piece can move
 */
std::vector<MoveDirection> const Knight::knightMoveDirections = { 
    { MoveDirection(-1, -2) }, 
    { MoveDirection(-1, 2) }, 
    { MoveDirection(1, -2) }, 
    { MoveDirection(1, 2) }, 
    { MoveDirection(-2, -1) }, 
    { MoveDirection(-2, 1) }, 
    { MoveDirection(2, -1) }, 
    { MoveDirection(2, 1) } 
};

// Basic ctor
Knight::Knight(PieceLevel pieceLevel, Team team, PieceDirection pieceDirection, bool hasMoved, char32_t image) :
    Piece(PieceData(PieceType::KNIGHT, pieceLevel, team, pieceDirection, hasMoved), PieceInfo(3, image)) {}

// Copy ctor
Knight::Knight(Knight const &other) : 
    Piece(other) {}

// Move ctor
Knight::Knight(Knight &&other) noexcept : 
    Piece(std::move(other)) {}

// Copy assignment
Knight& Knight::operator=(Knight const &other) {
    if (this != &other) {
        Piece::operator=(other);
    }
    return *this;
}

// Move assignment
Knight& Knight::operator=(Knight &&other) noexcept {
    if (this != &other) {
        Piece::operator=(std::move(other));
    }
    return *this;
}

/*
 * Returns all pseudo legal standard moves for a Knight Piece
 */
std::vector<std::unique_ptr<BoardMove>> Knight::getStandardMoves(std::unique_ptr<ChessBoard> const &chessBoard, BoardSquare const &fromSquare, bool onlyAttackingMoves) const {
    std::vector<std::unique_ptr<BoardMove>> moves;
    if (chessBoard->isSquareOnBoard(fromSquare)) {
        for (MoveDirection const &knightMoveDirection : knightMoveDirections) {
            BoardSquare toSquare(fromSquare.boardRow + knightMoveDirection.rowDirection, fromSquare.boardCol + knightMoveDirection.colDirection);
            if (chessBoard->isSquareEmpty(toSquare) || chessBoard->isSquareOtherTeam(toSquare, pieceData.team)) {
                moves.emplace_back(BoardMoveFactory::createStandardMove(fromSquare, toSquare, toSquare, false, pieceData, chessBoard->getPieceDataAt(toSquare)));
            }
        }
    }
    return moves;
}
