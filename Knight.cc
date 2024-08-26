// Knight.cc

#include <vector>
#include <cassert>

#include "Constants.h"
#include "Knight.h"
#include "BoardPieceInterface.h"
#include "Piece.h"
#include "Move.h"

std::vector<std::pair<int, int>> const Knight::knightDirections = { 
    {-1, -2}, 
    {-1, 2}, 
    {1, -2}, 
    {1, 2}, 
    {-2, -1}, 
    {-2, 1}, 
    {2, -1}, 
    {2, 1} 
};

Knight::Knight(Color pieceColor, PieceDirection pieceDirection, bool hasMoved, int pieceScore) :
    Piece(pieceColor, PieceType::KNIGHT, pieceDirection, hasMoved, "♞", "N", pieceScore) {}

std::vector<Move> Knight::getMovesImplementation(BoardPieceInterface const &board, int pieceRow, int pieceCol, bool attackingMoves) const {
    std::vector<Move> moves;
    for (std::pair<int, int> const &knightDirection : knightDirections) {
        int newRow = pieceRow + knightDirection.first;
        int newCol = pieceCol + knightDirection.second;
        if (board.isEmptySquareOrOpposingColorOnBoard(newRow, newCol, pieceColor)) {
            moves.emplace_back(Move(board.getNumRows(), pieceRow, pieceCol, newRow, newCol));
        }
    }
    return moves;
}
