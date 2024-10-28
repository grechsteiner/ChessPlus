// Knight.h

#ifndef Knight_h
#define Knight_h

#include <vector>
#include <utility>
#include <set>

#include "Constants.h"
#include "Piece.h"
#include "Cloneable.h"

class IChessBoard;
class BoardSquare;
class BoardMove;


/**
 * Knight Piece Class
 */
class Knight : public Cloneable<Piece, Knight> {
private:
    static std::set<std::pair<int, int>> const knightDirections;
    std::vector<BoardMove> getMovesImpl(IChessBoard const &chessBoard, BoardSquare const &fromSquare, bool onlyAttackingMoves) const override;
public:
    explicit Knight(Team team, PieceLevel pieceLevel, PieceDirection pieceDirection, bool hasMoved);
    Knight(Knight const &other);
    Knight(Knight &&other) noexcept;
    Knight& operator=(Knight const &other);
    Knight& operator=(Knight &&other) noexcept;
    virtual ~Knight() = default;
};


#endif /* Knight_h */
