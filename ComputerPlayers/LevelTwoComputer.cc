// LevelTwoComputer.cc

#include "LevelTwoComputer.h"

#include <memory>
#include <utility>
#include <vector>

#include "BoardMove.h"
#include "Cloneable.h"
#include "ComputerPlayer.h"
#include "Constants.h"


// Basic ctor
LevelTwoComputer::LevelTwoComputer(Team team) : 
    Cloneable<ComputerPlayer, LevelTwoComputer>(team) { }

// Copy ctor
LevelTwoComputer::LevelTwoComputer(LevelTwoComputer const &other) :
    Cloneable<ComputerPlayer, LevelTwoComputer>(other) { }

// Move ctor
LevelTwoComputer::LevelTwoComputer(LevelTwoComputer &&other) noexcept :
    Cloneable<ComputerPlayer, LevelTwoComputer>(std::move(other)) { }

// Copy assignment
LevelTwoComputer& LevelTwoComputer::operator=(LevelTwoComputer &other) {
    if (this != &other) {
        ComputerPlayer::operator=(other);
    }
    return *this;
}

// Move assignment
LevelTwoComputer& LevelTwoComputer::operator=(LevelTwoComputer &&other) noexcept {
    if (this != &other) {
        ComputerPlayer::operator=(std::move(other));
    }
    return *this;
}

/* 
 * Generate a move
 * 1) Game winning move
 * 2) Capturing and check applying move
 * 3) Capturing move
 * 4) Random move
 */
std::unique_ptr<BoardMove> LevelTwoComputer::generateMoveImpl(std::unique_ptr<ChessBoard> const &chessBoard) const {
    // Game winning moves
    std::vector<std::unique_ptr<BoardMove>> winningMoves = chessBoard->generateWinningMoves(team);
    if (!winningMoves.empty()) {
        return winningMoves.front()->clone();
    }

    // Capturing and check applying moves
    std::vector<std::unique_ptr<BoardMove>> capturingAndCheckApplyingMoves;
    std::vector<std::unique_ptr<BoardMove>> capturingMoves = chessBoard->generateCapturingMoves(team);
    std::vector<std::unique_ptr<BoardMove>> checkApplyingMoves = chessBoard->generateCheckApplyingMoves(team);
    for (std::unique_ptr<BoardMove> const &capturingMove : capturingMoves) {
        for (std::unique_ptr<BoardMove> const &checkApplyingMove : checkApplyingMoves) {
            if (*capturingMove == *checkApplyingMove) {
                capturingAndCheckApplyingMoves.emplace_back(capturingMove->clone());
                break;
            }
        }
    }
    if (!capturingAndCheckApplyingMoves.empty()) {
        shuffle(capturingAndCheckApplyingMoves);
        return capturingAndCheckApplyingMoves.front()->clone();
    }

    // Capturing moves
    if (!capturingMoves.empty()) {
        shuffle(capturingMoves);
        return capturingMoves.front()->clone();
    }

    // All moves
    std::vector<std::unique_ptr<BoardMove>> allLegalMoves = chessBoard->generateAllLegalMoves(team);
    shuffle(allLegalMoves);

    return allLegalMoves.front()->clone();
}
