// AdvancedPawn.h

#ifndef AdvancedPawn_h
#define AdvancedPawn_h

#include <memory>
#include <vector>

#include "BoardMove.h"
#include "BoardSquare.h"
#include "ChessBoard.h"
#include "ComplicatedCloneable.h"
#include "Constants.h"
#include "Pawn.h"
#include "Piece.h"


/**
 * AdvancedPawn Pawn Piece Class
 */
class AdvancedPawn final : public ComplicatedCloneable<Piece, Pawn, AdvancedPawn> {
private:
    std::vector<std::unique_ptr<BoardMove>> getMovesImpl(std::unique_ptr<ChessBoard> const &chessBoard, BoardSquare const &fromSquare, bool onlyAttackingMoves) const override;
    
public:
    explicit AdvancedPawn(Team team, PieceDirection pieceDirection, bool hasMoved);
    AdvancedPawn(AdvancedPawn const &other);
    AdvancedPawn(AdvancedPawn &&other) noexcept;
    AdvancedPawn& operator=(AdvancedPawn const &other);
    AdvancedPawn& operator=(AdvancedPawn &&other) noexcept;
    virtual ~AdvancedPawn() = default;
};


#endif /* AdvancedPawn_h */
