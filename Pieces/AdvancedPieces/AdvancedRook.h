// AdvancedRook.h

#ifndef AdvancedRook_h
#define AdvancedRook_h

#include <memory>
#include <vector>

#include "BoardMove.h"
#include "BoardSquare.h"
#include "ChessBoard.h"
#include "ComplicatedCloneable.h"
#include "Constants.h"
#include "Piece.h"
#include "Rook.h"


/**
 * AdvancedRook Rook Piece Class
 */
class AdvancedRook final : public ComplicatedCloneable<Piece, Rook, AdvancedRook> {
private:
    std::vector<std::unique_ptr<BoardMove>> getMovesImpl(std::unique_ptr<ChessBoard> const &chessBoard, BoardSquare const &fromSquare, bool onlyAttackingMoves) const override;

public:
    explicit AdvancedRook(Team team, PieceDirection pieceDirection, bool hasMoved);
    AdvancedRook(AdvancedRook const &other);
    AdvancedRook(AdvancedRook &&other) noexcept;
    AdvancedRook& operator=(AdvancedRook const &other);
    AdvancedRook& operator=(AdvancedRook &&other) noexcept;
    virtual ~AdvancedRook() = default;
};


#endif /* AdvancedRook_h */
