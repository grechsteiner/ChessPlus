// LevelOneComputer.cc

#include <vector>
#include <cassert>

#include "Constants.h"
#include "LevelOneComputer.h"


// Basic ctor
LevelOneComputer::LevelOneComputer(Team team) : 
    Cloneable<ComputerPlayer, LevelOneComputer>(team) {}

// Copy ctor
LevelOneComputer::LevelOneComputer(LevelOneComputer const &other) :
    Cloneable<ComputerPlayer, LevelOneComputer>(other) {}

// Move ctor
LevelOneComputer::LevelOneComputer(LevelOneComputer &&other) noexcept :
    Cloneable<ComputerPlayer, LevelOneComputer>(std::move(other)) {}

// Copy assignment
LevelOneComputer& LevelOneComputer::operator=(LevelOneComputer &other) {
    if (this != &other) {
        // Update if needed
        return *this;
    }
    return *this;
}

// Move assignment
LevelOneComputer& LevelOneComputer::operator=(LevelOneComputer &&other) noexcept {
    if (this != &other) {
        // Update if needed
        return *this;
    }
    return *this;
}

std::unique_ptr<BoardMove> LevelOneComputer::generateMoveImpl(std::unique_ptr<ChessBoard> const &chessBoard) const {
    std::vector<std::unique_ptr<BoardMove>> allLegalMoves = chessBoard->generateAllLegalMoves(team);
    shuffle(allLegalMoves);
    return allLegalMoves.front()->clone();
}
