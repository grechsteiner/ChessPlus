// LevelOneComputer.h

#ifndef LevelOneComputer_h
#define LevelOneComputer_h

#include <vector>

#include "OldBoardMove.h"
#include "BasicComputerPlayer.h"

class LevelOneComputer : public BasicComputerPlayer {
private:
    std::vector<OldBoardMove> getPossibleMoves(ChessBoard const &chessBoard, Team team) const override;
public:
    LevelOneComputer();
};

#endif /* LevelOneComputer_h */
