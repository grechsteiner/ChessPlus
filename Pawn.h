// Pawn.h

#ifndef Pawn_h
#define Pawn_h

#include <vector>
#include <utility>

#include "Constants.h"
#include "Piece.h"

class ChessBoard;
class BoardSquare;
class BoardMove;


/**
 * Pawn Piece Class
 */
class Pawn : public Piece {
private:
    std::pair<int, int> pawnDirection;
    std::vector<BoardMove> getMovesImpl(ChessBoard const &chessBoard, BoardSquare const &fromSquare, bool onlyAttackingMoves) const override;
    std::vector<BoardMove> createPromotionMoves(BoardMove const &move) const;
public:
    Pawn(Team team, PieceDirection pieceDirection, bool hasMoved, int pieceScore = 1);
};


#endif /* Pawn */
