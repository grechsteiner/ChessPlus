// Bishop.cc

#include <vector>
#include <cassert>

#include "Constants.h"
#include "Bishop.h"
#include "ChessBoard.h"
#include "Piece.h"


std::vector<std::pair<int, int>> const Bishop::bishopDirections = { 
    {-1, -1},  
    {-1, 1}, 
    {1, -1}, 
    {1, 1} 
};

Bishop::Bishop(Team team, PieceDirection pieceDirection, bool hasMoved, int pieceScore) :
    Piece(PieceType::BISHOP, team, pieceDirection, hasMoved, pieceScore, "♝", "B") {}

std::vector<BoardMove> Bishop::getMovesImplementation(ChessBoard const &board, BoardSquare const &boardSquare, bool onlyAttackingMoves) const {
    std::vector<BoardMove> moves;
    for (std::pair<int, int> const &bishopDirection : bishopDirections) {
        int newRow = boardSquare.getBoardRow() + bishopDirection.first;
        int newCol = boardSquare.getBoardCol() + bishopDirection.second;
        BoardSquare newBoardSquare(newRow, newCol);
        while (board.isSquareEmpty(newBoardSquare) || board.isSquareOtherTeam(newBoardSquare, pieceInfo.team)) {
            createAndAppendBoardMove(moves, board, boardSquare, newBoardSquare, newBoardSquare, MoveType::STANDARD, true);

            // If we ran into a piece of the opposite color, don't look past it
            if (board.isSquareOtherTeam(newBoardSquare, pieceInfo.team)) {
                break;
            }
            
            // Keep incrementing
            newRow += bishopDirection.first;
            newCol += bishopDirection.second;
            newBoardSquare = BoardSquare(newRow + bishopDirection.first, newCol + bishopDirection.second);
        }
    }
    return moves;
}
