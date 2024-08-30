// Knight.cc

#include <vector>
#include <cassert>

#include "Constants.h"
#include "Knight.h"
#include "ChessBoard.h"
#include "Piece.h"
#include "BoardMove.h"

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

std::vector<BoardMove> Knight::getMovesImplementation(ChessBoard const &board, BoardSquare const &boardSquare, bool onlyAttackingMoves) const {
    std::vector<BoardMove> moves;
    for (std::pair<int, int> const &knightDirection : knightDirections) {
        int newRow = boardSquare.getBoardRow() + knightDirection.first;
        int newCol = boardSquare.getBoardCol() + knightDirection.second;
        if (board.isEmptySquareOrOpposingColorOnBoard(BoardSquare(newRow, newCol), pieceInfo.pieceColor)) {
            moves.emplace_back(createBoardMove(board, boardSquare, BoardSquare(newRow, newCol), BoardSquare(newRow, newCol), MoveType::STANDARD, true));
        }
    }
    return moves;
}
