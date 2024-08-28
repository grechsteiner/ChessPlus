// ComputerPlayer.cc

#include "Constants.h"
#include "ComputerPlayer.h"
#include "FullMove.h"
#include "Board.h"
#include "BoardComputerInterface.h"

ComputerPlayer::ComputerPlayer() {}

FullMove ComputerPlayer::getMove(BoardComputerInterface &board, Color color) const {
    return getMoveImplementation(board, color);
}
