// ComputerPlayer.cc

#include "Constants.h"
#include "ComputerPlayer.h"
#include "BoardMove.h"
#include "Board.h"
#include "ChessBoard.h"

ComputerPlayer::ComputerPlayer() {}

BoardMove ComputerPlayer::getMove(ChessBoard &board, Team team) const {
    return getMoveImplementation(board, team);
}
