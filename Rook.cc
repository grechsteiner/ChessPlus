// Rook.cc

#include <vector>
#include <cassert>

#include "Constants.h"
#include "Rook.h"
#include "ChessBoard.h"
#include "Piece.h"
#include "BoardMove.h"

std::vector<std::pair<int, int>> const Rook::rookDirections = { 
    {-1, 0}, 
    {0, -1}, 
    {0, 1}, 
    {1, 0}, 
};

Rook::Rook(Color pieceColor, PieceDirection pieceDirection, bool hasMoved, int pieceScore) :
    Piece(pieceColor, PieceType::ROOK, pieceDirection, hasMoved, "♜", "R", pieceScore) {}

std::vector<BoardMove> Rook::getMovesImplementation(ChessBoard const &board, BoardSquare const &boardSquare, bool attackingMoves) const {
    std::vector<BoardMove> moves;

    for (std::pair<int, int> const &rookDirection : rookDirections) {
        int newRow = boardSquare.getBoardRow() + rookDirection.first;
        int newCol = boardSquare.getBoardCol() + rookDirection.second;
        while (board.isEmptySquareOrOpposingColorOnBoard(BoardSquare(newRow, newCol), pieceInfo.getPieceColor())) {
            moves.emplace_back(createBoardMove(board, boardSquare, BoardSquare(newRow, newCol), BoardSquare(newRow, newCol), MoveType::STANDARD, true));

            // If we ran into a piece of the opposite color, don't look past it
            if (board.isOpposingColorOnBoard(BoardSquare(newRow, newCol), pieceInfo.getPieceColor())) {
                break;
            }
            
            newRow += rookDirection.first;
            newCol += rookDirection.second;
        }
    }
    return moves;
}
