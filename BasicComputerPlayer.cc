// BasicComputerPlayer.h

#include <vector>

#include "BasicComputerPlayer.h"
#include "Board.h"
#include "Move.h"
#include "MoveShuffler.h"

BasicComputerPlayer::BasicComputerPlayer() : ComputerPlayer() {}

FullMove BasicComputerPlayer::getMoveImplementation(Board &board, Color color) const {
    std::vector<FullMove> possibleMoves = getPossibleMoves(board, color);
    MoveShuffler::shuffle(possibleMoves);
    return possibleMoves[0];
}
