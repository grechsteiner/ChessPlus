// LevelThreeComputer.h

#ifndef LevelThreeComputer_h
#define LevelThreeComputer_h

#include <vector>

#include "BasicComputerPlayer.h"
#include "BoardMove.h"

class LevelThreeComputer : public BasicComputerPlayer {
private:
    std::vector<std::unique_ptr<BoardMove>> getPossibleMoves(ChessBoard const &chessBoard, Team team) const override;
public:
    LevelThreeComputer();
};

#endif /* LevelThreeComputer_h */
