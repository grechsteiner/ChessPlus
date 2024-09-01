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

BoardMove Piece::createBoardMove(ChessBoard const &board, BoardSquare const &fromSquare, BoardSquare const &toSquare, BoardSquare const &captureSquare, MoveType moveType, bool isAttackingMove, std::optional<PieceType> promotionPieceType) const {
    return BoardMove(fromSquare, toSquare, captureSquare, 
                    board.getPieceInfoAt(fromSquare).value(), board.getPieceInfoAt(captureSquare),
                    moveType, isAttackingMove, promotionPieceType);
}


#pragma mark - Getters & Setters

PieceInfo Piece::getPieceInfo() const { return pieceInfo; }

