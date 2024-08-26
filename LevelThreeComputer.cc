// LevelThreeComputer.cc

#include <vector>
#include <cassert>
#include <algorithm>

#include "LevelThreeComputer.h"
#include "Constants.h"
#include "Move.h"
#include "Board.h"

LevelThreeComputer::LevelThreeComputer() : BasicComputerPlayer() {}

std::vector<Move> LevelThreeComputer::getPossibleMoves(Board &board, Color color) const {

    std::vector<Move> captureAvoidingMoves = board.getCaptureAvoidingMoves(color);
    if (!captureAvoidingMoves.empty()) {
        std::vector<Move> capturingMoves = board.getCapturingMoves(color);
        std::vector<Move> checkApplyMoves = board.getCheckApplyingMoves(color);

        std::vector<Move> topMoves;
        for (Move const & move : captureAvoidingMoves) {
            if (std::find(capturingMoves.begin(), capturingMoves.end(), move) != capturingMoves.end()) {
                topMoves.push_back(move);
            }
        }

        for (Move const & move : captureAvoidingMoves) {
            if (std::find(checkApplyMoves.begin(), checkApplyMoves.end(), move) != checkApplyMoves.end()) {
                if (std::find(topMoves.begin(), topMoves.end(), move) == topMoves.end()) {
                    topMoves.push_back(move);
                }
            }
        }

        return !topMoves.empty() ? topMoves : captureAvoidingMoves;
    }

    std::vector<Move> moves = board.getCapturingMoves(color);
    std::vector<Move> checkApplyMoves = board.getCheckApplyingMoves(color);
    moves.insert(moves.end(), checkApplyMoves.begin(), checkApplyMoves.end());
    return moves.empty() ? board.getLegalMoves(color) : moves;
}
