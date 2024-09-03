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
class Rook : public Cloneable<Piece, Rook> {
private:
    static std::set<std::pair<int, int>> const rookDirections;
    std::vector<BoardMove> getMovesImpl(IChessBoard const &chessBoard, BoardSquare const &fromSquare, bool onlyAttackingMoves) const override;
public:
    explicit Rook(Team team, PieceDirection pieceDirection, bool hasMoved, int pieceScore = 5);
    Rook(Rook const &other);
    Rook(Rook &&other) noexcept;
    Rook& operator=(Rook const &other);
    Rook& operator=(Rook &&other) noexcept;
    virtual ~Rook() = default;
};


#endif /* Rook_h */
