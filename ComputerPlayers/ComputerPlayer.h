// ComputerPlayer.h

#ifndef ComputerPlayer_h
#define ComputerPlayer_h

#include <memory>

#include "Constants.h"
#include "ChessBoardImpl.h"
#include "BoardMove.h"
#include "ChessBoard.h"

class ComputerPlayer {

private:
    virtual BoardMove getMoveImpl(ChessBoard const &chessBoard, Team team) const = 0;
public:
    BoardMove getMove(ChessBoard const &chessBoard, Team team) const;
    ComputerPlayer();
    virtual ~ComputerPlayer() = default;
};


#endif /* ComputerPlayer_h */
