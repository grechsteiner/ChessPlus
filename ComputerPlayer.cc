// ComputerPlayer.cc

#include "Constants.h"
#include "ComputerPlayer.h"
#include "FullMove.h"
#include "Board.h"
#include "ChessBoard.h"

ComputerPlayer::ComputerPlayer() {}

FullMove ComputerPlayer::getMove(ChessBoard &board, Color color) const {
    return getMoveImplementation(board, color);
}
