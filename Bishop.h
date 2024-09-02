// Bishop.h

#ifndef Bishop_h
#define Bishop_h

#include <vector>
#include <utility>
#include <set>

#include "Constants.h"
#include "Piece.h"

class ChessBoard;
class BoardSquare;
class BoardMove;


/**
 * Bishop Piece Class
 */
class Bishop : public Piece {
private:
    static std::set<std::pair<int, int>> const bishopDirections;
    std::vector<BoardMove> getMovesImpl(ChessBoard const &chessBoard, BoardSquare const &fromSquare, bool onlyAttackingMoves) const override;
public:
    Bishop(Team team, PieceDirection pieceDirection, bool hasMoved, int pieceScore = 3);
};


#endif /* Bishop_h */
