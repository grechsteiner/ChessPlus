// BoardMoves.cc

#include <optional>
#include <utility>

#include "BoardMove.h"
#include "BoardSquare.h"
#include "Constants.h"
#include "PieceData.h"
#include "IChessBoard.h"


// Basic ctor
BoardMove::BoardMove(
    MoveType moveType, PieceData const &movedPieceInfo,
    BoardSquare const &fromSquare, BoardSquare const &toSquare, BoardSquare const &captureSquare, std::optional<PieceData> const &capturedPieceInfo,
    std::optional<PieceType> promotionPieceType, std::optional<BoardSquare> const &rookFromSquare, std::optional<BoardSquare> const &rookToSquare) :
    moveType(moveType), movedPieceInfo(movedPieceInfo),
    fromSquare(fromSquare), toSquare(toSquare), captureSquare(captureSquare), capturedPieceInfo(capturedPieceInfo),
    promotionPieceType(promotionPieceType), rookFromSquare(rookFromSquare), rookToSquare(rookToSquare)
{}

// Static
BoardMove BoardMove::createBasicMove(
    MoveType moveType, PieceData const &movedPieceInfo, 
    BoardSquare const &fromSquare, BoardSquare const &toSquare, BoardSquare const &captureSquare, std::optional<PieceData> const &capturedPieceInfo) {
    return BoardMove(
        moveType, movedPieceInfo,
        fromSquare, toSquare, captureSquare, capturedPieceInfo,
        std::nullopt, std::nullopt, std::nullopt);
}

// Static
BoardMove BoardMove::createPromotionMove(
    PieceType promotionPieceType, 
    MoveType moveType, PieceData const &movedPieceInfo, 
    BoardSquare const &fromSquare, BoardSquare const &toSquare, BoardSquare const &captureSquare, std::optional<PieceData> const &capturedPieceInfo) {
    return BoardMove(
        moveType, movedPieceInfo,
        fromSquare, toSquare, captureSquare, capturedPieceInfo,
        promotionPieceType, std::nullopt, std::nullopt);
}

// Static
BoardMove BoardMove::createCastleMove(
    BoardSquare const &rookFromSquare, BoardSquare const &rookToSquare, 
    MoveType moveType, PieceData const &movedPieceInfo, 
    BoardSquare const &fromSquare, BoardSquare const &toSquare, BoardSquare const &captureSquare, std::optional<PieceData> const &capturedPieceInfo) {
    return BoardMove(
        moveType, movedPieceInfo,
        fromSquare, toSquare, captureSquare, capturedPieceInfo,
        std::nullopt, rookFromSquare, rookToSquare);
}

// Move ctor
BoardMove::BoardMove(BoardMove &&other) noexcept :
    moveType(other.moveType), movedPieceInfo(std::move(other.movedPieceInfo)), 
    fromSquare(std::move(other.fromSquare)), toSquare(std::move(other.toSquare)), captureSquare(std::move(other.captureSquare)), capturedPieceInfo(std::move(other.capturedPieceInfo)),
    promotionPieceType(other.promotionPieceType), rookFromSquare(std::move(other.rookFromSquare)), rookToSquare(std::move(other.rookToSquare))
{}

// Move assignment
BoardMove& BoardMove::operator=(BoardMove&& other) noexcept {
    if (this != &other) {
        moveType = other.moveType;
        movedPieceInfo = std::move(other.movedPieceInfo);
        fromSquare = std::move(other.fromSquare);
        toSquare = std::move(other.toSquare);
        captureSquare = std::move(other.captureSquare);
        capturedPieceInfo = std::move(other.capturedPieceInfo);
        promotionPieceType = other.promotionPieceType;
        rookFromSquare = std::move(other.rookFromSquare);
        rookToSquare = std::move(other.rookToSquare);
    }
    return *this;
}

// Equality operator
bool BoardMove::operator==(BoardMove const &other) const {
    return 
        moveType == other.moveType &&
        movedPieceInfo == other.movedPieceInfo &&
        fromSquare == other.fromSquare &&
        toSquare == other.toSquare &&
        captureSquare == other.captureSquare &&  
        capturedPieceInfo == other.capturedPieceInfo &&
        promotionPieceType == other.promotionPieceType &&
        rookFromSquare == other.rookFromSquare &&
        rookToSquare == other.rookToSquare;
}

