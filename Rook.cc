// Rook.cc

#include <vector>
#include <cassert>

#include "Constants.h"
#include "Rook.h"
#include "BoardPieceInterface.h"
#include "Piece.h"
#include "Move.h"

std::vector<std::pair<int, int>> const Rook::rookDirections = { 
    {-1, 0}, 
    {0, -1}, 
    {0, 1}, 
    {1, 0}, 
};

Rook::Rook(Color pieceColor, PieceDirection pieceDirection, bool hasMoved, int pieceScore) :
    Piece(pieceColor, PieceType::ROOK, pieceDirection, hasMoved, "♜", "R", pieceScore) {}

std::vector<Move> Rook::getMovesImplementation(BoardPieceInterface const &board, int pieceRow, int pieceCol, bool attackingMoves) const {
    std::vector<Move> moves;

    for (std::pair<int, int> const &rookDirection : rookDirections) {
        int newRow = pieceRow + rookDirection.first;
        int newCol = pieceCol + rookDirection.second;
        while (board.isEmptySquareOrOpposingColorOnBoard(newRow, newCol, pieceColor)) {
            moves.emplace_back(Move(board.getNumRows(), pieceRow, pieceCol, newRow, newCol));

            // If we ran into a piece of the opposite color, don't look past it
            if (board.isOpposingColorOnBoard(newRow, newCol, pieceColor)) {
                break;
            }
            
            newRow += rookDirection.first;
            newCol += rookDirection.second;
        }
    }
    return moves;
}
