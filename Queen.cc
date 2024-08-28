// Queen.cc

#include <vector>
#include <cassert>

#include "Constants.h"
#include "Queen.h"
#include "BoardPieceInterface.h"
#include "Piece.h"
#include "Move.h"

std::vector<std::pair<int, int>> const Queen::queenDirections = { 
    {-1, -1}, 
    {-1, 0}, 
    {-1, 1}, 
    {0, -1}, 
    {0, 1}, 
    {1, -1}, 
    {1, 0}, 
    {1, 1} 
};

Queen::Queen(Color pieceColor, PieceDirection pieceDirection, bool hasMoved, int pieceScore) :
    Piece(pieceColor, PieceType::QUEEN, pieceDirection, hasMoved, "♛", "Q", pieceScore) {}

std::vector<FullMove> Queen::getMovesImplementation(BoardPieceInterface const &board, int pieceRow, int pieceCol, bool attackingMoves) const {
    std::vector<FullMove> moves;

    for (std::pair<int, int> const &queenDirection : queenDirections) {
        int newRow = pieceRow + queenDirection.first;
        int newCol = pieceCol + queenDirection.second;
        while (board.isEmptySquareOrOpposingColorOnBoard(newRow, newCol, pieceColor)) {
            moves.emplace_back(createFullMove(board, pieceRow, pieceCol, newRow, newCol, newRow, newCol, MoveType::STANDARD, true));

            // If we ran into a piece of the opposite color, don't look past it
            if (board.isOpposingColorOnBoard(newRow, newCol, pieceColor)) {
                break;
            }
            
            newRow += queenDirection.first;
            newCol += queenDirection.second;
        }
    }
    return moves;
}
