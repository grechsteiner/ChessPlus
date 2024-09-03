// LevelTwoComputer.cc

#include <vector>
#include <cassert>

#include "LevelTwoComputer.h"
#include "Constants.h"

#include "Board.h"

LevelTwoComputer::LevelTwoComputer() : BasicComputerPlayer() {}

std::vector<BoardMove> LevelTwoComputer::getPossibleMoves(ChessBoard &board, Team team) const {
    std::vector<BoardMove> allMoves;
    std::vector<BoardMove> capturingMoves = board.generateCapturingMoves(team);
    std::vector<BoardMove> checkApplyingMoves = board.generateCheckApplyingMoves(team);
    allMoves.insert(allMoves.end(), capturingMoves.begin(), capturingMoves.end());
    allMoves.insert(allMoves.end(), checkApplyingMoves.begin(), checkApplyingMoves.end());

    return allMoves.size() > 0 ? allMoves : board.generateAllLegalMoves(team);
}
