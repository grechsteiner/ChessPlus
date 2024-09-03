// BasicComputerPlayer.h

#include <vector>

#include "BasicComputerPlayer.h"
#include "ChessBoard.h"

#include "MoveShuffler.h"

BasicComputerPlayer::BasicComputerPlayer() : ComputerPlayer() {}

BoardMove BasicComputerPlayer::getMoveImplementation(IChessBoard const &chessBoard, Team team) const {
    std::vector<BoardMove> possibleMoves = getPossibleMoves(chessBoard, team);
    MoveShuffler::shuffle(possibleMoves);
    return possibleMoves[0];
}
