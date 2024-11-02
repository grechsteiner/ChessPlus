// OldBoardMove.cc

#include <optional>
#include <utility>

#include "OldBoardMove.h"
#include "BoardSquare.h"
#include "Constants.h"
#include "PieceInfo.h"
#include "PieceData.h"
#include "ChessBoard.h"


// Basic ctor
OldBoardMove::OldBoardMove(
    MoveType moveType, PieceData const &movedPieceData,
    BoardSquare const &fromSquare, BoardSquare const &toSquare, BoardSquare const &captureSquare, std::optional<PieceData> const &capturedPieceData,
    std::optional<PieceType> promotionPieceType, std::optional<BoardSquare> const &rookFromSquare, std::optional<BoardSquare> const &rookToSquare) :
    moveType(moveType), movedPieceData(movedPieceData),
    fromSquare(fromSquare), toSquare(toSquare), captureSquare(captureSquare), capturedPieceData(capturedPieceData),
    promotionPieceType(promotionPieceType), rookFromSquare(rookFromSquare), rookToSquare(rookToSquare)
{}

// Static
OldBoardMove OldBoardMove::createBasicMove(
    MoveType moveType, PieceData const &movedPieceData, 
    BoardSquare const &fromSquare, BoardSquare const &toSquare, BoardSquare const &captureSquare, std::optional<PieceInfo> const &capturedPieceInfo) {
    if (capturedPieceInfo.has_value()) {
        return OldBoardMove(
            moveType, movedPieceData,
            fromSquare, toSquare, captureSquare, capturedPieceInfo.value().pieceData,
            std::nullopt, std::nullopt, std::nullopt);
    } else {
        return OldBoardMove(
            moveType, movedPieceData,
            fromSquare, toSquare, captureSquare, std::nullopt,
            std::nullopt, std::nullopt, std::nullopt);
    }
    
}

// Static
OldBoardMove OldBoardMove::createPromotionMove(
    PieceType promotionPieceType, 
    MoveType moveType, PieceData const &movedPieceData, 
    BoardSquare const &fromSquare, BoardSquare const &toSquare, BoardSquare const &captureSquare, std::optional<PieceInfo> const &capturedPieceInfo) {
    if (capturedPieceInfo.has_value()) {
        return OldBoardMove(
        moveType, movedPieceData,
        fromSquare, toSquare, captureSquare, capturedPieceInfo.value().pieceData,
        promotionPieceType, std::nullopt, std::nullopt);
    } else {
        return OldBoardMove(
        moveType, movedPieceData,
        fromSquare, toSquare, captureSquare, std::nullopt,
        promotionPieceType, std::nullopt, std::nullopt);
    }
    
}

// Static
OldBoardMove OldBoardMove::createCastleMove(
    BoardSquare const &rookFromSquare, BoardSquare const &rookToSquare, 
    MoveType moveType, PieceData const &movedPieceData, 
    BoardSquare const &fromSquare, BoardSquare const &toSquare, BoardSquare const &captureSquare, std::optional<PieceInfo> const &capturedPieceInfo) {
    if (capturedPieceInfo.has_value()) {
        return OldBoardMove(
            moveType, movedPieceData,
            fromSquare, toSquare, captureSquare, capturedPieceInfo.value().pieceData,
            std::nullopt, rookFromSquare, rookToSquare);
    } else {
        return OldBoardMove(
            moveType, movedPieceData,
            fromSquare, toSquare, captureSquare, std::nullopt,
            std::nullopt, rookFromSquare, rookToSquare); 
    }
}

// Move ctor
OldBoardMove::OldBoardMove(OldBoardMove &&other) noexcept :
    moveType(other.moveType), movedPieceData(std::move(other.movedPieceData)), 
    fromSquare(std::move(other.fromSquare)), toSquare(std::move(other.toSquare)), captureSquare(std::move(other.captureSquare)), capturedPieceData(std::move(other.capturedPieceData)),
    promotionPieceType(other.promotionPieceType), rookFromSquare(std::move(other.rookFromSquare)), rookToSquare(std::move(other.rookToSquare))
{}

// Move assignment
OldBoardMove& OldBoardMove::operator=(OldBoardMove&& other) noexcept {
    if (this != &other) {
        moveType = other.moveType;
        movedPieceData = std::move(other.movedPieceData);
        fromSquare = std::move(other.fromSquare);
        toSquare = std::move(other.toSquare);
        captureSquare = std::move(other.captureSquare);
        capturedPieceData = std::move(other.capturedPieceData);
        promotionPieceType = other.promotionPieceType;
        rookFromSquare = std::move(other.rookFromSquare);
        rookToSquare = std::move(other.rookToSquare);
    }
    return *this;
}

