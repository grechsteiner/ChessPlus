// BasicComputerPlayer.h

#include <vector>

#include "BasicComputerPlayer.h"
#include "ChessBoardImpl.h"

#include "MoveShuffler.h"

BasicComputerPlayer::BasicComputerPlayer() : ComputerPlayer() {}

std::unique_ptr<BoardMove> BasicComputerPlayer::getMoveImpl(ChessBoard const &chessBoard, Team team) const {
    std::vector<std::unique_ptr<BoardMove>> possibleMoves = getPossibleMoves(chessBoard, team);
    MoveShuffler::shuffle(possibleMoves);
    return possibleMoves[0]->clone();
}
