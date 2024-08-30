// LevelThreeComputer.h

#ifndef LevelThreeComputer_h
#define LevelThreeComputer_h

#include <vector>

#include "BasicComputerPlayer.h"
#include "BoardMove.h"

class LevelThreeComputer : public BasicComputerPlayer {
private:
    std::vector<BoardMove> getPossibleMoves(ChessBoard &board, Team team) const override;
public:
    LevelThreeComputer();
};

#endif /* LevelThreeComputer_h */
