// LevelTwoComputer.cc

#include <vector>
#include <cassert>

#include "LevelTwoComputer.h"
#include "Constants.h"

#include "ChessBoardImpl.h"

LevelTwoComputer::LevelTwoComputer() : BasicComputerPlayer() {}

std::vector<OldBoardMove> LevelTwoComputer::getPossibleMoves(ChessBoard const &chessBoard, Team team) const {
    std::vector<OldBoardMove> allMoves;
    std::vector<OldBoardMove> capturingMoves = chessBoard.generateCapturingMoves(team);
    std::vector<OldBoardMove> checkApplyingMoves = chessBoard.generateCheckApplyingMoves(team);
    allMoves.insert(allMoves.end(), capturingMoves.begin(), capturingMoves.end());
    allMoves.insert(allMoves.end(), checkApplyingMoves.begin(), checkApplyingMoves.end());

    return allMoves.size() > 0 ? allMoves : chessBoard.generateAllLegalMoves(team);
}
