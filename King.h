// King.h

#ifndef King_h
#define King_h

#include <vector>
#include <utility>
#include <set>

#include "Constants.h"
#include "Piece.h"

class ChessBoard;
class BoardSquare;
class BoardMove;


/**
 * King Piece Class
 */
class King : public Piece {
private:
    static std::set<std::pair<int, int>> const kingDirections;
    std::vector<BoardMove> getMovesImpl(ChessBoard const &chessBoard, BoardSquare const &fromSquare, bool onlyAttackingMoves) const override;
    bool checkCommonCastleInfo(ChessBoard const &chessBoard, BoardSquare const &fromSquare, BoardSquare const &toSquare, BoardSquare const &rookFromSquare, BoardSquare const &rookToSquare) const;
public:
    King(Team team, PieceDirection pieceDirection, bool hasMoved, int pieceScore = 1000);
};


#endif /* King_h */
