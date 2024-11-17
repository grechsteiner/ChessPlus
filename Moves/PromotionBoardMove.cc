// PromotionBoardMove.cc

#include "PromotionBoardMove.h"

#include <optional>
#include <utility>

#include "BoardMove.h"
#include "BoardSquare.h"
#include "Cloneable.h"
#include "Constants.h"
#include "PieceData.h"


/*
 * Basic ctor
 */
PromotionBoardMove::PromotionBoardMove(BoardSquare const &fromSquare, BoardSquare const &toSquare, BoardSquare const &captureSquare, PieceType promotionPieceType, bool doesEnableEnpassant, PieceData const &movedPieceData, std::optional<PieceData> const &capturedPieceData) :
    Cloneable<BoardMove, PromotionBoardMove>(fromSquare, toSquare, captureSquare, doesEnableEnpassant, movedPieceData, capturedPieceData), promotionPieceType(promotionPieceType) { }

/*
 * Copy ctor
 */
PromotionBoardMove::PromotionBoardMove(PromotionBoardMove const &other) : 
    Cloneable<BoardMove, PromotionBoardMove>(other), promotionPieceType(other.promotionPieceType) { }

/*
 * Move ctor
 */
PromotionBoardMove::PromotionBoardMove(PromotionBoardMove &&other) noexcept : 
    Cloneable<BoardMove, PromotionBoardMove>(std::move(other)), promotionPieceType(std::move(other.promotionPieceType)) { }

/*
 * Copy assignment
 */
PromotionBoardMove& PromotionBoardMove::operator=(PromotionBoardMove const &other) {
    if (this != &other) {
        BoardMove::operator=(other);
        promotionPieceType = other.promotionPieceType;
    }
    return *this;
}

/*
 * Move assignment
 */
PromotionBoardMove& PromotionBoardMove::operator=(PromotionBoardMove &&other) noexcept {
    if (this != &other) {
        BoardMove::operator=(std::move(other));
        promotionPieceType = std::move(other.promotionPieceType);
    }
    return *this;
}

/*
 * Equality
 */
bool PromotionBoardMove::operator==(PromotionBoardMove const &other) const {
    return 
        fromSquare == other.fromSquare &&
        toSquare == other.toSquare &&
        captureSquare == other.captureSquare &&
        doesEnableEnpassant == other.doesEnableEnpassant &&
        movedPieceData == other.movedPieceData &&
        capturedPieceData == other.capturedPieceData &&
        promotionPieceType == other.promotionPieceType;
}

/*
 * Inequality
 */
bool PromotionBoardMove::operator!=(PromotionBoardMove const &other) const {
    return !(*this == other);
}

/*
 * Polymorphic equality
 */
bool PromotionBoardMove::equals(BoardMove const &other) const {
    PromotionBoardMove const &derivedOther = static_cast<PromotionBoardMove const&>(other);
    return *this == derivedOther;
}

/*
 * Apply itself to ChessBoard argument
 */
void PromotionBoardMove::makeBoardMoveImpl(ChessBoard &chessBoard) const {
    chessBoard.clearPosition(captureSquare);
    chessBoard.setPosition(toSquare, PieceData(movedPieceData.pieceType, movedPieceData.pieceLevel, movedPieceData.team, movedPieceData.pieceDirection, true));
    chessBoard.clearPosition(fromSquare);

    // Apply promotion
    chessBoard.setPosition(toSquare, PieceData(promotionPieceType, movedPieceData.pieceLevel, movedPieceData.team, movedPieceData.pieceDirection, true));                          
}

/*
 * Un-apply itself to ChessBoard argument
 */
void PromotionBoardMove::undoBoardMoveImpl(ChessBoard &chessBoard) const {
    // This naturally undoes promotion
    chessBoard.setPosition(fromSquare, movedPieceData);
    chessBoard.clearPosition(toSquare);

    // Place captured Piece back
    if (capturedPieceData.has_value()) {
        chessBoard.setPosition(captureSquare, capturedPieceData.value());    
    }
}
