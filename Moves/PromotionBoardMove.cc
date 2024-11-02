// PromotionBoardMove.cc

#include <vector>

#include "PromotionBoardMove.h"
#include "ChessBoard.h"

// Basic ctor
PromotionBoardMove::PromotionBoardMove(BoardSquare const &fromSquare, BoardSquare const &toSquare, BoardSquare const &captureSquare, PieceType promotionPieceType, bool doesEnableEnpassant, PieceData const &movedPieceData, std::optional<PieceData> const &capturedPieceData) :
    Cloneable<BoardMove, PromotionBoardMove>(fromSquare, toSquare, captureSquare, doesEnableEnpassant, movedPieceData, capturedPieceData), promotionPieceType(promotionPieceType) {}

// Copy ctor
PromotionBoardMove::PromotionBoardMove(PromotionBoardMove const &other) : 
    Cloneable<BoardMove, PromotionBoardMove>(other), promotionPieceType(other.promotionPieceType) {}

// Move ctor
PromotionBoardMove::PromotionBoardMove(PromotionBoardMove &&other) noexcept : 
    Cloneable<BoardMove, PromotionBoardMove>(std::move(other)), promotionPieceType(std::move(other.promotionPieceType)) {}

// Copy assignment
PromotionBoardMove& PromotionBoardMove::operator=(PromotionBoardMove const &other) {
    if (this != &other) {
        BoardMove::operator=(other);
        promotionPieceType = other.promotionPieceType;
    }
    return *this;
}

// Move assignment
PromotionBoardMove& PromotionBoardMove::operator=(PromotionBoardMove &&other) noexcept {
    if (this != &other) {
        BoardMove::operator=(std::move(other));
        promotionPieceType = std::move(other.promotionPieceType);
    }
    return *this;
}

bool PromotionBoardMove::equals(BoardMove const &other) const {
    PromotionBoardMove const &derivedOther = static_cast<PromotionBoardMove const&>(other);
    return 
        fromSquare == derivedOther.fromSquare &&
        toSquare == derivedOther.toSquare &&
        captureSquare == derivedOther.captureSquare &&
        doesEnableEnpassant == derivedOther.doesEnableEnpassant &&
        movedPieceData == derivedOther.movedPieceData &&
        capturedPieceData == derivedOther.capturedPieceData &&
        promotionPieceType == derivedOther.promotionPieceType;
}

void PromotionBoardMove::makeBoardMoveImpl(ChessBoard &chessBoard) const {
    chessBoard.clearPosition(captureSquare);
    chessBoard.setPosition(toSquare, PieceData(movedPieceData.pieceType, movedPieceData.pieceLevel, movedPieceData.team, movedPieceData.pieceDirection, true));
    chessBoard.clearPosition(fromSquare);

    // Apply Promotion
    chessBoard.setPosition(toSquare, PieceData(promotionPieceType, movedPieceData.pieceLevel, movedPieceData.team, movedPieceData.pieceDirection, true));                          
}

void PromotionBoardMove::undoBoardMoveImpl(ChessBoard &chessBoard) const {
    chessBoard.setPosition(fromSquare, movedPieceData);     // Also undoes promotion
    chessBoard.clearPosition(toSquare);

    // Place Captured Piece Back
    if (capturedPieceData.has_value()) {
        chessBoard.setPosition(captureSquare, capturedPieceData.value());    
    } else {
        chessBoard.clearPosition(captureSquare);
    }
}
