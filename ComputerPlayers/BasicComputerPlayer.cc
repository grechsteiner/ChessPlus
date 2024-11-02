// BasicComputerPlayer.h

#include <vector>

#include "BasicComputerPlayer.h"
#include "ChessBoardImpl.h"

#include "MoveShuffler.h"

BasicComputerPlayer::BasicComputerPlayer() : ComputerPlayer() {}

BoardMove BasicComputerPlayer::getMoveImpl(IChessBoard const &chessBoard, Team team) const {
    std::vector<BoardMove> possibleMoves = getPossibleMoves(chessBoard, team);
    MoveShuffler::shuffle(possibleMoves);
    return possibleMoves[0];
}
