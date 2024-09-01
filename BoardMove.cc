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
            Team::TEAM_NONE, PieceType::EMPTY, PieceDirection::BLANK, false, 0);

BoardMove::BoardMove(BoardSquare const &fromSquare, BoardSquare const &toSquare, BoardSquare const &captureSquare,
                    MoveType moveType, bool isAttackingMove, PieceType promotionPieceType,
                    bool hasMovedBeforeMove, PieceType pieceTypeBeforeMove, int pieceScoreBeforeMove,
                    Team capturedTeam, PieceType capturedPieceType, PieceDirection capturedPieceDirection, bool capturedHasMoved, int capturedPieceScore) :

    fromSquare(fromSquare), toSquare(toSquare), captureSquare(captureSquare),
    moveType(moveType), isAttackingMove(isAttackingMove), promotionPieceType(promotionPieceType),
    hasMovedBeforeMove(hasMovedBeforeMove), pieceTypeBeforeMove(pieceTypeBeforeMove), pieceScoreBeforeMove(pieceScoreBeforeMove),
    capturedTeam(capturedTeam), capturedPieceType(capturedPieceType), capturedPieceDirection(capturedPieceDirection), capturedHasMoved(capturedHasMoved), capturedPieceScore(capturedPieceScore) 
{}

bool BoardMove::operator==(BoardMove const &other) const {
    return 
        fromSquare == other.fromSquare &&
        toSquare == other.toSquare &&
        captureSquare == other.captureSquare &&
        moveType == other.moveType &&
        isAttackingMove == other.isAttackingMove &&
        promotionPieceType == other.promotionPieceType &&
        hasMovedBeforeMove == other.hasMovedBeforeMove &&
        pieceTypeBeforeMove == other.pieceTypeBeforeMove &&
        pieceScoreBeforeMove == other.pieceScoreBeforeMove &&
        capturedTeam == other.capturedTeam &&
        capturedPieceType == other.capturedPieceType &&
        capturedPieceDirection == other.capturedPieceDirection &&
        capturedHasMoved == other.capturedHasMoved &&
        capturedPieceScore == other.capturedPieceScore;
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
        BoardSquare rookFromSquare(toRow, rookFromCol);
        BoardSquare rookToSquare(toRow, rookToCol);
        PieceInfo rookPieceInfo = board.getPieceInfoAt(rookFromSquare);
        board.setPosition(rookToSquare, rookPieceInfo.team, rookPieceInfo.pieceType, rookPieceInfo.pieceDirection, hasRookMoved, rookPieceInfo.pieceScore);
        board.clearPosition(rookFromSquare);
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
        BoardSquare rookFromSquare(rookFromRow, toCol);
        BoardSquare rookToSquare(rookToRow, toCol);
        PieceInfo rookPieceInfo = board.getPieceInfoAt(rookFromSquare);
        board.setPosition(rookToSquare, rookPieceInfo.team, rookPieceInfo.pieceType, rookPieceInfo.pieceDirection, hasRookMoved, rookPieceInfo.pieceScore);
        board.clearPosition(rookFromSquare);
    } else {
        assert(false);
    }
}

void BoardMove::makeMove(ChessBoard &board) const {
    PieceInfo pieceInfo = board.getPieceInfoAt(fromSquare);

    // Basic Stuff
    board.clearPosition(captureSquare);      // Set captured piece to blank (may not be square moving to)
    board.setPosition(toSquare, pieceInfo.team, pieceInfo.pieceType, pieceInfo.pieceDirection, true, pieceInfo.pieceScore);        // Move the piece to new square (hasMoved = true)
    board.clearPosition(fromSquare);                                    // Clear old spot

    // Apply Promotion
    if (promotionPieceType != PieceType::EMPTY) {
        PieceInfo unPromotedPieceInfo = board.getPieceInfoAt(toSquare);                                                                      // Piece already moved
        board.setPosition(toSquare, unPromotedPieceInfo.team, promotionPieceType, unPromotedPieceInfo.pieceDirection, true);    // Default piece score for promoted piece
    }

    // Apply Castle (rook part)
    if (moveType == MoveType::CASTLE) {
        performRookCastle(board, false);
    }
}

void BoardMove::undoMove(ChessBoard &board) const {
    PieceInfo pieceInfo = board.getPieceInfoAt(toSquare);

    // Basic Stuff
    board.setPosition(fromSquare, pieceInfo.team, pieceInfo.pieceType, pieceInfo.pieceDirection, hasMovedBeforeMove, pieceInfo.pieceScore);   // Undo moving piece (has moved to what it was before)
    board.clearPosition(toSquare);
    board.setPosition(captureSquare, capturedTeam, capturedPieceType, capturedPieceDirection, capturedHasMoved, capturedPieceScore);  // Place captured piece back

    // Undo promotion
    if (promotionPieceType != PieceType::EMPTY) {
        PieceInfo promotedPieceInfo = board.getPieceInfoAt(fromSquare);                                                                        // Piece already moved back
        board.setPosition(fromSquare, promotedPieceInfo.team, pieceTypeBeforeMove, promotedPieceInfo.pieceDirection, promotedPieceInfo.hasMoved, pieceScoreBeforeMove); // Get piece type & score prior to promotion
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
bool BoardMove::getHasMovedBeforeMove() const { return hasMovedBeforeMove; }
PieceType BoardMove::getPieceTypeBeforeMove() const { return pieceTypeBeforeMove; }
int BoardMove::getPieceScoreBeforeMove() const { return pieceScoreBeforeMove; }

// Captured Piece Info
Team BoardMove::getCapturedTeam() const { return capturedTeam; }
PieceType BoardMove::getCapturedPieceType() const { return capturedPieceType; }
PieceDirection BoardMove::getCapturedPieceDirection() const { return capturedPieceDirection; }
bool BoardMove::getCapturedHasMoved() const { return capturedHasMoved; }
int BoardMove::getCapturedPieceScore() const { return capturedPieceScore; }
