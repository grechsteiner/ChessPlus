// Bishop.cc

#include "Bishop.h"

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
 * The directions a bishop can move
 */
std::vector<MoveDirection> const Bishop::bishopMoveDirections = { 
    { MoveDirection(-1, -1) },  
    { MoveDirection(-1,  1) }, 
    { MoveDirection(1, -1) }, 
    { MoveDirection(1,  1) } 
};

// Basic ctor
Bishop::Bishop(PieceLevel pieceLevel, Team team, PieceDirection pieceDirection, bool hasMoved, char32_t image) :
    Piece(PieceData(PieceType::BISHOP, pieceLevel, team, pieceDirection, hasMoved), PieceInfo(3, image)) { }

// Copy ctor
Bishop::Bishop(Bishop const &other) : 
    Piece(other) { }

// Move ctor
Bishop::Bishop(Bishop &&other) noexcept : 
    Piece(std::move(other)) { }

// Copy assignment
Bishop& Bishop::operator=(Bishop const &other) {
    if (this != &other) {
        Piece::operator=(other);
    }
    return *this;
}

// Move assignment
Bishop& Bishop::operator=(Bishop &&other) noexcept {
    if (this != &other) {
        Piece::operator=(std::move(other));
    }
    return *this;
}

/*
 * Returns all pseudo legal standard moves for a Bishop Piece
 */
std::vector<std::unique_ptr<BoardMove>> Bishop::getStandardMoves(std::unique_ptr<ChessBoard> const &chessBoard, BoardSquare const &fromSquare, bool onlyAttackingMoves) const {
    std::vector<std::unique_ptr<BoardMove>> moves;
    if (chessBoard->isSquareOnBoard(fromSquare)) {
        for (MoveDirection const &bishopMoveDirection : bishopMoveDirections) {
            BoardSquare toSquare(fromSquare.boardRow + bishopMoveDirection.rowDirection, fromSquare.boardCol + bishopMoveDirection.colDirection);
            while (chessBoard->isSquareEmpty(toSquare) || chessBoard->isSquareOtherTeam(toSquare, pieceData.team)) {
                moves.emplace_back(BoardMoveFactory::createStandardMove(fromSquare, toSquare, toSquare, false, pieceData, chessBoard->getPieceDataAt(toSquare)));
                if (chessBoard->isSquareOtherTeam(toSquare, pieceData.team)) {
                    break;
                }
                toSquare.boardRow += bishopMoveDirection.rowDirection;
                toSquare.boardCol += bishopMoveDirection.colDirection;
            }
        }
    }
    return moves;
}
