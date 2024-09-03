// LevelOneComputer.h

#ifndef LevelOneComputer_h
#define LevelOneComputer_h

#include <vector>

#include "BoardMove.h"
#include "BasicComputerPlayer.h"

class LevelOneComputer : public BasicComputerPlayer {
private:
    std::vector<BoardMove> getPossibleMoves(IChessBoard &chessBoard, Team team) const override;
public:
    LevelOneComputer();
};

#endif /* LevelOneComputer_h */
