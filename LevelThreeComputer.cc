// LevelThreeComputer.cc

#include <vector>
#include <cassert>
#include <algorithm>

#include "LevelThreeComputer.h"
#include "Constants.h"

#include "ChessBoard.h"

LevelThreeComputer::LevelThreeComputer() : BasicComputerPlayer() {}

std::vector<BoardMove> LevelThreeComputer::getPossibleMoves(IChessBoard &chessBoard, Team team) const {

    std::vector<BoardMove> captureAvoidingMoves = chessBoard.generateCaptureAvoidingMoves(team);
    if (!captureAvoidingMoves.empty()) {
        std::vector<BoardMove> capturingMoves = chessBoard.generateCapturingMoves(team);
        std::vector<BoardMove> checkApplyMoves = chessBoard.generateCheckApplyingMoves(team);

        std::vector<BoardMove> topMoves;
        for (BoardMove const & move : captureAvoidingMoves) {
            if (std::find(capturingMoves.begin(), capturingMoves.end(), move) != capturingMoves.end()) {
                topMoves.push_back(move);
            }
        }

        for (BoardMove const & move : captureAvoidingMoves) {
            if (std::find(checkApplyMoves.begin(), checkApplyMoves.end(), move) != checkApplyMoves.end()) {
                if (std::find(topMoves.begin(), topMoves.end(), move) == topMoves.end()) {
                    topMoves.push_back(move);
                }
            }
        }

        return !topMoves.empty() ? topMoves : captureAvoidingMoves;
    }

    std::vector<BoardMove> moves = chessBoard.generateCapturingMoves(team);
    std::vector<BoardMove> checkApplyMoves = chessBoard.generateCheckApplyingMoves(team);
    moves.insert(moves.end(), checkApplyMoves.begin(), checkApplyMoves.end());
    return moves.empty() ? chessBoard.generateAllLegalMoves(team) : moves;
}
