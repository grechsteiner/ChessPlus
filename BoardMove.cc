// FullMove.cc

#include <cmath>
#include <cassert>
#include <string>

#include "FullMove.h"
#include "Constants.h"
#include "ChessBoard.h"
#include "Piece.h"
#include "UserSquare.h"


// Static
const BoardMove BoardMove::DEFAULT = 
    BoardMove(0, 0, 0, 0, 0, 0,
            MoveType::STANDARD, false, PieceType::EMPTY, 
            false, PieceType::EMPTY, 0, 
            Color::NONE, PieceType::EMPTY, PieceDirection::BLANK, false, 0);

BoardMove::BoardMove( int fromRow, int fromCol, int toRow, int toCol, int captureRow, int captureCol, 
                    MoveType moveType, bool isAttackingMove, PieceType promotionPieceType,
                    bool hasMoved, PieceType pieceType, int pieceScore,
                    Color capturedColor, PieceType capturedPieceType, PieceDirection capturedPieceDirection, bool capturedHasMoved, int capturedPieceScore) :

    fromRow(fromRow), fromCol(fromCol), toRow(toRow), toCol(toCol), captureRow(captureRow), captureCol(captureCol),
    moveType(moveType), isAttackingMove(isAttackingMove), promotionPieceType(promotionPieceType),
    hasMoved(hasMoved), pieceType(pieceType), pieceScore(pieceScore),
    capturedColor(capturedColor), capturedPieceType(capturedPieceType), capturedPieceDirection(capturedPieceDirection), capturedHasMoved(capturedHasMoved), capturedPieceScore(capturedPieceScore) 
{}

/*
FullMove::FullMove( int fromRow, int fromCol, int toRow, int toCol,
                    bool hasMoved, PieceType promotionPieceType, MoveType moveType, bool isAttackingMove,
                    PieceType pieceType, int pieceScore,
                    Color capturedColor, PieceType capturedPieceType, PieceDirection capturedPieceDirection, bool capturedHasMoved, int capturedPieceScore) :
    FullMove(fromRow, fromCol, toRow, toCol, toRow, toCol, 
            hasMoved, promotionPieceType, moveType, isAttackingMove, 
            pieceType, pieceScore,
            capturedColor, capturedPieceType, capturedPieceDirection, capturedHasMoved, capturedPieceScore) 
{}
*/

bool BoardMove::operator==(BoardMove const &other) const {
    return 
        fromRow == other.fromRow &&
        toRow == other.toRow &&
        captureRow == other.captureRow &&
        fromCol == other.fromCol &&
        toCol == other.toCol &&
        captureCol == other.captureCol &&
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
    std::string moveString = std::to_string(fromCol) + std::to_string(fromRow) + " " + std::to_string(toCol) + std::to_string(toRow);
    if (promotionPieceType != PieceType::EMPTY) {
        moveString += " " + pieceTypeToString(promotionPieceType);
    }
    return moveString;
}

#pragma mark - Commands

void BoardMove::performRookCastle(ChessBoard &board, bool isUndo) const {
    bool newHasRookMoved = isUndo ? false : true;
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
            board.swapPositions(toRow, rookFromCol, toRow, rookToCol);
            board.setHasMoved(toRow, rookToCol, newHasRookMoved);
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
            board.swapPositions(rookFromRow, toCol, rookToRow, toCol);
            board.setHasMoved(rookToRow, toCol, newHasRookMoved);
        } else {
            assert(false);
        }
}

void BoardMove::makeMove(ChessBoard &board) const {

    // Basic Stuff
    board.setPosition(captureRow, captureCol, Color::NONE, PieceType::EMPTY, PieceDirection::BLANK, false, 0);      // Set captured piece to blank
    board.swapPositions(fromRow, fromCol, toRow, toCol);                                                            // Move piece (if this is capturing move, captured piece will already be set to empty)
    board.setHasMoved(toRow, toCol, true);                                                                          // Set has moved to true

    // Apply Promotion
    if (promotionPieceType != PieceType::EMPTY) {
        Piece const& unPromotedPiece = board.getPieceAt(toRow, toCol);                                                                      // Piece already moved
        board.setPosition(toRow, toCol, unPromotedPiece.getPieceColor(), promotionPieceType, unPromotedPiece.getPieceDirection(), true);    // Default piece score for promoted piece
    }

    // Apply Castle (rook part)
    if (moveType == MoveType::CASTLE) {
        performRookCastle(board, false);
    }
}

bool BoardMove::undoMove(ChessBoard &board) const {

    // Basic Stuff
    board.swapPositions(fromRow, fromCol, toRow, toCol);                                                                                        // Undo moving the piece
    board.setHasMoved(fromRow, fromCol, hasMoved);                                                                                              // Set hasMoved field to what it was before
    board.setPosition(captureRow, captureCol, capturedColor, capturedPieceType, capturedPieceDirection, capturedHasMoved, capturedPieceScore);  // Place captured piece back

    // Undo promotion
    if (promotionPieceType != PieceType::EMPTY) {
        Piece const& promotedPiece = board.getPieceAt(fromRow, fromCol);                                                                        // Piece already moved back
        board.setPosition(fromRow, fromCol, promotedPiece.getPieceColor(), pieceType, promotedPiece.getPieceDirection(), hasMoved, pieceScore); // Get piece type & score prior to promotion
    }

    // Undo castle
    if (moveType == MoveType::CASTLE) {
        performRookCastle(board, true);
    }
}


#pragma mark - Getters

// Squares
int BoardMove::getFromRow() const { return fromRow; }
int BoardMove::getToRow() const { return toRow; }
int BoardMove::getCaptureRow() const { return captureRow; }
int BoardMove::getFromCol() const { return fromCol; }
int BoardMove::getToCol() const { return toCol; }
int BoardMove::getCaptureCol() const { return captureCol; }

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
