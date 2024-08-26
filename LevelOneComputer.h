// LevelOneComputer.h

#ifndef LevelOneComputer_h
#define LevelOneComputer_h

#include <vector>

#include "Move.h"
#include "BasicComputerPlayer.h"

class LevelOneComputer : public BasicComputerPlayer {
private:
    std::vector<Move> getPossibleMoves(Board &board, Color color) const override;
public:
    LevelOneComputer();
};

#endif /* LevelOneComputer_h */
