// AdvancedRook.h

#ifndef AdvancedRook_h
#define AdvancedRook_h

#include <vector>
#include <utility>
#include <set>

#include "Constants.h"
#include "Piece.h"
#include "Cloneable.h"
#include "ComplicatedCloneable.h"
#include "PieceData.h"
#include "Rook.h"

class ChessBoard;
class BoardSquare;
class OldBoardMove;


/**
 * AdvancedRook Piece Class
 */
class AdvancedRook final : public ComplicatedCloneable<Piece, Rook, AdvancedRook> {
private:
    std::vector<OldBoardMove> getMovesImpl(ChessBoard const &chessBoard, BoardSquare const &fromSquare, bool onlyAttackingMoves) const override;
public:
    explicit AdvancedRook(Team team, PieceDirection pieceDirection, bool hasMoved);
    AdvancedRook(AdvancedRook const &other);
    AdvancedRook(AdvancedRook &&other) noexcept;
    AdvancedRook& operator=(AdvancedRook const &other);
    AdvancedRook& operator=(AdvancedRook &&other) noexcept;
    virtual ~AdvancedRook() = default;
};


#endif /* AdvancedRook_h */
