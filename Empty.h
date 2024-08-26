// Empty.h

#ifndef Empty_h
#define Empty_h

#include <vector>

#include "BoardPieceInterface.h"
#include "Constants.h"
#include "Piece.h"
#include "Move.h"

class BoardPieceInterface;

class Empty : public Piece {
private:
    std::vector<Move> getMovesImplementation(BoardPieceInterface const &board, int pieceRow, int pieceCol, bool attackingMoves) const override;
public:
    Empty(Color pieceColor = Color::NONE, PieceDirection pieceDirection = PieceDirection::BLANK, bool hasMoved = false, int pieceScore = 0);
};


#endif /* Empty_h */
