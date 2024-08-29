// ComputerPlayer.cc

#include "Constants.h"
#include "ComputerPlayer.h"
#include "BoardMove.h"
#include "Board.h"
#include "ChessBoard.h"

ComputerPlayer::ComputerPlayer() {}

BoardMove ComputerPlayer::getMove(ChessBoard &board, Color color) const {
    return getMoveImplementation(board, color);
}
