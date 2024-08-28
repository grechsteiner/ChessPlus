// ComputerPlayer.cc

#include "Constants.h"
#include "ComputerPlayer.h"
#include "FullMove.h"
#include "Board.h"

ComputerPlayer::ComputerPlayer() {}

FullMove ComputerPlayer::getMove(Board &board, Color color) const {
    return getMoveImplementation(board, color);
}
