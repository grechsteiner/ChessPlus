// BoardMoves.cc

#include <cmath>
#include <cassert>
#include <string>

#include "BoardMove.h"
#include "Constants.h"
#include "ChessBoard.h"
#include "PieceInfo.h"
#include "UserSquare.h"
#include "BoardSquare.h"


// Static
const BoardMove BoardMove::DEFAULT = 
    BoardMove(BoardSquare(0, 0), BoardSquare(0, 0), BoardSquare(0, 0),
            MoveType::STANDARD, false, PieceType::EMPTY, 
            false, PieceType::EMPTY, 0, 
            Color::NONE, PieceType::EMPTY, PieceDirection::BLANK, false, 0);

BoardMove::BoardMove(BoardSquare const &fromSquare, BoardSquare const &toSquare, BoardSquare const &captureSquare,
                    MoveType moveType, bool isAttackingMove, PieceType promotionPieceType,
                    bool hasMoved, PieceType pieceType, int pieceScore,
                    Color capturedColor, PieceType capturedPieceType, PieceDirection capturedPieceDirection, bool capturedHasMoved, int capturedPieceScore) :

    fromSquare(fromSquare), toSquare(toSquare), captureSquare(captureSquare),
    moveType(moveType), isAttackingMove(isAttackingMove), promotionPieceType(promotionPieceType),
    hasMoved(hasMoved), pieceType(pieceType), pieceScore(pieceScore),
    capturedColor(capturedColor), capturedPieceType(capturedPieceType), capturedPieceDirection(capturedPieceDirection), capturedHasMoved(capturedHasMoved), capturedPieceScore(capturedPieceScore) 
{}

bool BoardMove::operator==(BoardMove const &other) const {
    return 
        fromSquare == other.fromSquare &&
        toSquare == other.toSquare &&
        captureSquare == other.captureSquare &&
        moveType == other.moveType &&
        isAttackingMove == other.isAttackingMove &&
        promotionPieceType == other.promotionPieceType &&
        hasMoved == other.hasMoved &&
        pieceType == other.pieceType &&
        pieceScore == other.pieceScore &&
        capturedColor == other.capturedColor &&
        capturedPieceType == other.capturedPieceType &&
        capturedPieceDirection == other.capturedPieceDirection &&
        capturedHasMoved == other.capturedHasMoved &&
        capturedPieceScore == other.capturedPieceScore;
}


std::string BoardMove::toString() const {
    std::string moveString = fromSquare.toString() + " " + toSquare.toString();
    if (promotionPieceType != PieceType::EMPTY) {
        moveString += " " + pieceTypeToString(promotionPieceType);
    }
    return moveString;
}

#pragma mark - Commands

void BoardMove::performRookCastle(ChessBoard &board, bool isUndo) const {
    bool hasRookMoved = isUndo ? false : true;

    int fromRow = fromSquare.getBoardRow();
    int fromCol = fromSquare.getBoardCol();
    int toRow = toSquare.getBoardRow();
    int toCol = toSquare.getBoardCol();
    if (abs(fromCol - toCol) == 2) {
            // Horizontal castle
            int rookFromCol;
            int rookToCol;
            if (fromCol > toCol) {
                // Left
                rookFromCol = toCol - 2;
                rookToCol = toCol + 1;
            } else {
                // Right
                rookFromCol = toCol + 1;
                rookToCol = toCol - 1;
            }
            board.swapPositions(BoardSquare(toRow, rookFromCol), BoardSquare(toRow, rookToCol));
            board.setHasMoved(BoardSquare(toRow, rookToCol), hasRookMoved);
        } else if (abs(fromRow - toRow) == 2) {
            // Vertical castle
            int rookFromRow;
            int rookToRow;
            if (fromRow > toRow) {
                // Up
                rookFromRow = toRow - 2;
                rookToRow = toRow + 1;
            } else {
                // Down
                rookFromRow = toRow + 1;
                rookToRow = toRow - 1;
            }
            board.swapPositions(BoardSquare(rookFromRow, toCol), BoardSquare(rookToRow, toCol));
            board.setHasMoved(BoardSquare(rookToRow, toCol), hasRookMoved);
        } else {
            assert(false);
        }
}

void BoardMove::makeMove(ChessBoard &board) const {

    // Basic Stuff
    board.setPosition(captureSquare, Color::NONE, PieceType::EMPTY, PieceDirection::BLANK, false, 0);      // Set captured piece to blank
    board.swapPositions(fromSquare, toSquare);                                                            // Move piece (if this is capturing move, captured piece will already be set to empty)
    board.setHasMoved(toSquare, true);                                                                          // Set has moved to true

    // Apply Promotion
    if (promotionPieceType != PieceType::EMPTY) {
        PieceInfo unPromotedPieceInfo = board.getPieceInfoAt(toSquare);                                                                      // Piece already moved
        board.setPosition(toSquare, unPromotedPieceInfo.getPieceColor(), promotionPieceType, unPromotedPieceInfo.getPieceDirection(), true);    // Default piece score for promoted piece
    }

    // Apply Castle (rook part)
    if (moveType == MoveType::CASTLE) {
        performRookCastle(board, false);
    }
}

void BoardMove::undoMove(ChessBoard &board) const {

    // Basic Stuff
    board.swapPositions(fromSquare, toSquare);                                                                                        // Undo moving the piece
    board.setHasMoved(fromSquare, hasMoved);                                                                                              // Set hasMoved field to what it was before
    board.setPosition(captureSquare, capturedColor, capturedPieceType, capturedPieceDirection, capturedHasMoved, capturedPieceScore);  // Place captured piece back

    // Undo promotion
    if (promotionPieceType != PieceType::EMPTY) {
        PieceInfo promotedPieceInfo = board.getPieceInfoAt(fromSquare);                                                                        // Piece already moved back
        board.setPosition(fromSquare, promotedPieceInfo.getPieceColor(), pieceType, promotedPieceInfo.getPieceDirection(), hasMoved, pieceScore); // Get piece type & score prior to promotion
    }

    // Undo castle
    if (moveType == MoveType::CASTLE) {
        performRookCastle(board, true);
    }
}


#pragma mark - Getters

// Squares
BoardSquare const& BoardMove::getFromSquare() const { return fromSquare; }
BoardSquare const& BoardMove::getToSquare() const { return toSquare; }
BoardSquare const& BoardMove::getCaptureSquare() const { return captureSquare; }

// General Info
MoveType BoardMove::getMoveType() const { return moveType; }
bool BoardMove::getIsAttackingMove() const { return isAttackingMove; }
PieceType BoardMove::getPromotionPieceType() const { return promotionPieceType; }

// Moved Piece Info
bool BoardMove::getHasMoved() const { return hasMoved; }
PieceType BoardMove::getPieceType() const { return pieceType; }
int BoardMove::getPieceScore() const { return pieceScore; }

// Captured Piece Info
Color BoardMove::getCapturedColor() const { return capturedColor; }
PieceType BoardMove::getCapturedPieceType() const { return capturedPieceType; }
PieceDirection BoardMove::getCapturedPieceDirection() const { return capturedPieceDirection; }
bool BoardMove::getCapturedHasMoved() const { return capturedHasMoved; }
int BoardMove::getCapturedPieceScore() const { return capturedPieceScore; }
