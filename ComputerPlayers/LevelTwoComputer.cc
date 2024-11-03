// LevelTwoComputer.cc

#include <vector>
#include <cassert>

#include "LevelTwoComputer.h"
#include "Constants.h"

#include "ChessBoardImpl.h"

LevelTwoComputer::LevelTwoComputer() : BasicComputerPlayer() {}

std::vector<std::unique_ptr<BoardMove>> LevelTwoComputer::getPossibleMoves(ChessBoard const &chessBoard, Team team) const {
    std::vector<std::unique_ptr<BoardMove>> capturingMoves = chessBoard.generateCapturingMoves(team);
    std::vector<std::unique_ptr<BoardMove>> checkApplyingMoves = chessBoard.generateCheckApplyingMoves(team);

    for (std::unique_ptr<BoardMove> &checkApplyMove : checkApplyingMoves) {
        capturingMoves.emplace_back(std::move(checkApplyMove));
    }
    checkApplyingMoves.clear();

    return capturingMoves.size() > 0 ? capturingMoves : chessBoard.generateAllLegalMoves(team);
}
