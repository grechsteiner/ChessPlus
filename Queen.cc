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

Queen::Queen(Team team, PieceDirection pieceDirection, bool hasMoved, int pieceScore) :
    Piece(team, PieceType::QUEEN, pieceDirection, hasMoved, "♛", "Q", pieceScore) {}

std::vector<BoardMove> Queen::getMovesImplementation(ChessBoard const &board, BoardSquare const &boardSquare, bool onlyAttackingMoves) const {
    std::vector<BoardMove> moves;

    for (std::pair<int, int> const &queenDirection : queenDirections) {
        int newRow = boardSquare.getBoardRow() + queenDirection.first;
        int newCol = boardSquare.getBoardCol() + queenDirection.second;
        BoardSquare newBoardSquare(newRow, newCol);
        while (board.isSquareEmpty(newBoardSquare) || board.isSquareOtherTeam(newBoardSquare, pieceInfo.team)) {
            moves.emplace_back(createBoardMove(board, boardSquare, newBoardSquare, newBoardSquare, MoveType::STANDARD, true));

            // If we ran into a piece of the opposite color, don't look past it
            if (board.isSquareOtherTeam(newBoardSquare, pieceInfo.team)) {
                break;
            }
            
            newRow += queenDirection.first;
            newCol += queenDirection.second;
            newBoardSquare = BoardSquare(newRow + queenDirection.first, newCol + queenDirection.second);
        }
    }
    return moves;
}
