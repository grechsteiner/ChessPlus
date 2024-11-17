// Queen.cc

#include "Queen.h"

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
 * The directions a Queen Piece can move
 */
std::vector<MoveDirection> const Queen::queenMoveDirections = { 
    { MoveDirection(-1, -1) }, 
    { MoveDirection(-1, 0) }, 
    { MoveDirection(-1, 1) }, 
    { MoveDirection(0, -1) }, 
    { MoveDirection(0, 1) }, 
    { MoveDirection(1, -1) }, 
    { MoveDirection(1, 0) }, 
    { MoveDirection(1, 1) } 
};

// Basic ctor
Queen::Queen(PieceLevel pieceLevel, Team team, PieceDirection pieceDirection, bool hasMoved, char32_t image) :
    Piece(PieceData(PieceType::QUEEN, pieceLevel, team, pieceDirection, hasMoved), PieceInfo(9, image)) {}

// Copy ctor
Queen::Queen(Queen const &other) : 
    Piece(other) {}

// Move ctor
Queen::Queen(Queen &&other) noexcept : 
    Piece(std::move(other)) {}

// Copy assignment
Queen& Queen::operator=(Queen const &other) {
    if (this != &other) {
        Piece::operator=(other);
    }
    return *this;
}

// Move assignment
Queen& Queen::operator=(Queen &&other) noexcept {
    if (this != &other) {
        Piece::operator=(std::move(other));
    }
    return *this;
}

/*
 * Returns all pseudo legal standard moves for a Queen Piece
 */
std::vector<std::unique_ptr<BoardMove>> Queen::getStandardMoves(std::unique_ptr<ChessBoard> const &chessBoard, BoardSquare const &fromSquare, bool onlyAttackingMoves) const {
    std::vector<std::unique_ptr<BoardMove>> moves;
    if (chessBoard->isSquareOnBoard(fromSquare)) {
        for (MoveDirection const &queenMoveDirection : queenMoveDirections) {
            BoardSquare toSquare(fromSquare.boardRow + queenMoveDirection.rowDirection, fromSquare.boardCol + queenMoveDirection.colDirection);
            while (chessBoard->isSquareEmpty(toSquare) || chessBoard->isSquareOtherTeam(toSquare, pieceData.team)) {
                moves.emplace_back(BoardMoveFactory::createStandardMove(fromSquare, toSquare, toSquare, false, pieceData, chessBoard->getPieceDataAt(toSquare)));
                if (chessBoard->isSquareOtherTeam(toSquare, pieceData.team)) {
                    break;
                }
                toSquare.boardRow += queenMoveDirection.rowDirection;
                toSquare.boardCol += queenMoveDirection.colDirection;
            }
        }
    }
    return moves;
}
