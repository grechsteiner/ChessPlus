// StandardBoardMove.h

#ifndef StandardBoardMove_h
#define StandardBoardMove_h

#include <vector>
#include <utility>
#include <set>

#include "Constants.h"
#include "Cloneable.h"
#include "BoardMove.h"


/**
 * StandardBoardMove BoardMove Class
 */
class StandardBoardMove final : public Cloneable<BoardMove, StandardBoardMove> {
private:
    bool equals(BoardMove const &other) const override;
    void makeBoardMoveImpl(ChessBoard &chessBoard) const override;
    void undoBoardMoveImpl(ChessBoard &chessBoard) const override;
public:
    explicit StandardBoardMove(BoardSquare const &fromSquare, BoardSquare const &toSquare, BoardSquare const &captureSquare, bool doesEnableEnpassant, PieceData const &movedPieceData, std::optional<PieceData> const &capturedPieceData = std::nullopt);
    StandardBoardMove(StandardBoardMove const &other);
    StandardBoardMove(StandardBoardMove &&other) noexcept;
    StandardBoardMove& operator=(StandardBoardMove const &other);
    StandardBoardMove& operator=(StandardBoardMove &&other) noexcept;
    virtual ~StandardBoardMove() = default;
};


#endif /* StandardBoardMove_h */
