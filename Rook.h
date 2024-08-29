// Rook.h

#ifndef Rook_h
#define Rook_h

#include <vector>

#include "Constants.h"
#include "Piece.h"
#include "FullMove.h"

class ChessBoard;

class Rook : public Piece {
private:
    std::vector<FullMove> getMovesImplementation(ChessBoard const &board, int pieceRow, int pieceCol, bool attackingMoves) const override;
    static std::vector<std::pair<int, int>> const rookDirections;
public:
    Rook(Color pieceColor, PieceDirection pieceDirection, bool hasMoved, int pieceScore = 5);
};


#endif /* Rook_h */
