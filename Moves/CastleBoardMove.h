// CastleBoardMove.h

#ifndef CastleBoardMove_h
#define CastleBoardMove_h

#include <vector>
#include <utility>
#include <set>

#include "Constants.h"
#include "Cloneable.h"
#include "BoardMove.h"


/**
 * CastleBoardMove BoardMove Class
 */
class CastleBoardMove final : public Cloneable<BoardMove, CastleBoardMove> {
private:
    bool equals(BoardMove const &other) const override;
    void makeBoardMoveImpl(ChessBoard &chessBoard) const override;
    void undoBoardMoveImpl(ChessBoard &chessBoard) const override;

    BoardSquare rookFromSquare;
    BoardSquare rookToSquare;

    // Utility method for performing the rook logic of a castle move
    void performRookCastle(ChessBoard &chessBoard, bool isUndo) const;

    std::optional<PieceType> getPromotionPieceTypeImpl() const override { return std::nullopt; }
public:
    explicit CastleBoardMove(BoardSquare const &fromSquare, BoardSquare const &toSquare, BoardSquare const &captureSquare, BoardSquare const &rookFromSquare, BoardSquare const &rookToSquare,  bool doesEnableEnpassant, PieceData const &movedPieceData, std::optional<PieceData> const &capturedPieceData = std::nullopt);
    CastleBoardMove(CastleBoardMove const &other);
    CastleBoardMove(CastleBoardMove &&other) noexcept;
    CastleBoardMove& operator=(CastleBoardMove const &other);
    CastleBoardMove& operator=(CastleBoardMove &&other) noexcept;
    virtual ~CastleBoardMove() = default;

    BoardSquare const& getRookFromSquare() const;
    BoardSquare const& getRookToSquare() const;
};


#endif /* CastleBoardMove_h */
