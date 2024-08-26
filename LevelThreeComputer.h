// LevelThreeComputer.h

#ifndef LevelThreeComputer_h
#define LevelThreeComputer_h

#include <vector>

#include "BasicComputerPlayer.h"
#include "Move.h"

class LevelThreeComputer : public BasicComputerPlayer {
private:
    std::vector<Move> getPossibleMoves(Board &board, Color color) const override;
public:
    LevelThreeComputer();
};

#endif /* LevelThreeComputer_h */
