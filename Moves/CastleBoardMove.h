// CastleBoardMove.h

#ifndef CastleBoardMove_h
#define CastleBoardMove_h

#include <optional>

#include "BoardMove.h"
#include "BoardSquare.h"
#include "Cloneable.h"
#include "Constants.h"
#include "PieceData.h"


/**
 * CastleBoardMove BoardMove Class
 */
class CastleBoardMove final : public Cloneable<BoardMove, CastleBoardMove> {
private:
    BoardSquare rookFromSquare;
    BoardSquare rookToSquare;

    bool equals(BoardMove const &other) const override;

    void makeBoardMoveImpl(ChessBoard &chessBoard) const override;
    void undoBoardMoveImpl(ChessBoard &chessBoard) const override;
    std::optional<PieceType> getPromotionPieceTypeImpl() const override { return std::nullopt; }
    
    void performRookCastle(ChessBoard &chessBoard, bool undoingMove) const;
    
public:
    explicit CastleBoardMove(BoardSquare const &fromSquare, BoardSquare const &toSquare, BoardSquare const &captureSquare, BoardSquare const &rookFromSquare, BoardSquare const &rookToSquare,  bool doesEnableEnpassant, PieceData const &movedPieceData, std::optional<PieceData> const &capturedPieceData = std::nullopt);
    CastleBoardMove(CastleBoardMove const &other);
    CastleBoardMove(CastleBoardMove &&other) noexcept;
    CastleBoardMove& operator=(CastleBoardMove const &other);
    CastleBoardMove& operator=(CastleBoardMove &&other) noexcept;
    virtual ~CastleBoardMove() = default;

    bool operator==(CastleBoardMove const &other) const;
    bool operator!=(CastleBoardMove const &other) const;
};


#endif /* CastleBoardMove_h */
