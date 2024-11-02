// AdvancedBishop.h

#ifndef AdvancedBishop_h
#define AdvancedBishop_h

#include <vector>
#include <utility>
#include <set>

#include "Constants.h"
#include "Piece.h"
#include "Cloneable.h"
#include "ComplicatedCloneable.h"
#include "PieceData.h"
#include "Bishop.h"

class ChessBoard;
class BoardSquare;
class OldBoardMove;


/**
 * AdvancedBishop Piece Class
 */
class AdvancedBishop final : public ComplicatedCloneable<Piece, Bishop, AdvancedBishop> {
private:
    std::vector<OldBoardMove> getMovesImpl(ChessBoard const &chessBoard, BoardSquare const &fromSquare, bool onlyAttackingMoves) const override;
public:
    explicit AdvancedBishop(Team team, PieceDirection pieceDirection, bool hasMoved);
    AdvancedBishop(AdvancedBishop const &other);
    AdvancedBishop(AdvancedBishop &&other) noexcept;
    AdvancedBishop& operator=(AdvancedBishop const &other);
    AdvancedBishop& operator=(AdvancedBishop &&other) noexcept;
    virtual ~AdvancedBishop() = default;
};


#endif /* AdvancedBishop_h */
