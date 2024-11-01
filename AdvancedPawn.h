// AdvancedPawn.h

#ifndef AdvancedPawn_h
#define AdvancedPawn_h

#include <vector>
#include <utility>
#include <set>

#include "Constants.h"
#include "Piece.h"
#include "Cloneable.h"
#include "ComplicatedCloneable.h"
#include "PieceData.h"
#include "Pawn.h"

class IChessBoard;
class BoardSquare;
class BoardMove;


/**
 * AdvancedPawn Piece Class
 */
class AdvancedPawn final : public ComplicatedCloneable<Piece, Pawn, AdvancedPawn> {
private:
    std::vector<BoardMove> getMovesImpl(IChessBoard const &chessBoard, BoardSquare const &fromSquare, bool onlyAttackingMoves) const override;
public:
    explicit AdvancedPawn(Team team, PieceDirection pieceDirection, bool hasMoved);
    AdvancedPawn(AdvancedPawn const &other);
    AdvancedPawn(AdvancedPawn &&other) noexcept;
    AdvancedPawn& operator=(AdvancedPawn const &other);
    AdvancedPawn& operator=(AdvancedPawn &&other) noexcept;
    virtual ~AdvancedPawn() = default;
};


#endif /* AdvancedPawn_h */
