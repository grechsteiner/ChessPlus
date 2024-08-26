// Empty.cc

#include <vector>
#include <cassert>

#include "Constants.h"
#include "Empty.h"
#include "BoardPieceInterface.h"
#include "Piece.h"
#include "Move.h"

Empty::Empty(Color pieceColor, PieceDirection pieceDirection, bool hasMoved, int pieceScore) :
    Piece(pieceColor, PieceType::EMPTY, pieceDirection, hasMoved, " ", " ", pieceScore) {}

std::vector<Move> Empty::getMovesImplementation(BoardPieceInterface const &board, int pieceRow, int pieceCol, bool attackingMoves) const {
    return {};
}

