// LevelThreeComputer.cc

#include <vector>
#include <cassert>
#include <algorithm>

#include "LevelThreeComputer.h"
#include "Constants.h"
#include "Move.h"
#include "Board.h"

LevelThreeComputer::LevelThreeComputer() : BasicComputerPlayer() {}

std::vector<FullMove> LevelThreeComputer::getPossibleMoves(ChessBoard &board, Color color) const {

    std::vector<FullMove> captureAvoidingMoves = board.getCaptureAvoidingMoves(color);
    if (!captureAvoidingMoves.empty()) {
        std::vector<FullMove> capturingMoves = board.getCapturingMoves(color);
        std::vector<FullMove> checkApplyMoves = board.getCheckApplyingMoves(color);

        std::vector<FullMove> topMoves;
        for (FullMove const & move : captureAvoidingMoves) {
            if (std::find(capturingMoves.begin(), capturingMoves.end(), move) != capturingMoves.end()) {
                topMoves.push_back(move);
            }
        }

        for (FullMove const & move : captureAvoidingMoves) {
            if (std::find(checkApplyMoves.begin(), checkApplyMoves.end(), move) != checkApplyMoves.end()) {
                if (std::find(topMoves.begin(), topMoves.end(), move) == topMoves.end()) {
                    topMoves.push_back(move);
                }
            }
        }

        return !topMoves.empty() ? topMoves : captureAvoidingMoves;
    }

    std::vector<FullMove> moves = board.getCapturingMoves(color);
    std::vector<FullMove> checkApplyMoves = board.getCheckApplyingMoves(color);
    moves.insert(moves.end(), checkApplyMoves.begin(), checkApplyMoves.end());
    return moves.empty() ? board.getLegalMoves(color) : moves;
}
