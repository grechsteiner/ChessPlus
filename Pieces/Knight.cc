// Knight.cc

#include <vector>
#include <utility>
#include <set>

#include "Knight.h"
#include "Constants.h"
#include "Piece.h"
#include "Cloneable.h"
#include "ChessBoard.h"
#include "BoardSquare.h"
#include "BoardMove.h"
#include "BoardMoveFactory.h"


// Static
std::set<std::pair<int, int>> const Knight::knightDirections = { 
    {-1, -2}, 
    {-1, 2}, 
    {1, -2}, 
    {1, 2}, 
    {-2, -1}, 
    {-2, 1}, 
    {2, -1}, 
    {2, 1} 
};

// Basic ctor
Knight::Knight(PieceLevel pieceLevel, Team team, PieceDirection pieceDirection, bool hasMoved) :
    Piece(PieceData(PieceType::KNIGHT, pieceLevel, team, pieceDirection, hasMoved), PieceInfo(3, "♞", "N")) {}

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

std::vector<std::unique_ptr<BoardMove>> Knight::getStandardMoves(std::unique_ptr<ChessBoard> const &chessBoard, BoardSquare const &fromSquare, bool onlyAttackingMoves) const {
    std::vector<std::unique_ptr<BoardMove>> moves;
    if (chessBoard->isSquareOnBoard(fromSquare)) {
        for (std::pair<int, int> const &knightDirection : knightDirections) {
            BoardSquare toSquare(fromSquare.boardRow + knightDirection.first, fromSquare.boardCol + knightDirection.second);
            if (chessBoard->isSquareEmpty(toSquare) || chessBoard->isSquareOtherTeam(toSquare, pieceData.team)) {
                moves.emplace_back(BoardMoveFactory::createStandardMove(fromSquare, toSquare, toSquare, false, pieceData, chessBoard->getPieceDataAt(toSquare)));
            }
        }
    }
    return moves;
}
