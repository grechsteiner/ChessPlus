// BasicComputerPlayer.h

#include <vector>

#include "BasicComputerPlayer.h"
#include "ChessBoardImpl.h"

#include "MoveShuffler.h"

BasicComputerPlayer::BasicComputerPlayer() : ComputerPlayer() {}

OldBoardMove BasicComputerPlayer::getMoveImpl(ChessBoard const &chessBoard, Team team) const {
    std::vector<OldBoardMove> possibleMoves = getPossibleMoves(chessBoard, team);
    MoveShuffler::shuffle(possibleMoves);
    return possibleMoves[0];
}
