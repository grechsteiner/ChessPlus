// Rook.h

#ifndef Rook_h
#define Rook_h

#include <vector>
#include <utility>
#include <set>

#include "Constants.h"
#include "Piece.h"

class ChessBoard;
class BoardSquare;
class BoardMove;


/**
 * Rook Piece Class
 */
class Rook : public Piece {
private:
    static std::set<std::pair<int, int>> const rookDirections;
    std::vector<BoardMove> getMovesImpl(ChessBoard const &chessBoard, BoardSquare const &fromSquare, bool onlyAttackingMoves) const override;
public:
    Rook(Team team, PieceDirection pieceDirection, bool hasMoved, int pieceScore = 5);
};


#endif /* Rook_h */
