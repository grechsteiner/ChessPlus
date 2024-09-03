// LevelOneComputer.cc

#include <vector>
#include <cassert>

#include "Constants.h"
#include "LevelOneComputer.h"
#include "Board.h"


LevelOneComputer::LevelOneComputer() : BasicComputerPlayer() {}

std::vector<BoardMove> LevelOneComputer::getPossibleMoves(ChessBoard &board, Team team) const {
    std::vector<BoardMove> possibleMoves = board.generateAllLegalMoves(team);
    return possibleMoves;
}
