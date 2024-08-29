// LevelOneComputer.h

#ifndef LevelOneComputer_h
#define LevelOneComputer_h

#include <vector>

#include "FullMove.h"
#include "BasicComputerPlayer.h"

class LevelOneComputer : public BasicComputerPlayer {
private:
    std::vector<BoardMove> getPossibleMoves(ChessBoard &board, Color color) const override;
public:
    LevelOneComputer();
};

#endif /* LevelOneComputer_h */
