// Piece.cc

#include <vector>
#include <memory>

#include "Board.h"
#include "Constants.h"
#include "Piece.h"


Piece::Piece(Color pieceColor, PieceType pieceType, PieceDirection pieceDirection, bool hasMoved, std::string const &image, std::string const &display, int pieceScore) :
    pieceInfo(pieceColor, pieceType, pieceDirection, hasMoved, image, display, pieceScore) {}

std::vector<BoardMove> Piece::getMoves(ChessBoard const &board, BoardSquare const &boardSquare, bool attackingMoves) const {
    return getMovesImplementation(board, boardSquare, attackingMoves);
}

BoardMove Piece::createBoardMove(ChessBoard const &board, BoardSquare const &fromSquare, BoardSquare const &toSquare, BoardSquare const &captureSquare, MoveType moveType, bool isAttackingMove, PieceType promotionPieceType) const {
    PieceInfo capturePieceInfo = board.getPieceInfoAt(captureSquare);
    return BoardMove(fromSquare, toSquare, captureSquare, 
                    moveType, isAttackingMove, promotionPieceType, 
                    pieceInfo.getHasMoved(), pieceInfo.getPieceType(), pieceInfo.getPieceScore(), 
                    capturePieceInfo.getPieceColor(), capturePieceInfo.getPieceType(), capturePieceInfo.getPieceDirection(), capturePieceInfo.getHasMoved(), capturePieceInfo.getPieceScore());
}


#pragma mark - Getters

PieceInfo& Piece::getPieceInfo() { return pieceInfo; }
