// Empty.cc

#include <vector>
#include <cassert>

#include "Constants.h"
#include "Empty.h"
#include "ChessBoard.h"
#include "Piece.h"
#include "BoardMove.h"

Empty::Empty(Color pieceColor, PieceDirection pieceDirection, bool hasMoved, int pieceScore) :
    Piece(pieceColor, PieceType::EMPTY, pieceDirection, hasMoved, " ", " ", pieceScore) {}

std::vector<BoardMove> Empty::getMovesImplementation(ChessBoard const &board, BoardSquare const &boardSquare, bool attackingMoves) const {
    return {};
}

