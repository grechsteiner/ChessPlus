// Rook.h

#ifndef Rook_h
#define Rook_h

#include <vector>

#include "Constants.h"
#include "Piece.h"
#include "Move.h"

class BoardPieceInterface;

class Rook : public Piece {
private:
    std::vector<Move> getMovesImplementation(BoardPieceInterface const &board, int pieceRow, int pieceCol, bool attackingMoves) const override;
    static std::vector<std::pair<int, int>> const rookDirections;
public:
    Rook(Color pieceColor, PieceDirection pieceDirection, bool hasMoved, int pieceScore = 5);
};


#endif /* Rook_h */
