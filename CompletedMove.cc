// CompletedMove.cc

#include <vector>
#include <memory>
#include <cassert>
#include <string>
#include <iostream>

#include "CompletedMove.h"
#include "Constants.h"
#include "Move.h"
#include "Piece.h"


// Default assign captured information as (toRow, toCol)
CompletedMove::CompletedMove(Move const &move, std::vector<std::vector<std::unique_ptr<Piece>>> const &grid) : 
    Move(move), 
    capturedRow(toRow), capturedCol(toCol), 
    capturedColor(grid[getVectorRow(grid.size(), capturedRow)][getVectorCol(capturedCol)]->getPieceColor()),
    capturedPieceType(grid[getVectorRow(grid.size(), capturedRow)][getVectorCol(capturedCol)]->getPieceType()),
    capturedPieceDirection(grid[getVectorRow(grid.size(), capturedRow)][getVectorCol(capturedCol)]->getPieceDirection()),
    capturedHasMoved(grid[getVectorRow(grid.size(), capturedRow)][getVectorCol(capturedCol)]->getHasMoved()),
    capturedPieceScore(grid[getVectorRow(grid.size(), capturedRow)][getVectorCol(capturedCol)]->getPieceScore()),
    movedHasMoved(grid[getVectorRow(grid.size(), fromRow)][getVectorCol(fromCol)]->getHasMoved()),
    moveType(MoveType::STANDARD),
    castleMove(nullptr)
    {

    // Pre calculate
    int vectorFromRow = getVectorRow(grid.size(), fromRow);
    int vectorFromCol = getVectorCol(fromCol);
    int vectorToRow = getVectorRow(grid.size(), toRow);
    int vectorToCol = getVectorCol(toCol);

    // Check if double pawn move type
    if (grid[vectorFromRow][vectorFromCol]->getPieceType() == PieceType::PAWN && ((abs(vectorFromRow - vectorToRow) == 2) || (abs(vectorFromCol - vectorToCol) == 2))) {
        moveType = MoveType::DOUBLE_PAWN;
        return;
    }

    // Check enpassant
    if (grid[vectorFromRow][vectorFromCol]->getPieceType() == PieceType::PAWN && grid[vectorToRow][vectorToCol]->getPieceType() == PieceType::EMPTY) {
        
        // Check what direction the pawn is moving
        switch (grid[vectorFromRow][vectorFromCol]->getPieceDirection()) {
            case PieceDirection::NORTH:
            case PieceDirection::SOUTH:
                if (fromCol != toCol) {
                    capturedRow = fromRow;
                    capturedCol = toCol;
                    capturedColor = grid[getVectorRow(grid.size(), capturedRow)][getVectorCol(capturedCol)]->getPieceColor();
                    capturedPieceType = grid[getVectorRow(grid.size(), capturedRow)][getVectorCol(capturedCol)]->getPieceType();
                    capturedPieceDirection = grid[getVectorRow(grid.size(), capturedRow)][getVectorCol(capturedCol)]->getPieceDirection();
                    capturedHasMoved = grid[getVectorRow(grid.size(), capturedRow)][getVectorCol(capturedCol)]->getHasMoved();
                    capturedPieceScore = grid[getVectorRow(grid.size(), capturedRow)][getVectorCol(capturedCol)]->getPieceScore();
                    moveType = MoveType::ENPASSANT;
                } 
                break;
            case PieceDirection::EAST:
            case PieceDirection::WEST:
                if (fromRow != toRow) {
                    capturedRow = toRow;
                    capturedCol = fromCol;
                    capturedColor = grid[getVectorRow(grid.size(), capturedRow)][getVectorCol(capturedCol)]->getPieceColor();
                    capturedPieceType = grid[getVectorRow(grid.size(), capturedRow)][getVectorCol(capturedCol)]->getPieceType();
                    capturedPieceDirection = grid[getVectorRow(grid.size(), capturedRow)][getVectorCol(capturedCol)]->getPieceDirection();
                    capturedHasMoved = grid[getVectorRow(grid.size(), capturedRow)][getVectorCol(capturedCol)]->getHasMoved();
                    capturedPieceScore = grid[getVectorRow(grid.size(), capturedRow)][getVectorCol(capturedCol)]->getPieceScore();
                    moveType = MoveType::ENPASSANT;
                }
                break;
            default:
                break;
        }        
    }

    // Check castle
    if (grid[vectorFromRow][vectorFromCol]->getPieceType() == PieceType::KING) {
        
        // Check direction
        switch (grid[vectorFromRow][vectorFromCol]->getPieceDirection()) {
            case PieceDirection::NORTH:
            case PieceDirection::SOUTH:
                if (abs(vectorFromCol - vectorToCol) == 2) {
                    castleMove = vectorFromCol > vectorToCol
                        ? std::make_unique<CompletedMove>(Move(grid.size(), vectorFromRow, vectorToCol - 2, vectorFromRow, vectorToCol + 1), grid)      // Left
                        : std::make_unique<CompletedMove>(Move(grid.size(), vectorFromRow, vectorToCol + 1, vectorFromRow, vectorToCol - 1), grid);     // Right
                    moveType = MoveType::CASTLE;
                }
                break;
            case PieceDirection::EAST:
            case PieceDirection::WEST:
                if (abs(vectorFromRow - vectorToRow) == 2) {
                    castleMove = vectorFromRow > vectorToRow 
                        ? std::make_unique<CompletedMove>(Move(grid.size(), vectorToRow - 2, vectorFromCol, vectorToRow + 1, vectorFromCol), grid)      // Up
                        : std::make_unique<CompletedMove>(Move(grid.size(), vectorToRow + 1, vectorFromCol, vectorToRow - 1, vectorFromCol), grid);     // Down
                    moveType = MoveType::CASTLE;
                }
                break;
            default:
                break;
        }
    }
}


#pragma mark - Getters

int CompletedMove::getCapturedRow() const {
    return capturedRow;
}

char CompletedMove::getCapturedCol() const {
    return capturedCol;
}

Color CompletedMove::getCapturedColor() const {
    return capturedColor;
}

PieceType CompletedMove::getCapturedPieceType() const {
    return capturedPieceType;
}

PieceDirection CompletedMove::getCapturedPieceDirection() const {
    return capturedPieceDirection;
}

bool CompletedMove::getCapturedHasMoved() const {
    return capturedHasMoved;
}
int CompletedMove::getCapturedScore() const {
    return capturedPieceScore;
}

bool CompletedMove::getMovedHasMoved() const {
    return movedHasMoved;
}

MoveType CompletedMove::getMoveType() const {
    return moveType;
}
    
const std::unique_ptr<CompletedMove>& CompletedMove::getCastleMove() const {
    return castleMove;
}
