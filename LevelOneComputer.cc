// LevelOneComputer.cc

#include <vector>
#include <cassert>

#include "Constants.h"
#include "LevelOneComputer.h"
#include "ChessBoard.h"


LevelOneComputer::LevelOneComputer() : BasicComputerPlayer() {}

std::vector<BoardMove> LevelOneComputer::getPossibleMoves(IChessBoard &chessBoard, Team team) const {
    std::vector<BoardMove> possibleMoves = chessBoard.generateAllLegalMoves(team);
    return possibleMoves;
}
