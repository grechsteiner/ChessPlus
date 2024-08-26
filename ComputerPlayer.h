// ComputerPlayer.h

#ifndef ComputerPlayer_h
#define ComputerPlayer_h

#include "Constants.h"
#include "Board.h"
#include "Move.h"


class ComputerPlayer {

private:
    virtual Move getMoveImplementation(Board &board, Color color) const = 0;
public:
    Move getMove(Board &board, Color color) const;
    ComputerPlayer();
    virtual ~ComputerPlayer() = default;
};


#endif /* ComputerPlayer_h */
