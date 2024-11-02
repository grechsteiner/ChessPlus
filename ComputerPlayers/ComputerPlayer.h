// ComputerPlayer.h

#ifndef ComputerPlayer_h
#define ComputerPlayer_h

#include <memory>

#include "Constants.h"
#include "ChessBoardImpl.h"
#include "OldBoardMove.h"
#include "ChessBoard.h"

class ComputerPlayer {

private:
    virtual OldBoardMove getMoveImpl(ChessBoard const &chessBoard, Team team) const = 0;
public:
    OldBoardMove getMove(ChessBoard const &chessBoard, Team team) const;
    ComputerPlayer();
    virtual ~ComputerPlayer() = default;
};


#endif /* ComputerPlayer_h */
