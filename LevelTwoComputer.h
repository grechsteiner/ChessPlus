// LevelTwoComputer.h

#ifndef LevelTwoComputer_h
#define LevelTwoComputer_h

#include <vector>

#include "BasicComputerPlayer.h"
#include "FullMove.h"

class LevelTwoComputer : public BasicComputerPlayer {
private:
    std::vector<FullMove> getPossibleMoves(ChessBoard &board, Color color) const override;
public:
    LevelTwoComputer();
};

#endif /* LevelTwoComputer_h */
