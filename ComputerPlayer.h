// ComputerPlayer.h

#ifndef ComputerPlayer_h
#define ComputerPlayer_h

#include "Constants.h"
#include "ChessBoard.h"
#include "BoardMove.h"
#include "IChessBoard.h"

class ComputerPlayer {

private:
    virtual BoardMove getMoveImplementation(IChessBoard &chessBoard, Team team) const = 0;
public:
    BoardMove getMove(IChessBoard &chessBoard, Team team) const;
    ComputerPlayer();
    virtual ~ComputerPlayer() = default;
};


#endif /* ComputerPlayer_h */
