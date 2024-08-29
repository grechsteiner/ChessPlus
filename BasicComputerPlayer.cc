// BasicComputerPlayer.h

#include <vector>

#include "BasicComputerPlayer.h"
#include "Board.h"
#include "Move.h"
#include "MoveShuffler.h"

BasicComputerPlayer::BasicComputerPlayer() : ComputerPlayer() {}

BoardMove BasicComputerPlayer::getMoveImplementation(ChessBoard &board, Color color) const {
    std::vector<BoardMove> possibleMoves = getPossibleMoves(board, color);
    MoveShuffler::shuffle(possibleMoves);
    return possibleMoves[0];
}
