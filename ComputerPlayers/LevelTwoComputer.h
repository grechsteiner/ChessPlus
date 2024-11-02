// LevelTwoComputer.h

#ifndef LevelTwoComputer_h
#define LevelTwoComputer_h

#include <vector>

#include "BasicComputerPlayer.h"
#include "OldBoardMove.h"

class LevelTwoComputer : public BasicComputerPlayer {
private:
    std::vector<OldBoardMove> getPossibleMoves(ChessBoard const &chessBoard, Team team) const override;
public:
    LevelTwoComputer();
};

#endif /* LevelTwoComputer_h */
