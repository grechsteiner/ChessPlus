// Empty.h

#ifndef Empty_h
#define Empty_h

#include <vector>

#include "ChessBoard.h"
#include "Constants.h"
#include "Piece.h"


class ChessBoard;

class Empty : public Piece {
private:
    std::vector<BoardMove> getMovesImplementation(ChessBoard const &board, BoardSquare const &boardSquare, bool attackingMoves) const override;
public:
    Empty(Color pieceColor = Color::NONE, PieceDirection pieceDirection = PieceDirection::BLANK, bool hasMoved = false, int pieceScore = 0);
};


#endif /* Empty_h */
