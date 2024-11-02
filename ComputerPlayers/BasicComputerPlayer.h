// BasicComputerPlayer.h

#ifndef BasicComputerPlayer_h
#define BasicComputerPlayer_h

#include <vector>

#include "Constants.h"
#include "ChessBoardImpl.h"
#include "OldBoardMove.h"
#include "ComputerPlayer.h"

class BasicComputerPlayer : public ComputerPlayer {
private:
    OldBoardMove getMoveImpl(ChessBoard const &chessBoard, Team team) const override;
    virtual std::vector<OldBoardMove> getPossibleMoves(ChessBoard const &chessBoard, Team team) const = 0;
public:
    BasicComputerPlayer();
    virtual ~BasicComputerPlayer() = default;
};


#endif /* BasicComputerPlayer_h */
