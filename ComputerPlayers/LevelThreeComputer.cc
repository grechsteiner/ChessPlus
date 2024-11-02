// LevelThreeComputer.cc

#include <vector>
#include <cassert>
#include <algorithm>

#include "LevelThreeComputer.h"
#include "Constants.h"

#include "ChessBoardImpl.h"

LevelThreeComputer::LevelThreeComputer() : BasicComputerPlayer() {}

std::vector<OldBoardMove> LevelThreeComputer::getPossibleMoves(ChessBoard const &chessBoard, Team team) const {

    std::vector<OldBoardMove> captureAvoidingMoves = chessBoard.generateCaptureAvoidingMoves(team);
    if (!captureAvoidingMoves.empty()) {
        std::vector<OldBoardMove> capturingMoves = chessBoard.generateCapturingMoves(team);
        std::vector<OldBoardMove> checkApplyMoves = chessBoard.generateCheckApplyingMoves(team);

        std::vector<OldBoardMove> topMoves;
        for (OldBoardMove const & move : captureAvoidingMoves) {
            if (std::find(capturingMoves.begin(), capturingMoves.end(), move) != capturingMoves.end()) {
                topMoves.push_back(move);
            }
        }

        for (OldBoardMove const & move : captureAvoidingMoves) {
            if (std::find(checkApplyMoves.begin(), checkApplyMoves.end(), move) != checkApplyMoves.end()) {
                if (std::find(topMoves.begin(), topMoves.end(), move) == topMoves.end()) {
                    topMoves.push_back(move);
                }
            }
        }

        return !topMoves.empty() ? topMoves : captureAvoidingMoves;
    }

    std::vector<OldBoardMove> moves = chessBoard.generateCapturingMoves(team);
    std::vector<OldBoardMove> checkApplyMoves = chessBoard.generateCheckApplyingMoves(team);
    moves.insert(moves.end(), checkApplyMoves.begin(), checkApplyMoves.end());
    return moves.empty() ? chessBoard.generateAllLegalMoves(team) : moves;
}
