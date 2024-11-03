// LevelOneComputer.cc

#include <vector>
#include <cassert>

#include "Constants.h"
#include "LevelOneComputer.h"


// Basic ctor
LevelOneComputer::LevelOneComputer(ChessBoard const &chessBoard, Team team) : 
    Cloneable<ComputerPlayer, LevelOneComputer>(chessBoard, team) {}

// Copy ctor
LevelOneComputer::LevelOneComputer(LevelOneComputer const &other) :
    Cloneable<ComputerPlayer, LevelOneComputer>(other) {}

// Move ctor
LevelOneComputer::LevelOneComputer(LevelOneComputer &&other) noexcept :
    Cloneable<ComputerPlayer, LevelOneComputer>(std::move(other)) {}

std::unique_ptr<BoardMove> LevelOneComputer::generateMoveImpl() const {
    std::vector<std::unique_ptr<BoardMove>> allLegalMoves = chessBoard.generateAllLegalMoves(team);
    shuffle(allLegalMoves);
    return allLegalMoves.front()->clone();
}
