// Empty.cc

#include <vector>
#include <cassert>

#include "Constants.h"
#include "Empty.h"
#include "ChessBoard.h"
#include "Piece.h"
#include "BoardMove.h"

Empty::Empty(Team team, PieceDirection pieceDirection, bool hasMoved, int pieceScore) :
    Piece(team, PieceType::EMPTY, pieceDirection, hasMoved, " ", " ", pieceScore) {}

std::vector<BoardMove> Empty::getMovesImplementation(ChessBoard const &board, BoardSquare const &boardSquare, bool attackingMoves) const {
    return std::vector<BoardMove>();
}

