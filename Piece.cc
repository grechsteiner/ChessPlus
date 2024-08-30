// Piece.cc

#include <vector>
#include <memory>

#include "Board.h"
#include "Constants.h"
#include "Piece.h"


Piece::Piece(Team team, PieceType pieceType, PieceDirection pieceDirection, bool hasMoved, std::string const &image, std::string const &display, int pieceScore) :
    pieceInfo(team, pieceType, pieceDirection, hasMoved, image, display, pieceScore) {}

std::vector<BoardMove> Piece::getMoves(ChessBoard const &board, BoardSquare const &boardSquare, bool onlyAttackingMoves) const {
    return getMovesImplementation(board, boardSquare, onlyAttackingMoves);
}

BoardMove Piece::createBoardMove(ChessBoard const &board, BoardSquare const &fromSquare, BoardSquare const &toSquare, BoardSquare const &captureSquare, MoveType moveType, bool isAttackingMove, PieceType promotionPieceType) const {
    PieceInfo capturePieceInfo = board.getPieceInfoAt(captureSquare);
    return BoardMove(fromSquare, toSquare, captureSquare, 
                    moveType, isAttackingMove, promotionPieceType, 
                    pieceInfo.hasMoved, pieceInfo.pieceType, pieceInfo.pieceScore, 
                    capturePieceInfo.team, capturePieceInfo.pieceType, capturePieceInfo.pieceDirection, capturePieceInfo.hasMoved, capturePieceInfo.pieceScore);
}


#pragma mark - Getters & Setters

PieceInfo Piece::getPieceInfo() const { return pieceInfo; }

void Piece::setHasMoved(bool newHasMoved) {
    pieceInfo.hasMoved = newHasMoved;
}
