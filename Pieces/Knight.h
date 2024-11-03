// Knight.h

#ifndef Knight_h
#define Knight_h

#include <vector>
#include <utility>
#include <set>

#include "Constants.h"
#include "Piece.h"
#include "Cloneable.h"

class ChessBoard;
class BoardSquare;
class BoardMove;


/**
 * Knight Piece Class
 */
class Knight : public Piece {
private:
    static std::set<std::pair<int, int>> const knightDirections;

protected:
    explicit Knight(PieceLevel pieceLevel, Team team, PieceDirection pieceDirection, bool hasMoved);
    Knight(Knight const &other);
    Knight(Knight &&other) noexcept;
    Knight& operator=(Knight const &other);
    Knight& operator=(Knight &&other) noexcept;
    virtual ~Knight() = default;

    std::vector<std::unique_ptr<BoardMove>> getStandardMoves(ChessBoard const &chessBoard, BoardSquare const &fromSquare, bool onlyAttackingMoves) const override;
};


#endif /* Knight_h */
