// BasicComputerPlayer.h

#ifndef BasicComputerPlayer_h
#define BasicComputerPlayer_h

#include <vector>

#include "Constants.h"
#include "ChessBoard.h"
#include "BoardMove.h"
#include "ComputerPlayer.h"

class BasicComputerPlayer : public ComputerPlayer {
private:
    BoardMove getMoveImpl(IChessBoard const &chessBoard, Team team) const override;
    virtual std::vector<BoardMove> getPossibleMoves(IChessBoard const &chessBoard, Team team) const = 0;
public:
    BasicComputerPlayer();
    virtual ~BasicComputerPlayer() = default;
};


#endif /* BasicComputerPlayer_h */
