// BoardComputerInterface.cc

#include <vector>

#include "BoardComputerInterface.h"
#include "FullMove.h"
#include "Constants.h"
#include "Piece.h"


std::vector<FullMove> BoardComputerInterface::getLegalMoves(Color color) const { return getLegalMovesImpl(color); }
std::vector<FullMove> BoardComputerInterface::getCapturingMoves(Color color) const { return getCapturingMovesImpl(color); }
std::vector<FullMove> BoardComputerInterface::getCheckApplyingMoves(Color color) const { return getCheckApplyingMoves(color); }
std::vector<FullMove> BoardComputerInterface::getCaptureAvoidingMoves(Color color) const { return getCaptureAvoidingMovesImpl(color); }

Color BoardComputerInterface::getColorOne() const { return getColorOneImpl(); }
Color BoardComputerInterface::getColorTwo() const { return getColorTwoImpl(); }
Color BoardComputerInterface::oppositeColor(Color color) const { return oppositeColorImpl(color); }

void BoardComputerInterface::makeMove(FullMove const &move) { makeMoveImpl(move); }
bool BoardComputerInterface::undoMove() { return undoMoveImpl(); }

Piece const& BoardComputerInterface::getPieceAt(int row, int col) const { return getPieceAtImpl(row, col); }
bool BoardComputerInterface::isInStaleMate(Color color) const { return isInStaleMateImpl(color); }
int BoardComputerInterface::getAlphaBetaBoardScore(Color color) const { return getAlphaBetaBoardScoreImpl(color); }
