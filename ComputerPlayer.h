// ComputerPlayer.h

#ifndef ComputerPlayer_h
#define ComputerPlayer_h

#include "Constants.h"
#include "Board.h"
#include "FullMove.h"


class ComputerPlayer {

private:
    virtual FullMove getMoveImplementation(Board &board, Color color) const = 0;
public:
    FullMove getMove(Board &board, Color color) const;
    ComputerPlayer();
    virtual ~ComputerPlayer() = default;
};


#endif /* ComputerPlayer_h */
