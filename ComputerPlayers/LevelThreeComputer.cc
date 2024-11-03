// LevelThreeComputer.cc

#include <vector>
#include <cassert>
#include <algorithm>

#include "LevelThreeComputer.h"
#include "Constants.h"

#include "ChessBoardImpl.h"

LevelThreeComputer::LevelThreeComputer() : BasicComputerPlayer() {}

std::vector<std::unique_ptr<BoardMove>> LevelThreeComputer::getPossibleMoves(ChessBoard const &chessBoard, Team team) const {

    std::vector<std::unique_ptr<BoardMove>> captureAvoidingMoves = chessBoard.generateCaptureAvoidingMoves(team);
    if (!captureAvoidingMoves.empty()) {
        std::vector<std::unique_ptr<BoardMove>> capturingMoves = chessBoard.generateCapturingMoves(team);
        std::vector<std::unique_ptr<BoardMove>> checkApplyMoves = chessBoard.generateCheckApplyingMoves(team);

        std::vector<std::unique_ptr<BoardMove>> topMoves;
        for (std::unique_ptr<BoardMove> const & move : captureAvoidingMoves) {
            if (std::find(capturingMoves.begin(), capturingMoves.end(), move) != capturingMoves.end()) {
                topMoves.emplace_back(move->clone());
            }
        }

        for (std::unique_ptr<BoardMove> const & move : captureAvoidingMoves) {
            if (std::find(checkApplyMoves.begin(), checkApplyMoves.end(), move) != checkApplyMoves.end()) {
                if (std::find(topMoves.begin(), topMoves.end(), move) == topMoves.end()) {
                    topMoves.emplace_back(move->clone());
                }
            }
        }

        return !topMoves.empty() ? std::move(topMoves) : std::move(captureAvoidingMoves);
    }

    std::vector<std::unique_ptr<BoardMove>> moves = chessBoard.generateCapturingMoves(team);
    std::vector<std::unique_ptr<BoardMove>> checkApplyMoves = chessBoard.generateCheckApplyingMoves(team);
    for (std::unique_ptr<BoardMove> &checkApplyMove : checkApplyMoves) {
        moves.emplace_back(std::move(checkApplyMove));
    }
    checkApplyMoves.clear();

    std::vector<std::unique_ptr<BoardMove>> allMoves = chessBoard.generateAllLegalMoves(team);
    return moves.empty() ? std::move(allMoves) : std::move(moves);
}
