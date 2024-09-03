// Pawn.h

#ifndef Pawn_h
#define Pawn_h

#include <vector>
#include <utility>

#include "Constants.h"
#include "Piece.h"
#include "Cloneable.h"

class IChessBoard;
class BoardSquare;
class BoardMove;


/**
 * Pawn Piece Class
 */
class Pawn : public Cloneable<Piece, Pawn> {
private:
    std::pair<int, int> pawnDirection;
    std::vector<BoardMove> getMovesImpl(IChessBoard const &chessBoard, BoardSquare const &fromSquare, bool onlyAttackingMoves) const override;
    std::vector<BoardMove> createPromotionMoves(BoardMove const &move) const;
public:
    explicit Pawn(Team team, PieceDirection pieceDirection, bool hasMoved, int pieceScore = 1);
    Pawn(Pawn const &other);
    Pawn(Pawn &&other) noexcept;
    Pawn& operator=(Pawn const &other);
    Pawn& operator=(Pawn &&other) noexcept;
    virtual ~Pawn() = default;
};


#endif /* Pawn */
