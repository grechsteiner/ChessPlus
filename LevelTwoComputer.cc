// LevelTwoComputer.cc

#include <vector>
#include <cassert>

#include "LevelTwoComputer.h"
#include "Constants.h"
#include "Move.h"
#include "Board.h"

LevelTwoComputer::LevelTwoComputer() : BasicComputerPlayer() {}

std::vector<FullMove> LevelTwoComputer::getPossibleMoves(ChessBoard &board, Color color) const {
    std::vector<FullMove> allMoves;
    std::vector<FullMove> capturingMoves = board.getCapturingMoves(color);
    std::vector<FullMove> checkApplyingMoves = board.getCheckApplyingMoves(color);
    allMoves.insert(allMoves.end(), capturingMoves.begin(), capturingMoves.end());
    allMoves.insert(allMoves.end(), checkApplyingMoves.begin(), checkApplyingMoves.end());

    return allMoves.size() > 0 ? allMoves : board.getLegalMoves(color);
}
