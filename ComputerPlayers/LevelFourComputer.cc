// LevelFourComputer.cc

#include "LevelFourComputer.h"

#include <memory>
#include <utility>
#include <vector>

#include "BoardMove.h"
#include "Cloneable.h"
#include "ComputerPlayer.h"
#include "Constants.h"


// Basic ctor
LevelFourComputer::LevelFourComputer(Team team) : 
    Cloneable<ComputerPlayer, LevelFourComputer>(team) { }

// Copy ctor
LevelFourComputer::LevelFourComputer(LevelFourComputer const &other) :
    Cloneable<ComputerPlayer, LevelFourComputer>(other) { }

// Move ctor
LevelFourComputer::LevelFourComputer(LevelFourComputer &&other) noexcept :
    Cloneable<ComputerPlayer, LevelFourComputer>(std::move(other)) { }

// Copy assignment
LevelFourComputer& LevelFourComputer::operator=(LevelFourComputer &other) {
    if (this != &other) {
        ComputerPlayer::operator=(other);
    }
    return *this;
}

// Move assignment
LevelFourComputer& LevelFourComputer::operator=(LevelFourComputer &&other) noexcept {
    if (this != &other) {
        ComputerPlayer::operator=(std::move(other));
    }
    return *this;
}

/* 
 * Generate a move
 * 1) Game winning move
 * 2) Capturing, capture avoiding, and check applying move
 * 3) Capturing and capture avoiding move
 * 4) Capturing avoiding move
 * 5) Random move
 */
std::unique_ptr<BoardMove> LevelFourComputer::generateMoveImpl(std::unique_ptr<ChessBoard> const &chessBoard) const {
    // All moves
    std::vector<std::unique_ptr<BoardMove>> winningMoves = chessBoard->generateWinningMoves(team);
    if (!winningMoves.empty()) {
        return winningMoves.front()->clone();
    }

    // Capturing, capture avoiding, and check applying moves
    std::vector<std::unique_ptr<BoardMove>> capturingAndCaptureAvoidingAndCheckApplyingMoves;
    std::vector<std::unique_ptr<BoardMove>> capturingMoves = chessBoard->generateCapturingMoves(team);
    std::vector<std::unique_ptr<BoardMove>> captureAvoidingMoves = chessBoard->generateCaptureAvoidingMoves(team);
    std::vector<std::unique_ptr<BoardMove>> checkApplyingMoves = chessBoard->generateCheckApplyingMoves(team);
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

    // Capturing and capture avoiding moves
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

    // Capture avoiding moves
    if (!captureAvoidingMoves.empty()) {
        shuffle(captureAvoidingMoves);
        return captureAvoidingMoves.front()->clone();
    }

    // All moves
    std::vector<std::unique_ptr<BoardMove>> allLegalMoves = chessBoard->generateAllLegalMoves(team);
    shuffle(allLegalMoves);
    
    return allLegalMoves.front()->clone();
}
