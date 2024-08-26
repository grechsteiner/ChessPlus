// Queen.h

#ifndef Queen_h
#define Queen_h

#include <vector>

#include "Constants.h"
#include "Piece.h"
#include "Move.h"

class BoardPieceInterface;

class Queen : public Piece {
private:
    std::vector<Move> getMovesImplementation(BoardPieceInterface const &board, int pieceRow, int pieceCol, bool attackingMoves) const override;
    static std::vector<std::pair<int, int>> const queenDirections;
public:
    Queen(Color pieceColor, PieceDirection pieceDirection, bool hasMoved, int pieceScore = 9);
};


#endif /* Queen_h */
