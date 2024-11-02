// AdvancedKnight.h

#ifndef AdvancedKnight_h
#define AdvancedKnight_h

#include <vector>
#include <utility>
#include <set>

#include "Constants.h"
#include "Piece.h"
#include "Cloneable.h"
#include "ComplicatedCloneable.h"
#include "PieceData.h"
#include "Knight.h"

class ChessBoard;
class BoardSquare;
class BoardMove;


/**
 * AdvancedKnight Piece Class
 */
class AdvancedKnight final : public ComplicatedCloneable<Piece, Knight, AdvancedKnight> {
private:
    std::vector<BoardMove> getMovesImpl(ChessBoard const &chessBoard, BoardSquare const &fromSquare, bool onlyAttackingMoves) const override;
public:
    explicit AdvancedKnight(Team team, PieceDirection pieceDirection, bool hasMoved);
    AdvancedKnight(AdvancedKnight const &other);
    AdvancedKnight(AdvancedKnight &&other) noexcept;
    AdvancedKnight& operator=(AdvancedKnight const &other);
    AdvancedKnight& operator=(AdvancedKnight &&other) noexcept;
    virtual ~AdvancedKnight() = default;
};


#endif /* AdvancedKnight_h */
