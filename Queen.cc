// Queen.cc

#include <vector>
#include <utility>
#include <set>

#include "Queen.h"
#include "Constants.h"
#include "Piece.h"
#include "ChessBoard.h"
#include "BoardSquare.h"
#include "BoardMove.h"


// Static
std::set<std::pair<int, int>> const Queen::queenDirections = { 
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
    Piece(PieceType::QUEEN, team, pieceDirection, hasMoved, pieceScore, "♛", "Q") {}

std::vector<BoardMove> Queen::getMovesImpl(ChessBoard const &chessBoard, BoardSquare const &fromSquare, bool onlyAttackingMoves) const {
    std::vector<BoardMove> moves;
    if (chessBoard.isSquareOnBoard(fromSquare)) {
        for (std::pair<int, int> const &queenDirection : queenDirections) {
            BoardSquare toSquare(fromSquare.getBoardRow() + queenDirection.first, fromSquare.getBoardCol() + queenDirection.second);
            while (chessBoard.isSquareEmpty(toSquare) || chessBoard.isSquareOtherTeam(toSquare, pieceInfo.getTeam())) {
                moves.emplace_back(BoardMove::createBasicMove(MoveType::STANDARD, pieceInfo, fromSquare, toSquare, toSquare, chessBoard.getPieceInfoAt(toSquare)));
                if (chessBoard.isSquareOtherTeam(toSquare, pieceInfo.getTeam())) {
                    break;
                }
                toSquare = BoardSquare(toSquare.getBoardRow() + queenDirection.first, toSquare.getBoardCol() + queenDirection.second);
            }
        }
    }
    return moves;
}
