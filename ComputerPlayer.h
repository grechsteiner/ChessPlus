// ComputerPlayer.h

#ifndef ComputerPlayer_h
#define ComputerPlayer_h

#include "Constants.h"
#include "Board.h"
#include "BoardMove.h"
#include "ChessBoard.h"

class ComputerPlayer {

private:
    virtual BoardMove getMoveImplementation(ChessBoard &board, Team team) const = 0;
public:
    BoardMove getMove(ChessBoard &board, Team team) const;
    ComputerPlayer();
    virtual ~ComputerPlayer() = default;
};


#endif /* ComputerPlayer_h */
