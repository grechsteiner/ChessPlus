// ComputerPlayer.cc

#include "Constants.h"
#include "ComputerPlayer.h"
#include "Move.h"
#include "Board.h"

ComputerPlayer::ComputerPlayer() {}

Move ComputerPlayer::getMove(Board &board, Color color) const {
    return getMoveImplementation(board, color);
}
