// LevelThreeComputer.cc

#include "LevelThreeComputer.h"

#include <memory>
#include <vector>

#include "BoardMove.h"
#include "Cloneable.h"
#include "ComputerPlayer.h"
#include "Constants.h"


// Basic ctor
LevelThreeComputer::LevelThreeComputer(Team team) : 
    Cloneable<ComputerPlayer, LevelThreeComputer>(team) { }

// Copy ctor
LevelThreeComputer::LevelThreeComputer(LevelThreeComputer const &other) :
    Cloneable<ComputerPlayer, LevelThreeComputer>(other) { }

// Move ctor
LevelThreeComputer::LevelThreeComputer(LevelThreeComputer &&other) noexcept :
    Cloneable<ComputerPlayer, LevelThreeComputer>(std::move(other)) { }

// Copy assignment
LevelThreeComputer& LevelThreeComputer::operator=(LevelThreeComputer &other) {
    if (this != &other) {
        ComputerPlayer::operator=(other);
    }
    return *this;
}

// Move assignment
LevelThreeComputer& LevelThreeComputer::operator=(LevelThreeComputer &&other) noexcept {
    if (this != &other) {
        ComputerPlayer::operator=(std::move(other));
    }
    return *this;
}

/* 
 * Generate a move
 * 1) Game winning move
 * 2) Capturing and capture avoiding move
 * 3) Capturing avoiding move
 * 4) Random move
 */
std::unique_ptr<BoardMove> LevelThreeComputer::generateMoveImpl(std::unique_ptr<ChessBoard> const &chessBoard) const {
    // Game winning moves
    std::vector<std::unique_ptr<BoardMove>> winningMoves = chessBoard->generateWinningMoves(team);
    if (!winningMoves.empty()) {
        return winningMoves.front()->clone();
    }

    // Capturing and capture avoiding moves
    std::vector<std::unique_ptr<BoardMove>> capturingAndCaptureAvoidingMoves;
    std::vector<std::unique_ptr<BoardMove>> capturingMoves = chessBoard->generateCapturingMoves(team);
    std::vector<std::unique_ptr<BoardMove>> captureAvoidingMoves = chessBoard->generateCaptureAvoidingMoves(team);
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
