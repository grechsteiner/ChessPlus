// BasicComputerPlayer.h

#include <vector>

#include "BasicComputerPlayer.h"
#include "Board.h"

#include "MoveShuffler.h"

BasicComputerPlayer::BasicComputerPlayer() : ComputerPlayer() {}

BoardMove BasicComputerPlayer::getMoveImplementation(ChessBoard &board, Team team) const {
    std::vector<BoardMove> possibleMoves = getPossibleMoves(board, team);
    MoveShuffler::shuffle(possibleMoves);
    return possibleMoves[0];
}
