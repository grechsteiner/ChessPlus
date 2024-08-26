// LevelTwoComputer.h

#ifndef LevelTwoComputer_h
#define LevelTwoComputer_h

#include <vector>

#include "BasicComputerPlayer.h"
#include "Move.h"

class LevelTwoComputer : public BasicComputerPlayer {
private:
    std::vector<Move> getPossibleMoves(Board &board, Color color) const override;
public:
    LevelTwoComputer();
};

#endif /* LevelTwoComputer_h */
