// PromotionBoardMove.h

#ifndef PromotionBoardMove_h
#define PromotionBoardMove_h

#include <vector>
#include <utility>
#include <set>

#include "Constants.h"
#include "Cloneable.h"
#include "BoardMove.h"


/**
 * PromotionBoardMove BoardMove Class
 */
class PromotionBoardMove final : public Cloneable<BoardMove, PromotionBoardMove> {
private:
    bool equals(BoardMove const &other) const override;
    void makeBoardMoveImpl(ChessBoard &chessBoard) const override;
    void undoBoardMoveImpl(ChessBoard &chessBoard) const override;

    PieceType promotionPieceType;
public:
    explicit PromotionBoardMove(BoardSquare const &fromSquare, BoardSquare const &toSquare, BoardSquare const &captureSquare, PieceType promotionPieceType, bool doesEnableEnpassant, PieceData const &movedPieceData, std::optional<PieceData> const &capturedPieceData = std::nullopt);
    PromotionBoardMove(PromotionBoardMove const &other);
    PromotionBoardMove(PromotionBoardMove &&other) noexcept;
    PromotionBoardMove& operator=(PromotionBoardMove const &other);
    PromotionBoardMove& operator=(PromotionBoardMove &&other) noexcept;
    virtual ~PromotionBoardMove() = default;
};


#endif /* PromotionBoardMove_h */
