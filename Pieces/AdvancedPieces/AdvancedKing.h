// AdvancedKing.h

#ifndef AdvancedKing_h
#define AdvancedKing_h

#include <memory>
#include <vector>

#include "BoardMove.h"
#include "BoardSquare.h"
#include "ChessBoard.h"
#include "ComplicatedCloneable.h"
#include "Constants.h"
#include "King.h"
#include "Piece.h"


/**
 * AdvancedKing King Piece Class
 */
class AdvancedKing final : public ComplicatedCloneable<Piece, King, AdvancedKing> {
private:
    std::vector<std::unique_ptr<BoardMove>> getMovesImpl(std::unique_ptr<ChessBoard> const &chessBoard, BoardSquare const &fromSquare, bool onlyAttackingMoves) const override;

public:
    explicit AdvancedKing(Team team, PieceDirection pieceDirection, bool hasMoved);
    AdvancedKing(AdvancedKing const &other);
    AdvancedKing(AdvancedKing &&other) noexcept;
    AdvancedKing& operator=(AdvancedKing const &other);
    AdvancedKing& operator=(AdvancedKing &&other) noexcept;
    virtual ~AdvancedKing() = default;
};


#endif /* AdvancedKing_h */
