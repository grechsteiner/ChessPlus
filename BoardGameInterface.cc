// BoardGameInterface.cc

#include "BoardGameInterface.h"

bool BoardGameInterface::isInStaleMate() const { return isInStaleMateImpl(); }
bool BoardGameInterface::hasGameFinished() const { return hasGameFinishedImpl(); }
bool BoardGameInterface::isBoardInValidState() const { return isBoardInValidStateImpl(); }

void BoardGameInterface::setPosition(int row, char col, Color pieceColor, PieceType pieceType, PieceDirection pieceDirection, bool hasMoved, int pieceScore) { setPositionImpl(row, col, pieceColor, pieceType, pieceDirection, hasMoved, pieceScore); }
bool BoardGameInterface::clearPosition(int row, char col) { return clearPositionImpl(row, col); }
void BoardGameInterface::clearBoard() { clearBoardImpl(); }

bool BoardGameInterface::isSquareOnBoard(int row, char col) const { return isSquareOnBoardImpl(row, col); }
bool BoardGameInterface::setBoardSize(int newNumRows, int newNumCols) { return setBoardSizeImpl(newNumRows, newNumCols); }
void BoardGameInterface::applyStandardSetup() { applyStandardSetupImpl(); }

std::unique_ptr<FullMove> BoardGameInterface::generateFullMove(UserEnteredMove const &userEnteredMove) const { return generateFullMoveImpl(userEnteredMove); }
void BoardGameInterface::makeMove(FullMove const &move) { makeMoveImpl(move); }
bool BoardGameInterface::undoMove() { return undoMoveImpl(); }
bool BoardGameInterface::redoMove() { return redoMoveImpl(); }
