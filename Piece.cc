// Piece.cc

#include <vector>
#include <memory>

#include "Board.h"
#include "Constants.h"
#include "Piece.h"


Piece::Piece(Color pieceColor, PieceType pieceType, PieceDirection pieceDirection, bool hasMoved, std::string const &image, std::string const &display, int pieceScore) :
    pieceColor(pieceColor), pieceType(pieceType), pieceDirection(pieceDirection), hasMoved(hasMoved), image(image), display(display), pieceScore(pieceScore) {}

std::vector<BoardMove> Piece::getMoves(ChessBoard const &board, int pieceRow, int pieceCol, bool attackingMoves) const {
    return getMovesImplementation(board, pieceRow, pieceCol, attackingMoves);
}

BoardMove Piece::createFullMove(ChessBoard const &board, int fromRow, int fromCol, int toRow, int toCol, int captureRow, int captureCol, MoveType moveType, bool isAttackingMove, PieceType promotionPieceType) const {
    Piece const &capturePiece = board.getPieceAt(captureRow, captureCol);
    return BoardMove(fromRow, fromCol, toRow, toCol, captureRow, captureCol, 
                    moveType, isAttackingMove, promotionPieceType, 
                    hasMoved, pieceType, pieceScore, 
                    capturePiece.getPieceColor(), capturePiece.getPieceType(), capturePiece.getPieceDirection(), capturePiece.getHasMoved(), capturePiece.getPieceScore());
}


#pragma mark - Getters

Color Piece::getPieceColor() const {
    return pieceColor;
}

PieceType Piece::getPieceType() const {
    return pieceType;
}

PieceDirection Piece::getPieceDirection() const {
    return pieceDirection;
}

bool Piece::getHasMoved() const {
    return hasMoved;
}

void Piece::setHasMoved(bool newHasMoved) {
    hasMoved = newHasMoved;
}

int Piece::getPieceScore() const {
    return pieceScore;
}

const std::string& Piece::getImage() const {
    return image;
}

const std::string& Piece::getDisplay() const {
    return display;
}
