// BoardMoveFactory.h

#ifndef BoardMoveFactory_h
#define BoardMoveFactory_h

#include <memory>
#include <optional>

#include "Constants.h"
#include "PieceData.h"

class BoardMove;
class BoardSquare;


class BoardMoveFactory {
public:
    static std::unique_ptr<BoardMove> createStandardMove(BoardSquare const &fromSquare, BoardSquare const &toSquare, BoardSquare const &captureSquare, bool doesEnableEnpassant, PieceData const &movedPieceData, std::optional<PieceData> const &capturedPieceData = std::nullopt);
    static std::unique_ptr<BoardMove> createPromotionMove(BoardSquare const &fromSquare, BoardSquare const &toSquare, BoardSquare const &captureSquare, PieceType promotionPieceType, bool doesEnableEnpassant, PieceData const &movedPieceData, std::optional<PieceData> const &capturedPieceData = std::nullopt);
    static std::unique_ptr<BoardMove> createCastleMove(BoardSquare const &fromSquare, BoardSquare const &toSquare, BoardSquare const &captureSquare, BoardSquare const &rookFromSquare, BoardSquare const &rookToSquare,  bool doesEnableEnpassant, PieceData const &movedPieceData, std::optional<PieceData> const &capturedPieceData = std::nullopt);
};


#endif /* BoardMoveFactory_h */
