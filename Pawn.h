// Pawn.h

#ifndef Pawn_h
#define Pawn_h

#include <vector>

#include "Constants.h"
#include "Piece.h"
#include "Move.h"

class BoardPieceInterface;

class Pawn : public Piece {
private:
    std::vector<Move> getMovesImplementation(BoardPieceInterface const &board, int pieceRow, int pieceCol, bool attackingMoves) const override;
    std::vector<Move> getPromotionMoves(BoardPieceInterface const &board, Move const &move) const;
public:
    Pawn(Color pieceColor, PieceDirection pieceDirection, bool hasMoved, int pieceScore = 1);
};


#endif /* Pawn */
