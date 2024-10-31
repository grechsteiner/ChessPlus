// AdvancedKing.h

#ifndef AdvancedKing_h
#define AdvancedKing_h

#include <vector>
#include <utility>
#include <set>

#include "Constants.h"
#include "Piece.h"
#include "Cloneable.h"
#include "ComplicatedCloneable.h"
#include "PieceData.h"
#include "King.h"

class IChessBoard;
class BoardSquare;
class BoardMove;


/**
 * Advanced King Piece Class
 */
class AdvancedKing final : public ComplicatedCloneable<Piece, King, AdvancedKing> {
private:
    std::vector<BoardMove> getMovesImpl(IChessBoard const &chessBoard, BoardSquare const &fromSquare, bool onlyAttackingMoves) const override;
public:
    explicit AdvancedKing(Team team, PieceDirection pieceDirection, bool hasMoved);
    AdvancedKing(AdvancedKing const &other);
    AdvancedKing(AdvancedKing &&other) noexcept;
    AdvancedKing& operator=(AdvancedKing const &other);
    AdvancedKing& operator=(AdvancedKing &&other) noexcept;
    virtual ~AdvancedKing() = default;
};

#endif /* AdvancedKing_h */
