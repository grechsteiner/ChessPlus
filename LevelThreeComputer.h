// LevelThreeComputer.h

#ifndef LevelThreeComputer_h
#define LevelThreeComputer_h

#include <vector>

#include "BasicComputerPlayer.h"
#include "FullMove.h"

class LevelThreeComputer : public BasicComputerPlayer {
private:
    std::vector<FullMove> getPossibleMoves(ChessBoard &board, Color color) const override;
public:
    LevelThreeComputer();
};

#endif /* LevelThreeComputer_h */
