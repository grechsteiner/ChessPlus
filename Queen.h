// Queen.h

#ifndef Queen_h
#define Queen_h

#include <vector>
#include <utility>
#include <set>

#include "Constants.h"
#include "Piece.h"

class ChessBoard;
class BoardSquare;
class BoardMove;


/**
 * Queen Piece Class
 */
class Queen : public Piece {
private:
    static std::set<std::pair<int, int>> const queenDirections;
    std::vector<BoardMove> getMovesImpl(ChessBoard const &chessBoard, BoardSquare const &fromSquare, bool onlyAttackingMoves) const override;
public:
    Queen(Team team, PieceDirection pieceDirection, bool hasMoved, int pieceScore = 9);
};


#endif /* Queen_h */
