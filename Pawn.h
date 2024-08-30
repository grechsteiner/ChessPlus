// Pawn.h

#ifndef Pawn_h
#define Pawn_h

#include <vector>

#include "Constants.h"
#include "Piece.h"
#include "BoardMove.h"

class ChessBoard;

class Pawn : public Piece {
private:
    std::vector<BoardMove> getMovesImplementation(ChessBoard const &board, BoardSquare const &boardSquare, bool onlyAttackingMoves) const override;
    std::vector<BoardMove> getPromotionMoves(ChessBoard const &board, BoardMove const &move) const;
public:
    Pawn(Team team, PieceDirection pieceDirection, bool hasMoved, int pieceScore = 1);
};


#endif /* Pawn */
