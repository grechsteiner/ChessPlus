// Knight.h

#ifndef Knight_h
#define Knight_h

#include <vector>
#include <utility>
#include <set>

#include "Constants.h"
#include "Piece.h"

class ChessBoard;
class BoardSquare;
class BoardMove;


/**
 * Knight Piece Class
 */
class Knight : public Piece {
private:
    static std::set<std::pair<int, int>> const knightDirections;
    std::vector<BoardMove> getMovesImpl(ChessBoard const &chessBoard, BoardSquare const &fromSquare, bool onlyAttackingMoves) const override;
public:
    Knight(Team team, PieceDirection pieceDirection, bool hasMoved, int pieceScore = 3);
};


#endif /* Knight_h */
