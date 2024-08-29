// ComputerPlayer.h

#ifndef ComputerPlayer_h
#define ComputerPlayer_h

#include "Constants.h"
#include "Board.h"
#include "FullMove.h"
#include "ChessBoard.h"

class ComputerPlayer {

private:
    virtual FullMove getMoveImplementation(ChessBoard &board, Color color) const = 0;
public:
    FullMove getMove(ChessBoard &board, Color color) const;
    ComputerPlayer();
    virtual ~ComputerPlayer() = default;
};


#endif /* ComputerPlayer_h */
