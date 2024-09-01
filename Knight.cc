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

Knight::Knight(Team team, PieceDirection pieceDirection, bool hasMoved, int pieceScore) :
    Piece(PieceType::KNIGHT, team, pieceDirection, hasMoved, pieceScore, "♞", "N") {}

std::vector<BoardMove> Knight::getMovesImplementation(ChessBoard const &board, BoardSquare const &boardSquare, bool onlyAttackingMoves) const {
    std::vector<BoardMove> moves;
    for (std::pair<int, int> const &knightDirection : knightDirections) {
        int newRow = boardSquare.getBoardRow() + knightDirection.first;
        int newCol = boardSquare.getBoardCol() + knightDirection.second;
        BoardSquare newBoardSquare(newRow, newCol);
        if (board.isSquareEmpty(newBoardSquare) || board.isSquareOtherTeam(newBoardSquare, pieceInfo.team)) {
            createAndAppendBoardMove(moves, board, boardSquare, newBoardSquare, newBoardSquare, MoveType::STANDARD, true);
        }
    }
    return moves;
}
