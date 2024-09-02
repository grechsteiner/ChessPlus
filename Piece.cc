// Piece.cc

#include <vector>

#include "Piece.h"
#include "Constants.h"
#include "PieceInfo.h"
#include "BoardMove.h"

class ChessBoard;
class BoardSquare;


Piece::Piece(PieceType pieceType, Team team, PieceDirection pieceDirection, bool hasMoved, int pieceScore, std::string const &image, std::string const &display) :
    pieceInfo(PieceInfo(pieceType, team, pieceDirection, hasMoved, pieceScore, image, display)) {}

std::vector<BoardMove> Piece::getMoves(ChessBoard const &chessBoard, BoardSquare const &fromSquare, bool onlyAttackingMoves) const {
    return getMovesImpl(chessBoard, fromSquare, onlyAttackingMoves);
}

PieceInfo const& Piece::getPieceInfo() const { return pieceInfo; }
