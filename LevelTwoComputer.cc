// LevelTwoComputer.cc

#include <vector>
#include <cassert>

#include "LevelTwoComputer.h"
#include "Constants.h"
#include "Move.h"
#include "Board.h"

LevelTwoComputer::LevelTwoComputer() : BasicComputerPlayer() {}

std::vector<Move> LevelTwoComputer::getPossibleMoves(Board &board, Color color) const {
    std::vector<Move> allMoves;
    std::vector<Move> capturingMoves = board.getCapturingMoves(color);
    std::vector<Move> checkApplyingMoves = board.getCheckApplyingMoves(color);
    allMoves.insert(allMoves.end(), capturingMoves.begin(), capturingMoves.end());
    allMoves.insert(allMoves.end(), checkApplyingMoves.begin(), checkApplyingMoves.end());

    return allMoves.size() > 0 ? allMoves : board.getLegalMoves(color);
}
