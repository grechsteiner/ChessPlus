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

Rook::Rook(Team team, PieceDirection pieceDirection, bool hasMoved, int pieceScore) :
    Piece(team, PieceType::ROOK, pieceDirection, hasMoved, "♜", "R", pieceScore) {}

std::vector<BoardMove> Rook::getMovesImplementation(ChessBoard const &board, BoardSquare const &boardSquare, bool onlyAttackingMoves) const {
    std::vector<BoardMove> moves;

    for (std::pair<int, int> const &rookDirection : rookDirections) {
        int newRow = boardSquare.getBoardRow() + rookDirection.first;
        int newCol = boardSquare.getBoardCol() + rookDirection.second;
        while (board.isEmptySquareOrOpposingTeamOnBoard(BoardSquare(newRow, newCol), pieceInfo.team)) {
            moves.emplace_back(createBoardMove(board, boardSquare, BoardSquare(newRow, newCol), BoardSquare(newRow, newCol), MoveType::STANDARD, true));

            // If we ran into a piece of the opposite color, don't look past it
            if (board.isOpposingTeamOnBoard(BoardSquare(newRow, newCol), pieceInfo.team)) {
                break;
            }
            
            newRow += rookDirection.first;
            newCol += rookDirection.second;
        }
    }
    return moves;
}
