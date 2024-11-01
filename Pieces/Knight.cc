// Knight.cc

#include <vector>
#include <utility>
#include <set>

#include "Knight.h"
#include "Constants.h"
#include "Piece.h"
#include "Cloneable.h"
#include "IChessBoard.h"
#include "BoardSquare.h"
#include "BoardMove.h"


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
    Piece(PieceInfo(PieceData(PieceType::KNIGHT, pieceLevel, team, pieceDirection, hasMoved), 3, "♞", "N")) {}

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

std::vector<BoardMove> Knight::getStandardMoves(IChessBoard const &chessBoard, BoardSquare const &fromSquare, bool onlyAttackingMoves) const {
    std::vector<BoardMove> moves;
    if (chessBoard.isSquareOnBoard(fromSquare)) {
        for (std::pair<int, int> const &knightDirection : knightDirections) {
            BoardSquare toSquare(fromSquare.getBoardRow() + knightDirection.first, fromSquare.getBoardCol() + knightDirection.second);
            if (chessBoard.isSquareEmpty(toSquare) || chessBoard.isSquareOtherTeam(toSquare, pieceInfo.pieceData.team)) {
                moves.emplace_back(BoardMove::createBasicMove(MoveType::STANDARD, pieceInfo.pieceData, fromSquare, toSquare, toSquare, chessBoard.getPieceInfoAt(toSquare)));
            }
        }
    }
    return moves;
}
