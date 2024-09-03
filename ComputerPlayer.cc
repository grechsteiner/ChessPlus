// ComputerPlayer.cc

#include "Constants.h"
#include "ComputerPlayer.h"
#include "BoardMove.h"
#include "IChessBoard.h"

ComputerPlayer::ComputerPlayer() {}

BoardMove ComputerPlayer::getMove(IChessBoard const &chessBoard, Team team) const {
    return getMoveImpl(chessBoard, team);
}
