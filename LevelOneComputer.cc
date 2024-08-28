// LevelOneComputer.cc

#include <vector>
#include <cassert>

#include "Constants.h"
#include "LevelOneComputer.h"
#include "Board.h"
#include "Move.h"

LevelOneComputer::LevelOneComputer() : BasicComputerPlayer() {}

std::vector<FullMove> LevelOneComputer::getPossibleMoves(BoardComputerInterface &board, Color color) const {
    std::vector<FullMove> possibleMoves = board.getLegalMoves(color);
    return possibleMoves;
}
