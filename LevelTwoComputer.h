// LevelTwoComputer.h

#ifndef LevelTwoComputer_h
#define LevelTwoComputer_h

#include <vector>

#include "BasicComputerPlayer.h"
#include "BoardMove.h"

class LevelTwoComputer : public BasicComputerPlayer {
private:
    std::vector<BoardMove> getPossibleMoves(ChessBoard &board, Team team) const override;
public:
    LevelTwoComputer();
};

#endif /* LevelTwoComputer_h */
