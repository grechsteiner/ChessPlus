// LevelOneComputer.cc

#include "LevelOneComputer.h"

#include <memory>
#include <utility>
#include <vector>

#include "BoardMove.h"
#include "ChessBoard.h"
#include "Cloneable.h"
#include "ComputerPlayer.h"
#include "Constants.h"


/*
 * Basic ctor
 */
LevelOneComputer::LevelOneComputer(Team team) : 
    Cloneable<ComputerPlayer, LevelOneComputer>(team) { }

/*
 * Copy ctor
 */
LevelOneComputer::LevelOneComputer(LevelOneComputer const &other) :
    Cloneable<ComputerPlayer, LevelOneComputer>(other) { }

/*
 * Move ctor
 */
LevelOneComputer::LevelOneComputer(LevelOneComputer &&other) noexcept :
    Cloneable<ComputerPlayer, LevelOneComputer>(std::move(other)) { }

/*
 * Copy assignment
 */
LevelOneComputer& LevelOneComputer::operator=(LevelOneComputer &other) {
    if (this != &other) {
        ComputerPlayer::operator=(other);
    }
    return *this;
}

/*
 * Move assignment
 */
LevelOneComputer& LevelOneComputer::operator=(LevelOneComputer &&other) noexcept {
    if (this != &other) {
        ComputerPlayer::operator=(std::move(other));
    }
    return *this;
}

/* 
 * Generate a move
 * Pick a random move
 */
std::unique_ptr<BoardMove> LevelOneComputer::generateMoveImpl(std::unique_ptr<ChessBoard> const &chessBoard) const {
    std::vector<std::unique_ptr<BoardMove>> allLegalMoves = chessBoard->generateAllLegalMoves(team);
    shuffle(allLegalMoves);

    return allLegalMoves.front()->clone();
}
