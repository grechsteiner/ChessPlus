// Rook.cc

#include "Rook.h"

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
 * The directions a Bishop Piece can move
 */
std::vector<MoveDirection> const Rook::rookMoveDirections = { 
    { MoveDirection(-1, 0) }, 
    { MoveDirection(0, -1) }, 
    { MoveDirection(0, 1) }, 
    { MoveDirection(1, 0) }, 
};

// Basic ctor
Rook::Rook(PieceLevel pieceLevel, Team team, PieceDirection pieceDirection, bool hasMoved, char32_t image) :
    Piece(PieceData(PieceType::ROOK, pieceLevel, team, pieceDirection, hasMoved), PieceInfo(5, image)) { }

// Copy ctor
Rook::Rook(Rook const &other) : 
    Piece(other) { }

// Move ctor
Rook::Rook(Rook &&other) noexcept : 
    Piece(std::move(other)) { }

// Copy assignment
Rook& Rook::operator=(Rook const &other) {
    if (this != &other) {
        Piece::operator=(other);
    }
    return *this;
}

// Move assignment
Rook& Rook::operator=(Rook &&other) noexcept {
    if (this != &other) {
        Piece::operator=(std::move(other));
    }
    return *this;
}

/*
 * Returns all pseudo legal standard moves for a Bishop Piece
 */
std::vector<std::unique_ptr<BoardMove>> Rook::getStandardMoves(std::unique_ptr<ChessBoard> const &chessBoard, BoardSquare const &fromSquare, bool onlyAttackingMoves) const {
    std::vector<std::unique_ptr<BoardMove>> moves;
    if (chessBoard->isSquareOnBoard(fromSquare)) {
        for (MoveDirection const &rookMoveDirection : rookMoveDirections) {
            BoardSquare toSquare(fromSquare.boardRow + rookMoveDirection.rowDirection, fromSquare.boardCol + rookMoveDirection.colDirection);
            while (chessBoard->isSquareEmpty(toSquare) || chessBoard->isSquareOtherTeam(toSquare, pieceData.team)) {
                moves.emplace_back(BoardMoveFactory::createStandardMove(fromSquare, toSquare, toSquare, false, pieceData, chessBoard->getPieceDataAt(toSquare)));
                if (chessBoard->isSquareOtherTeam(toSquare, pieceData.team)) {
                    break;
                }
                toSquare.boardRow += rookMoveDirection.rowDirection;
                toSquare.boardCol += rookMoveDirection.colDirection;
            }
        }
    }
    return moves;
}
