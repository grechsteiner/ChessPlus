// LevelOneComputer.cc

#include <vector>
#include <cassert>

#include "Constants.h"
#include "LevelOneComputer.h"
#include "Board.h"
#include "Move.h"

LevelOneComputer::LevelOneComputer() : BasicComputerPlayer() {}

std::vector<Move> LevelOneComputer::getPossibleMoves(Board &board, Color color) const {
    std::vector<Move> possibleMoves = board.getLegalMoves(color);
    return possibleMoves;
}
