// Queen.cc

#include <vector>
#include <cassert>

#include "Constants.h"
#include "Queen.h"
#include "ChessBoard.h"
#include "Piece.h"


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

std::vector<BoardMove> Queen::getMovesImplementation(ChessBoard const &board, BoardSquare const &boardSquare, bool attackingMoves) const {
    std::vector<BoardMove> moves;

    for (std::pair<int, int> const &queenDirection : queenDirections) {
        int newRow = boardSquare.getBoardRow() + queenDirection.first;
        int newCol = boardSquare.getBoardCol() + queenDirection.second;
        while (board.isEmptySquareOrOpposingColorOnBoard(BoardSquare(newRow, newCol), pieceInfo.getPieceColor())) {
            moves.emplace_back(createBoardMove(board, boardSquare, BoardSquare(newRow, newCol), BoardSquare(newRow, newCol), MoveType::STANDARD, true));

            // If we ran into a piece of the opposite color, don't look past it
            if (board.isOpposingColorOnBoard(BoardSquare(newRow, newCol), pieceInfo.getPieceColor())) {
                break;
            }
            
            newRow += queenDirection.first;
            newCol += queenDirection.second;
        }
    }
    return moves;
}
