// StandardBoardMove.h

#ifndef StandardBoardMove_h
#define StandardBoardMove_h

#include <optional>

#include "BoardMove.h"
#include "BoardSquare.h"
#include "Cloneable.h"
#include "Constants.h"
#include "PieceData.h"


/**
 * StandardBoardMove BoardMove Class
 */
class StandardBoardMove final : public Cloneable<BoardMove, StandardBoardMove> {
private:
    bool equals(BoardMove const &other) const override;
    
    void makeBoardMoveImpl(ChessBoard &chessBoard) const override;
    void undoBoardMoveImpl(ChessBoard &chessBoard) const override;
    std::optional<PieceType> getPromotionPieceTypeImpl() const override { return std::nullopt; }

public:
    explicit StandardBoardMove(BoardSquare const &fromSquare, BoardSquare const &toSquare, BoardSquare const &captureSquare, bool doesEnableEnpassant, PieceData const &movedPieceData, std::optional<PieceData> const &capturedPieceData = std::nullopt);
    StandardBoardMove(StandardBoardMove const &other);
    StandardBoardMove(StandardBoardMove &&other) noexcept;
    StandardBoardMove& operator=(StandardBoardMove const &other);
    StandardBoardMove& operator=(StandardBoardMove &&other) noexcept;
    virtual ~StandardBoardMove() = default;

    bool operator==(StandardBoardMove const &other) const;
    bool operator!=(StandardBoardMove const &other) const;
};


#endif /* StandardBoardMove_h */
