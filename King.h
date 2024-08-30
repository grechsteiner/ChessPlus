// King.h

#ifndef King_h
#define King_h

#include <vector>

#include "Constants.h"
#include "Piece.h"


class ChessBoard;

class King : public Piece {
private:
    std::vector<BoardMove> getMovesImplementation(ChessBoard const &board, BoardSquare const &boardSquare, bool onlyAttackingMoves) const override;
    static std::vector<std::pair<int, int>> const kingDirections;
public:
    King(Color pieceColor, PieceDirection pieceDirection, bool hasMoved, int pieceScore = 1000);
};


#endif /* King_h */
