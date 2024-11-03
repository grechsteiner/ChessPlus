// ComputerPlayer.cc

#include "Constants.h"
#include "ComputerPlayer.h"
#include "BoardMove.h"
#include "ChessBoard.h"

ComputerPlayer::ComputerPlayer() {}

std::unique_ptr<BoardMove> ComputerPlayer::getMove(ChessBoard const &chessBoard, Team team) const {
    return getMoveImpl(chessBoard, team);
}
