// King.h

#ifndef King_h
#define King_h

#include <vector>

#include "Constants.h"
#include "Piece.h"
#include "Move.h"

class BoardPieceInterface;

class King : public Piece {
private:
    std::vector<Move> getMovesImplementation(BoardPieceInterface const &board, int pieceRow, int pieceCol, bool attackingMoves) const override;
    static std::vector<std::pair<int, int>> const kingDirections;
public:
    King(Color pieceColor, PieceDirection pieceDirection, bool hasMoved, int pieceScore = 1000);
};


#endif /* King_h */
