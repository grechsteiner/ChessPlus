// Rook.cc

#include <vector>
#include <cassert>

#include "Constants.h"
#include "Rook.h"
#include "BoardPieceInterface.h"
#include "Piece.h"
#include "FullMove.h"

std::vector<std::pair<int, int>> const Rook::rookDirections = { 
    {-1, 0}, 
    {0, -1}, 
    {0, 1}, 
    {1, 0}, 
};

Rook::Rook(Color pieceColor, PieceDirection pieceDirection, bool hasMoved, int pieceScore) :
    Piece(pieceColor, PieceType::ROOK, pieceDirection, hasMoved, "♜", "R", pieceScore) {}

std::vector<FullMove> Rook::getMovesImplementation(BoardPieceInterface const &board, int pieceRow, int pieceCol, bool attackingMoves) const {
    std::vector<FullMove> moves;

    for (std::pair<int, int> const &rookDirection : rookDirections) {
        int newRow = pieceRow + rookDirection.first;
        int newCol = pieceCol + rookDirection.second;
        while (board.isEmptySquareOrOpposingColorOnBoard(newRow, newCol, pieceColor)) {
            moves.emplace_back(createFullMove(board, pieceRow, pieceCol, newRow, newCol, newRow, newCol, MoveType::STANDARD, true));

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
