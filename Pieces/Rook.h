// Rook.h

#ifndef Rook_h
#define Rook_h

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
 * Rook Piece Class
 */
class Rook : public Piece {
private:
    static std::set<std::pair<int, int>> const rookDirections;
protected:
    explicit Rook(PieceLevel pieceLevel, Team team, PieceDirection pieceDirection, bool hasMoved);
    Rook(Rook const &other);
    Rook(Rook &&other) noexcept;
    Rook& operator=(Rook const &other);
    Rook& operator=(Rook &&other) noexcept;
    virtual ~Rook() = default;

    std::vector<BoardMove> getStandardMoves(IChessBoard const &chessBoard, BoardSquare const &fromSquare, bool onlyAttackingMoves) const override;
};


#endif /* Rook_h */
