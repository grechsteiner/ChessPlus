// BasicComputerPlayer.h

#include <vector>

#include "BasicComputerPlayer.h"
#include "Board.h"
#include "Move.h"
#include "MoveShuffler.h"

BasicComputerPlayer::BasicComputerPlayer() : ComputerPlayer() {}

Move BasicComputerPlayer::getMoveImplementation(Board &board, Color color) const {
    std::vector<Move> possibleMoves = getPossibleMoves(board, color);
    MoveShuffler::shuffle(possibleMoves);
    return possibleMoves[0];
}