void BoardMove::performRookCastle(IChessBoard &chessBoard, bool isUndo) const {
    if (moveType == MoveType::CASTLE && rookFromSquare.has_value() && rookToSquare.has_value()) {
        std::optional<PieceData> rookPieceInfo = isUndo 
            ? chessBoard.getPieceInfoAt(rookToSquare.value()) 
            : chessBoard.getPieceInfoAt(rookFromSquare.value());
        if (rookPieceInfo.has_value()) {
            bool hasRookMoved = isUndo ? false : true;
            if (isUndo) {
                chessBoard.setPosition(rookFromSquare.value(), rookPieceInfo.value().getTeam(), rookPieceInfo.value().getPieceType(), rookPieceInfo.value().getPieceDirection(), hasRookMoved, rookPieceInfo.value().getPieceScore());
                chessBoard.clearPosition(rookToSquare.value());
            } else {
                chessBoard.setPosition(rookToSquare.value(), rookPieceInfo.value().getTeam(), rookPieceInfo.value().getPieceType(), rookPieceInfo.value().getPieceDirection(), hasRookMoved, rookPieceInfo.value().getPieceScore());
                chessBoard.clearPosition(rookFromSquare.value());
            }
        }
    }
}

void BoardMove::makeBoardMove(IChessBoard &chessBoard) const {

    /*
     * Basic Stuff:
     * Set captureSquare to blank (may not equal toSquare)
     * Move piece to toSquare and set hasMoved = true
     * Clear fromSquare after moving piece
     */
    chessBoard.clearPosition(captureSquare);
    chessBoard.setPosition(toSquare, movedPieceInfo.getTeam(), movedPieceInfo.getPieceType(), movedPieceInfo.getPieceDirection(), true, movedPieceInfo.getPieceScore());
    chessBoard.clearPosition(fromSquare);

    // Apply Promotion (default piece score for promoted piece, and set hasMoved = true)
    if (promotionPieceType.has_value()) {
        chessBoard.setPosition(toSquare, movedPieceInfo.getTeam(), promotionPieceType.value(), movedPieceInfo.getPieceDirection(), true);                          
    }

    // Apply Castle (rook part)
    if (moveType == MoveType::CASTLE) {
        performRookCastle(chessBoard, false);
    }
}

void BoardMove::undoBoardMove(IChessBoard &chessBoard) const {

    /*
     * Basic Stuff
     * Move piece back (use saved movedPieceInfo)
     * Clear toSquare after moving piece back
     */
    chessBoard.setPosition(fromSquare, movedPieceInfo.getTeam(), movedPieceInfo.getPieceType(), movedPieceInfo.getPieceDirection(), movedPieceInfo.getHasMoved(), movedPieceInfo.getPieceScore());
    chessBoard.clearPosition(toSquare);

    // Place Captured Piece Back
    if (capturedPieceInfo.has_value()) {
        chessBoard.setPosition(captureSquare, capturedPieceInfo.value().getTeam(), capturedPieceInfo.value().getPieceType(), capturedPieceInfo.value().getPieceDirection(), capturedPieceInfo.value().getHasMoved(), capturedPieceInfo.value().getPieceScore());    
    } else {
        chessBoard.clearPosition(captureSquare);
    }
    
    // Undo Promotion
    if (promotionPieceType.has_value()) {
        chessBoard.setPosition(fromSquare, movedPieceInfo.getTeam(), movedPieceInfo.getPieceType(), movedPieceInfo.getPieceDirection(), movedPieceInfo.getHasMoved(), movedPieceInfo.getPieceScore());
    }

    // Undo Castle (rook part)
    if (moveType == MoveType::CASTLE) {
        performRookCastle(chessBoard, true);
    }
}

MoveType BoardMove::getMoveType() const { return moveType; }
PieceData const& BoardMove::getMovedPieceInfo() const { return movedPieceInfo; }

BoardSquare const& BoardMove::getFromSquare() const { return fromSquare; }
BoardSquare const& BoardMove::getToSquare() const { return toSquare; }
BoardSquare const& BoardMove::getCaptureSquare() const { return captureSquare; }
std::optional<PieceData> BoardMove::getCapturedPieceInfo() const { return capturedPieceInfo; }

std::optional<PieceType> BoardMove::getPromotionPieceType() const { return promotionPieceType; }
std::optional<BoardSquare> BoardMove::getRookFromSquare() const { return rookFromSquare; }
std::optional<BoardSquare> BoardMove::getRookToSquare() const { return rookToSquare; }
