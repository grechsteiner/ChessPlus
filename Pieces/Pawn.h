// Pawn.h

#ifndef Pawn_h
#define Pawn_h

#include <vector>
#include <utility>

#include "Constants.h"
#include "Piece.h"
#include "Cloneable.h"

class ChessBoard;
class BoardSquare;
class BoardMove;


/**
 * Pawn Piece Class
 */
class Pawn : public Piece {
private:
    std::vector<BoardMove> createPromotionMoves(BoardMove const &move) const;
protected:
    explicit Pawn(PieceLevel pieceLevel, Team team, PieceDirection pieceDirection, bool hasMoved);
    Pawn(Pawn const &other);
    Pawn(Pawn &&other) noexcept;
    Pawn& operator=(Pawn const &other);
    Pawn& operator=(Pawn &&other) noexcept;
    virtual ~Pawn() = default;

    std::vector<BoardMove> getStandardMoves(ChessBoard const &chessBoard, BoardSquare const &fromSquare, bool onlyAttackingMoves) const override;
    std::pair<int, int> getPawnDirection() const;
};


#endif /* Pawn */
