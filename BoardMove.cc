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
            PieceInfo(Team::TEAM_ONE, PieceType::BISHOP, PieceDirection::NORTH, false, " ", " ", 0), std::nullopt,
            MoveType::STANDARD, false);

BoardMove::BoardMove(BoardSquare const &fromSquare, BoardSquare const &toSquare, BoardSquare const &captureSquare,
                    PieceInfo movedPieceInfo, std::optional<PieceInfo> capturedPieceInfo,
                    MoveType moveType, bool isAttackingMove, std::optional<PieceType> promotionPieceType) :

    fromSquare(fromSquare), toSquare(toSquare), captureSquare(captureSquare),
    movedPieceInfo(movedPieceInfo), capturedPieceInfo(capturedPieceInfo),
    moveType(moveType), isAttackingMove(isAttackingMove), promotionPieceType(promotionPieceType) 
{}

bool BoardMove::operator==(BoardMove const &other) const {
    return 
        fromSquare == other.fromSquare &&
        toSquare == other.toSquare &&
        captureSquare == other.captureSquare &&
        movedPieceInfo == other.movedPieceInfo &&
        capturedPieceInfo == other.capturedPieceInfo &&
        moveType == other.moveType &&
        isAttackingMove == other.isAttackingMove &&
        promotionPieceType == other.promotionPieceType;
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
        BoardSquare rookFromSquare = isUndo ? BoardSquare(toRow, rookToCol) : BoardSquare(toRow, rookFromCol);
        BoardSquare rookToSquare = isUndo ? BoardSquare(toRow, rookFromCol) : BoardSquare(toRow, rookToCol);
        std::optional<PieceInfo> rookPiece = board.getPieceInfoAt(rookFromSquare);
        if (rookPiece.has_value()) {
            PieceInfo rookPieceInfo = rookPiece.value();
            board.setPosition(rookToSquare, rookPieceInfo.team, rookPieceInfo.pieceType, rookPieceInfo.pieceDirection, hasRookMoved, rookPieceInfo.pieceScore);
            board.clearPosition(rookFromSquare);
        }
        
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
        BoardSquare rookFromSquare = isUndo ? BoardSquare(rookToRow, toCol) : BoardSquare(rookFromRow, toCol);
        BoardSquare rookToSquare = isUndo ? BoardSquare(rookFromRow, toCol) : BoardSquare(rookToRow, toCol);
        std::optional<PieceInfo> rookPiece = board.getPieceInfoAt(rookFromSquare);
        if (rookPiece.has_value()) {
            PieceInfo rookPieceInfo = rookPiece.value();
            board.setPosition(rookToSquare, rookPieceInfo.team, rookPieceInfo.pieceType, rookPieceInfo.pieceDirection, hasRookMoved, rookPieceInfo.pieceScore);
            board.clearPosition(rookFromSquare);
        } 
        
    }
}

void BoardMove::makeMove(ChessBoard &board) const {

    // Basic Stuff
    board.clearPosition(captureSquare);      // Set captured piece to blank (may not be square moving to)
    board.setPosition(toSquare, movedPieceInfo.team, movedPieceInfo.pieceType, movedPieceInfo.pieceDirection, true, movedPieceInfo.pieceScore);        // Move the piece to new square (hasMoved = true)
    board.clearPosition(fromSquare);                                    // Clear old spot

    // Apply Promotion
    if (promotionPieceType.has_value()) {
        board.setPosition(toSquare, movedPieceInfo.team, promotionPieceType.value(), movedPieceInfo.pieceDirection, true);    // Default piece score for promoted piece, yes has moved
    }

    // Apply Castle (rook part)
    if (moveType == MoveType::CASTLE) {
        performRookCastle(board, false);
    }
}

void BoardMove::undoMove(ChessBoard &board) const {

    // Basic Stuff
    board.setPosition(fromSquare, movedPieceInfo.team, movedPieceInfo.pieceType, movedPieceInfo.pieceDirection, movedPieceInfo.hasMoved, movedPieceInfo.pieceScore);   // Undo moving piece (has moved to what it was before)
    board.clearPosition(toSquare);                                                                                                      // Clear toSquare

    // Place captured piece back
    if (capturedPieceInfo.has_value()) {
        PieceInfo capturedPieceInfoValue = capturedPieceInfo.value();
        board.setPosition(captureSquare, capturedPieceInfoValue.team, capturedPieceInfoValue.pieceType, capturedPieceInfoValue.pieceDirection, capturedPieceInfoValue.hasMoved, capturedPieceInfoValue.pieceScore);    
    } else {
        board.clearPosition(captureSquare);
    }
    
    // Undo promotion
    if (promotionPieceType.has_value()) {
        board.setPosition(fromSquare, movedPieceInfo.team, movedPieceInfo.pieceType, movedPieceInfo.pieceDirection, movedPieceInfo.hasMoved, movedPieceInfo.pieceScore); // Get piece type & score prior to promotion
    }

    // Undo castle
    if (moveType == MoveType::CASTLE) {
        performRookCastle(board, true);
    }
}


#pragma mark - Getters

// Squares
BoardSquare BoardMove::getFromSquare() const { return fromSquare; }
BoardSquare BoardMove::getToSquare() const { return toSquare; }
BoardSquare BoardMove::getCaptureSquare() const { return captureSquare; }

// Moved Piece Info
PieceInfo BoardMove::getMovedPieceInfo() const { return movedPieceInfo; }

// Captured Piece Info
std::optional<PieceInfo> BoardMove::getCapturedPieceInfo() const { return capturedPieceInfo; }

// General Info
MoveType BoardMove::getMoveType() const { return moveType; }
bool BoardMove::getIsAttackingMove() const { return isAttackingMove; }
std::optional<PieceType> BoardMove::getPromotionPieceType() const { return promotionPieceType; }
