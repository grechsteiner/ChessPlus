// ComputerPlayer.cc

#include "Constants.h"
#include "ComputerPlayer.h"
#include "OldBoardMove.h"
#include "ChessBoard.h"

ComputerPlayer::ComputerPlayer() {}

OldBoardMove ComputerPlayer::getMove(ChessBoard const &chessBoard, Team team) const {
    return getMoveImpl(chessBoard, team);
}