// Equality operator
bool OldBoardMove::operator==(OldBoardMove const &other) const {
    return 
        moveType == other.moveType &&
        movedPieceData == other.movedPieceData &&
        fromSquare == other.fromSquare &&
        toSquare == other.toSquare &&
        captureSquare == other.captureSquare &&  
        capturedPieceData == other.capturedPieceData &&
        promotionPieceType == other.promotionPieceType &&
        rookFromSquare == other.rookFromSquare &&
        rookToSquare == other.rookToSquare;
}

void OldBoardMove::performRookCastle(ChessBoard &chessBoard, bool isUndo) const {
    if (moveType == MoveType::CASTLE && rookFromSquare.has_value() && rookToSquare.has_value()) {
        std::optional<PieceInfo> rookPieceInfo = isUndo 
            ? chessBoard.getPieceInfoAt(rookToSquare.value()) 
            : chessBoard.getPieceInfoAt(rookFromSquare.value());
        if (rookPieceInfo.has_value()) {
            bool hasRookMoved = isUndo ? false : true;
            PieceData rookPieceData = rookPieceInfo.value().pieceData;
            if (isUndo) {
                chessBoard.setPosition(rookFromSquare.value(), PieceData(rookPieceData.pieceType, rookPieceData.pieceLevel, rookPieceData.team, rookPieceData.pieceDirection, hasRookMoved));
                chessBoard.clearPosition(rookToSquare.value());
            } else {
                chessBoard.setPosition(rookToSquare.value(), PieceData(rookPieceData.pieceType, rookPieceData.pieceLevel, rookPieceData.team, rookPieceData.pieceDirection, hasRookMoved));
                chessBoard.clearPosition(rookFromSquare.value());
            }
        }
    }
}

void OldBoardMove::makeBoardMove(ChessBoard &chessBoard) const {

    /*
     * Basic Stuff:
     * Set captureSquare to blank (may not equal toSquare)
     * Move piece to toSquare and set hasMoved = true
     * Clear fromSquare after moving piece
     */
    chessBoard.clearPosition(captureSquare);
    chessBoard.setPosition(toSquare, PieceData(movedPieceData.pieceType, movedPieceData.pieceLevel, movedPieceData.team, movedPieceData.pieceDirection, true));
    chessBoard.clearPosition(fromSquare);

    // Apply Promotion (default piece score for promoted piece, and set hasMoved = true)
    if (promotionPieceType.has_value()) {
        chessBoard.setPosition(toSquare, PieceData(promotionPieceType.value(), movedPieceData.pieceLevel, movedPieceData.team, movedPieceData.pieceDirection, true));                          
    }

    // Apply Castle (rook part)
    if (moveType == MoveType::CASTLE) {
        performRookCastle(chessBoard, false);
    }
}

void OldBoardMove::undoBoardMove(ChessBoard &chessBoard) const {

    /*
     * Basic Stuff
     * Move piece back (use saved movedPieceData)
     * Clear toSquare after moving piece back
     */
    chessBoard.setPosition(fromSquare, PieceData(movedPieceData.pieceType, movedPieceData.pieceLevel, movedPieceData.team, movedPieceData.pieceDirection, movedPieceData.hasMoved));
    chessBoard.clearPosition(toSquare);

    // Place Captured Piece Back
    if (capturedPieceData.has_value()) {
        chessBoard.setPosition(captureSquare, PieceData(capturedPieceData.value().pieceType, capturedPieceData.value().pieceLevel, capturedPieceData.value().team, capturedPieceData.value().pieceDirection, capturedPieceData.value().hasMoved));    
    } else {
        chessBoard.clearPosition(captureSquare);
    }
    
    // Undo Promotion
    if (promotionPieceType.has_value()) {
        chessBoard.setPosition(fromSquare, PieceData(movedPieceData.pieceType, movedPieceData.pieceLevel, movedPieceData.team, movedPieceData.pieceDirection, movedPieceData.hasMoved));
    }

    // Undo Castle (rook part)
    if (moveType == MoveType::CASTLE) {
        performRookCastle(chessBoard, true);
    }
}

MoveType OldBoardMove::getMoveType() const { return moveType; }
PieceData const& OldBoardMove::getMovedPieceData() const { return movedPieceData; }

BoardSquare const& OldBoardMove::getFromSquare() const { return fromSquare; }
BoardSquare const& OldBoardMove::getToSquare() const { return toSquare; }
BoardSquare const& OldBoardMove::getCaptureSquare() const { return captureSquare; }
std::optional<PieceData> OldBoardMove::getCapturedPieceData() const { return capturedPieceData; }

std::optional<PieceType> OldBoardMove::getPromotionPieceType() const { return promotionPieceType; }
std::optional<BoardSquare> OldBoardMove::getRookFromSquare() const { return rookFromSquare; }
std::optional<BoardSquare> OldBoardMove::getRookToSquare() const { return rookToSquare; }
