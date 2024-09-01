// Piece.cc

#include <vector>
#include <memory>

#include "Board.h"
#include "Constants.h"
#include "Piece.h"


Piece::Piece(PieceType pieceType, Team team, PieceDirection pieceDirection, bool hasMoved, int pieceScore, std::string const &image, std::string const &display) :
    pieceInfo(pieceType, team, pieceDirection, hasMoved, pieceScore, image, display) {}

std::vector<BoardMove> Piece::getMoves(ChessBoard const &board, BoardSquare const &boardSquare, bool onlyAttackingMoves) const {
    return getMovesImplementation(board, boardSquare, onlyAttackingMoves);
}

void Piece::createAndAppendBoardMove(std::vector<BoardMove> &moves, ChessBoard const &board, BoardSquare const &fromSquare, BoardSquare const &toSquare, BoardSquare const &captureSquare, MoveType moveType, bool isAttackingMove, std::optional<PieceType> promotionPieceType) const {
    if (board.getPieceInfoAt(fromSquare).has_value()) {
        moves.emplace_back(BoardMove(fromSquare, toSquare, captureSquare, 
                                        board.getPieceInfoAt(fromSquare).value(), board.getPieceInfoAt(captureSquare),
                                        moveType, isAttackingMove, promotionPieceType));
    }
}


#pragma mark - Getters & Setters

PieceInfo Piece::getPieceInfo() const { return pieceInfo; }

