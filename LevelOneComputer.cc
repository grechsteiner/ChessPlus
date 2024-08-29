// LevelOneComputer.cc

#include <vector>
#include <cassert>

#include "Constants.h"
#include "LevelOneComputer.h"
#include "Board.h"
#include "Move.h"

LevelOneComputer::LevelOneComputer() : BasicComputerPlayer() {}

std::vector<BoardMove> LevelOneComputer::getPossibleMoves(ChessBoard &board, Color color) const {
    std::vector<BoardMove> possibleMoves = board.getLegalMoves(color);
    return possibleMoves;
}
