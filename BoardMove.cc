// BoardMoves.cc

#include <optional>
#include <utility>

#include "BoardMove.h"
#include "BoardSquare.h"
#include "Constants.h"
#include "PieceInfo.h"
#include "ChessBoard.h"


// Basic ctor
BoardMove::BoardMove(
    MoveType moveType, PieceInfo const &movedPieceInfo,
    BoardSquare const &fromSquare, BoardSquare const &toSquare, BoardSquare const &captureSquare, std::optional<PieceInfo> const &capturedPieceInfo,
    std::optional<PieceType> promotionPieceType, std::optional<BoardSquare> const &rookFromSquare, std::optional<BoardSquare> const &rookToSquare) :
    moveType(moveType), movedPieceInfo(movedPieceInfo),
    fromSquare(fromSquare), toSquare(toSquare), captureSquare(captureSquare), capturedPieceInfo(capturedPieceInfo),
    promotionPieceType(promotionPieceType), rookFromSquare(rookFromSquare), rookToSquare(rookToSquare)
{}

// Static
BoardMove BoardMove::createBasicMove(
    MoveType moveType, PieceInfo const &movedPieceInfo, 
    BoardSquare const &fromSquare, BoardSquare const &toSquare, BoardSquare const &captureSquare, std::optional<PieceInfo> const &capturedPieceInfo) {
    return BoardMove(
        moveType, movedPieceInfo,
        fromSquare, toSquare, captureSquare, capturedPieceInfo,
        std::nullopt, std::nullopt, std::nullopt);
}

// Static
BoardMove BoardMove::createPromotionMove(
    PieceType promotionPieceType, 
    MoveType moveType, PieceInfo const &movedPieceInfo, 
    BoardSquare const &fromSquare, BoardSquare const &toSquare, BoardSquare const &captureSquare, std::optional<PieceInfo> const &capturedPieceInfo) {
    return BoardMove(
        moveType, movedPieceInfo,
        fromSquare, toSquare, captureSquare, capturedPieceInfo,
        promotionPieceType, std::nullopt, std::nullopt);
}

// Static
BoardMove BoardMove::createCastleMove(
    BoardSquare const &rookFromSquare, BoardSquare const &rookToSquare, 
    MoveType moveType, PieceInfo const &movedPieceInfo, 
    BoardSquare const &fromSquare, BoardSquare const &toSquare, BoardSquare const &captureSquare, std::optional<PieceInfo> const &capturedPieceInfo) {
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

void BoardMove::performRookCastle(ChessBoard &board, bool isUndo) const {
    if (moveType == MoveType::CASTLE && rookFromSquare.has_value() && rookToSquare.has_value()) {
        std::optional<PieceInfo> rookPieceInfo = isUndo 
            ? board.getPieceInfoAt(rookToSquare.value()) 
            : board.getPieceInfoAt(rookFromSquare.value());
        if (rookPieceInfo.has_value()) {
            bool hasRookMoved = isUndo ? false : true;
            if (isUndo) {
                board.setPosition(rookFromSquare.value(), rookPieceInfo.value().getTeam(), rookPieceInfo.value().getPieceType(), rookPieceInfo.value().getPieceDirection(), hasRookMoved, rookPieceInfo.value().getPieceScore());
                board.clearPosition(rookToSquare.value());
            } else {
                board.setPosition(rookToSquare.value(), rookPieceInfo.value().getTeam(), rookPieceInfo.value().getPieceType(), rookPieceInfo.value().getPieceDirection(), hasRookMoved, rookPieceInfo.value().getPieceScore());
                board.clearPosition(rookFromSquare.value());
            }
        }
    }
}

void BoardMove::makeBoardMove(ChessBoard &board) const {

    /*
     * Basic Stuff:
     * Set captureSquare to blank (may not equal toSquare)
     * Move piece to toSquare and set hasMoved = true
     * Clear fromSquare after moving piece
     */
    board.clearPosition(captureSquare);
    board.setPosition(toSquare, movedPieceInfo.getTeam(), movedPieceInfo.getPieceType(), movedPieceInfo.getPieceDirection(), true, movedPieceInfo.getPieceScore());
    board.clearPosition(fromSquare);

    // Apply Promotion (default piece score for promoted piece, and set hasMoved = true)
    if (promotionPieceType.has_value()) {
        board.setPosition(toSquare, movedPieceInfo.getTeam(), promotionPieceType.value(), movedPieceInfo.getPieceDirection(), true);                          
    }

    // Apply Castle (rook part)
    if (moveType == MoveType::CASTLE) {
        performRookCastle(board, false);
    }
}

void BoardMove::undoBoardMove(ChessBoard &board) const {

    /*
     * Basic Stuff
     * Move piece back (use saved movedPieceInfo)
     * Clear toSquare after moving piece back
     */
    board.setPosition(fromSquare, movedPieceInfo.getTeam(), movedPieceInfo.getPieceType(), movedPieceInfo.getPieceDirection(), movedPieceInfo.getHasMoved(), movedPieceInfo.getPieceScore());
    board.clearPosition(toSquare);

    // Place Captured Piece Back
    if (capturedPieceInfo.has_value()) {
        board.setPosition(captureSquare, capturedPieceInfo.value().getTeam(), capturedPieceInfo.value().getPieceType(), capturedPieceInfo.value().getPieceDirection(), capturedPieceInfo.value().getHasMoved(), capturedPieceInfo.value().getPieceScore());    
    } else {
        board.clearPosition(captureSquare);
    }
    
    // Undo Promotion
    if (promotionPieceType.has_value()) {
        board.setPosition(fromSquare, movedPieceInfo.getTeam(), movedPieceInfo.getPieceType(), movedPieceInfo.getPieceDirection(), movedPieceInfo.getHasMoved(), movedPieceInfo.getPieceScore());
    }

    // Undo Castle (rook part)
    if (moveType == MoveType::CASTLE) {
        performRookCastle(board, true);
    }
}

MoveType BoardMove::getMoveType() const { return moveType; }
PieceInfo const& BoardMove::getMovedPieceInfo() const { return movedPieceInfo; }

BoardSquare const& BoardMove::getFromSquare() const { return fromSquare; }
BoardSquare const& BoardMove::getToSquare() const { return toSquare; }
BoardSquare const& BoardMove::getCaptureSquare() const { return captureSquare; }
std::optional<PieceInfo> BoardMove::getCapturedPieceInfo() const { return capturedPieceInfo; }

std::optional<PieceType> BoardMove::getPromotionPieceType() const { return promotionPieceType; }
std::optional<BoardSquare> BoardMove::getRookFromSquare() const { return rookFromSquare; }
std::optional<BoardSquare> BoardMove::getRookToSquare() const { return rookToSquare; }
