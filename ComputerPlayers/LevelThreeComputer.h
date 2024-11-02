// LevelThreeComputer.h

#ifndef LevelThreeComputer_h
#define LevelThreeComputer_h

#include <vector>

#include "BasicComputerPlayer.h"
#include "OldBoardMove.h"

class LevelThreeComputer : public BasicComputerPlayer {
private:
    std::vector<OldBoardMove> getPossibleMoves(ChessBoard const &chessBoard, Team team) const override;
public:
    LevelThreeComputer();
};

#endif /* LevelThreeComputer_h */
