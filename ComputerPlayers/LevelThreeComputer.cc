// LevelThreeComputer.cc

#include <vector>
#include <cassert>

#include "Constants.h"
#include "LevelThreeComputer.h"


// Basic ctor
LevelThreeComputer::LevelThreeComputer(ChessBoard const &chessBoard, Team team) : 
    Cloneable<ComputerPlayer, LevelThreeComputer>(chessBoard, team) {}

// Copy ctor
LevelThreeComputer::LevelThreeComputer(LevelThreeComputer const &other) :
    Cloneable<ComputerPlayer, LevelThreeComputer>(other) {}

// Move ctor
LevelThreeComputer::LevelThreeComputer(LevelThreeComputer &&other) noexcept :
    Cloneable<ComputerPlayer, LevelThreeComputer>(std::move(other)) {}

std::unique_ptr<BoardMove> LevelThreeComputer::generateMoveImpl() const {
    std::vector<std::unique_ptr<BoardMove>> winningMoves = chessBoard.generateWinningMoves(team);
    if (!winningMoves.empty()) {
        return winningMoves.front()->clone();
    }

    std::vector<std::unique_ptr<BoardMove>> capturingAndCaptureAvoidingMoves;
    std::vector<std::unique_ptr<BoardMove>> capturingMoves = chessBoard.generateCapturingMoves(team);
    std::vector<std::unique_ptr<BoardMove>> captureAvoidingMoves = chessBoard.generateCaptureAvoidingMoves(team);
    for (std::unique_ptr<BoardMove> const &capturingMove : capturingMoves) {
        for (std::unique_ptr<BoardMove> const &captureAvoidingMove : captureAvoidingMoves) {
            if (*capturingMove == *captureAvoidingMove) {
                capturingAndCaptureAvoidingMoves.emplace_back(capturingMove->clone());
                break;
            }
        }
    }
    if (!capturingAndCaptureAvoidingMoves.empty()) {
        shuffle(capturingAndCaptureAvoidingMoves);
        return capturingAndCaptureAvoidingMoves.front()->clone();
    }

    if (!captureAvoidingMoves.empty()) {
        shuffle(captureAvoidingMoves);
        return captureAvoidingMoves.front()->clone();
    }

    std::vector<std::unique_ptr<BoardMove>> allLegalMoves = chessBoard.generateAllLegalMoves(team);
    shuffle(allLegalMoves);
    return allLegalMoves.front()->clone();
}
