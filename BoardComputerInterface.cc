// ChessBoard.cc

#include <vector>

#include "ChessBoard.h"
#include "FullMove.h"
#include "Constants.h"
#include "Piece.h"


std::vector<FullMove> ChessBoard::getLegalMoves(Color color) const { return getLegalMovesImpl(color); }
std::vector<FullMove> ChessBoard::getCapturingMoves(Color color) const { return getCapturingMovesImpl(color); }
std::vector<FullMove> ChessBoard::getCheckApplyingMoves(Color color) const { return getCheckApplyingMoves(color); }
std::vector<FullMove> ChessBoard::getCaptureAvoidingMoves(Color color) const { return getCaptureAvoidingMovesImpl(color); }

Color ChessBoard::getColorOne() const { return getColorOneImpl(); }
Color ChessBoard::getColorTwo() const { return getColorTwoImpl(); }
Color ChessBoard::oppositeColor(Color color) const { return oppositeColorImpl(color); }

void ChessBoard::makeMove(FullMove const &move) { makeMoveImpl(move); }
bool ChessBoard::undoMove() { return undoMoveImpl(); }

Piece const& ChessBoard::getPieceAt(int row, int col) const { return getPieceAtImpl(row, col); }
bool ChessBoard::isInStaleMate(Color color) const { return isInStaleMateImpl(color); }
int ChessBoard::getAlphaBetaBoardScore(Color color) const { return getAlphaBetaBoardScoreImpl(color); }
