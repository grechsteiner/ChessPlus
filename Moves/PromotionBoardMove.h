// PromotionBoardMove.h

#ifndef PromotionBoardMove_h
#define PromotionBoardMove_h

#include <optional>

#include "BoardMove.h"
#include "BoardSquare.h"
#include "Cloneable.h"
#include "Constants.h"
#include "PieceData.h"


/**
 * PromotionBoardMove BoardMove Class
 */
class PromotionBoardMove final : public Cloneable<BoardMove, PromotionBoardMove> {
private:
    PieceType promotionPieceType;

    bool equals(BoardMove const &other) const override;

    void makeBoardMoveImpl(ChessBoard &chessBoard) const override;
    void undoBoardMoveImpl(ChessBoard &chessBoard) const override;
    std::optional<PieceType> getPromotionPieceTypeImpl() const override { return promotionPieceType; }
    
public:
    explicit PromotionBoardMove(BoardSquare const &fromSquare, BoardSquare const &toSquare, BoardSquare const &captureSquare, PieceType promotionPieceType, bool doesEnableEnpassant, PieceData const &movedPieceData, std::optional<PieceData> const &capturedPieceData = std::nullopt);
    PromotionBoardMove(PromotionBoardMove const &other);
    PromotionBoardMove(PromotionBoardMove &&other) noexcept;
    PromotionBoardMove& operator=(PromotionBoardMove const &other);
    PromotionBoardMove& operator=(PromotionBoardMove &&other) noexcept;
    virtual ~PromotionBoardMove() = default;

    bool operator==(PromotionBoardMove const &other) const;
    bool operator!=(PromotionBoardMove const &other) const;
};


#endif /* PromotionBoardMove_h */
