// AdvancedKnight.h

#ifndef AdvancedKnight_h
#define AdvancedKnight_h

#include <memory>
#include <vector>

#include "BoardMove.h"
#include "BoardSquare.h"
#include "ChessBoard.h"
#include "ComplicatedCloneable.h"
#include "Constants.h"
#include "Knight.h"
#include "Piece.h"


/**
 * AdvancedKnight Knight Piece Class
 */
class AdvancedKnight final : public ComplicatedCloneable<Piece, Knight, AdvancedKnight> {
private:
    std::vector<std::unique_ptr<BoardMove>> getMovesImpl(std::unique_ptr<ChessBoard> const &chessBoard, BoardSquare const &fromSquare, bool onlyAttackingMoves) const override;

public:
    explicit AdvancedKnight(Team team, PieceDirection pieceDirection, bool hasMoved);
    AdvancedKnight(AdvancedKnight const &other);
    AdvancedKnight(AdvancedKnight &&other) noexcept;
    AdvancedKnight& operator=(AdvancedKnight const &other);
    AdvancedKnight& operator=(AdvancedKnight &&other) noexcept;
    virtual ~AdvancedKnight() = default;
};


#endif /* AdvancedKnight_h */
