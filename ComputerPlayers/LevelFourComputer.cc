// LevelFourComputer.cc

#include <vector>
#include <cassert>

#include "Constants.h"
#include "LevelFourComputer.h"


// Basic ctor
LevelFourComputer::LevelFourComputer(ChessBoard const &chessBoard, Team team) : 
    Cloneable<ComputerPlayer, LevelFourComputer>(chessBoard, team) {}

// Copy ctor
LevelFourComputer::LevelFourComputer(LevelFourComputer const &other) :
    Cloneable<ComputerPlayer, LevelFourComputer>(other) {}

// Move ctor
LevelFourComputer::LevelFourComputer(LevelFourComputer &&other) noexcept :
    Cloneable<ComputerPlayer, LevelFourComputer>(std::move(other)) {}

std::unique_ptr<BoardMove> LevelFourComputer::generateMoveImpl() const {
    std::vector<std::unique_ptr<BoardMove>> winningMoves = chessBoard.generateWinningMoves(team);
    if (!winningMoves.empty()) {
        return winningMoves.front()->clone();
    }

    std::vector<std::unique_ptr<BoardMove>> capturingAndCaptureAvoidingAndCheckApplyingMoves;
    std::vector<std::unique_ptr<BoardMove>> capturingMoves = chessBoard.generateCapturingMoves(team);
    std::vector<std::unique_ptr<BoardMove>> captureAvoidingMoves = chessBoard.generateCaptureAvoidingMoves(team);
    std::vector<std::unique_ptr<BoardMove>> checkApplyingMoves = chessBoard.generateCheckApplyingMoves(team);
    for (std::unique_ptr<BoardMove> const &capturingMove : capturingMoves) {
        bool isCaptureAvoidingMove = false;
        bool isCheckApplyingMove = false;

        for (std::unique_ptr<BoardMove> const &captureAvoidingMove : captureAvoidingMoves) {
            if (*capturingMove == *captureAvoidingMove) {
                isCaptureAvoidingMove = true;
                break;
            }
        }

        if (isCaptureAvoidingMove) {
            for (std::unique_ptr<BoardMove> const &checkApplyingMove : checkApplyingMoves) {
                if (*capturingMove == *checkApplyingMove) {
                    isCheckApplyingMove = true;
                    break;
                }
            }
        }
        
        if (isCaptureAvoidingMove & isCheckApplyingMove) {
            capturingAndCaptureAvoidingAndCheckApplyingMoves.emplace_back(capturingMove->clone());
        }
    }
    if (!capturingAndCaptureAvoidingAndCheckApplyingMoves.empty()) {
        shuffle(capturingAndCaptureAvoidingAndCheckApplyingMoves);
        return capturingAndCaptureAvoidingAndCheckApplyingMoves.front()->clone();
    }

    std::vector<std::unique_ptr<BoardMove>> capturingAndCaptureAvoidingMoves;
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
