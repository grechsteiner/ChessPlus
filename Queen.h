// Queen.h

#ifndef Queen_h
#define Queen_h

#include <vector>
#include <utility>
#include <set>

#include "Constants.h"
#include "Piece.h"
#include "PieceCloneable.h"

class ChessBoard;
class BoardSquare;
class BoardMove;


/**
 * Queen Piece Class
 */
class Queen : public Cloneable<Piece, Queen> {
private:
    static std::set<std::pair<int, int>> const queenDirections;
    std::vector<BoardMove> getMovesImpl(ChessBoard const &chessBoard, BoardSquare const &fromSquare, bool onlyAttackingMoves) const override;
public:
    explicit Queen(Team team, PieceDirection pieceDirection, bool hasMoved, int pieceScore = 9);
    Queen(Queen const &other);
    Queen(Queen &&other) noexcept;
    Queen& operator=(Queen const &other);
    Queen& operator=(Queen &&other) noexcept;
    virtual ~Queen() = default;
};


#endif /* Queen_h */
