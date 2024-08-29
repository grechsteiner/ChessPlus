// Empty.h

#ifndef Empty_h
#define Empty_h

#include <vector>

#include "ChessBoard.h"
#include "Constants.h"
#include "Piece.h"
#include "Move.h"

class ChessBoard;

class Empty : public Piece {
private:
    std::vector<FullMove> getMovesImplementation(ChessBoard const &board, int pieceRow, int pieceCol, bool attackingMoves) const override;
public:
    Empty(Color pieceColor = Color::NONE, PieceDirection pieceDirection = PieceDirection::BLANK, bool hasMoved = false, int pieceScore = 0);
};


#endif /* Empty_h */
