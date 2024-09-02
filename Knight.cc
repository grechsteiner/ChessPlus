// Knight.cc

#include <vector>
#include <utility>
#include <set>

#include "Knight.h"
#include "Constants.h"
#include "Piece.h"
#include "ChessBoard.h"
#include "BoardSquare.h"
#include "BoardMove.h"


// Static
std::set<std::pair<int, int>> const Knight::knightDirections = { 
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

std::vector<BoardMove> Knight::getMovesImpl(ChessBoard const &chessBoard, BoardSquare const &fromSquare, bool onlyAttackingMoves) const {
    std::vector<BoardMove> moves;
    if (chessBoard.isSquareOnBoard(fromSquare)) {
        for (std::pair<int, int> const &knightDirection : knightDirections) {
            BoardSquare toSquare(fromSquare.getBoardRow() + knightDirection.first, fromSquare.getBoardCol() + knightDirection.second);
            if (chessBoard.isSquareEmpty(toSquare) || chessBoard.isSquareOtherTeam(toSquare, pieceInfo.getTeam())) {
                moves.emplace_back(BoardMove::createBasicMove(MoveType::STANDARD, pieceInfo, fromSquare, toSquare, toSquare, chessBoard.getPieceInfoAt(toSquare)));
            }
        }
    }
    return moves;
}
