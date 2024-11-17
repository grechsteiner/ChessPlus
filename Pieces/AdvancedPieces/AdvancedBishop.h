// AdvancedBishop.h

#ifndef AdvancedBishop_h
#define AdvancedBishop_h

#include <memory>
#include <vector>

#include "Bishop.h"
#include "BoardMove.h"
#include "BoardSquare.h"
#include "ChessBoard.h"
#include "ComplicatedCloneable.h"
#include "Constants.h"
#include "Piece.h"


/**
 * AdvancedBishop Bishop Piece Class
 */
class AdvancedBishop final : public ComplicatedCloneable<Piece, Bishop, AdvancedBishop> {
private:
    std::vector<std::unique_ptr<BoardMove>> getMovesImpl(std::unique_ptr<ChessBoard> const &chessBoard, BoardSquare const &fromSquare, bool onlyAttackingMoves) const override;

public:
    explicit AdvancedBishop(Team team, PieceDirection pieceDirection, bool hasMoved);
    AdvancedBishop(AdvancedBishop const &other);
    AdvancedBishop(AdvancedBishop &&other) noexcept;
    AdvancedBishop& operator=(AdvancedBishop const &other);
    AdvancedBishop& operator=(AdvancedBishop &&other) noexcept;
    virtual ~AdvancedBishop() = default;
};


#endif /* AdvancedBishop_h */
