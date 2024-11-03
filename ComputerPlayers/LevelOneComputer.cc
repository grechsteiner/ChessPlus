// LevelOneComputer.cc

#include <vector>
#include <cassert>

#include "Constants.h"
#include "LevelOneComputer.h"
#include "ChessBoardImpl.h"


LevelOneComputer::LevelOneComputer() : BasicComputerPlayer() {}

std::vector<std::unique_ptr<BoardMove>> LevelOneComputer::getPossibleMoves(ChessBoard const &chessBoard, Team team) const {
    std::vector<std::unique_ptr<BoardMove>> possibleMoves = chessBoard.generateAllLegalMoves(team);
    return possibleMoves;
}
