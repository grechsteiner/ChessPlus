// ChessBoard.cc

#include "ChessBoard.h"

bool ChessBoard::isInStaleMate() const { return isInStaleMateImpl(); }
bool ChessBoard::hasGameFinished() const { return hasGameFinishedImpl(); }
bool ChessBoard::isBoardInValidState() const { return isBoardInValidStateImpl(); }

void ChessBoard::setPosition(int row, char col, Color pieceColor, PieceType pieceType, PieceDirection pieceDirection, bool hasMoved, int pieceScore) { setPositionImpl(row, col, pieceColor, pieceType, pieceDirection, hasMoved, pieceScore); }
bool ChessBoard::clearPosition(int row, char col) { return clearPositionImpl(row, col); }
void ChessBoard::clearBoard() { clearBoardImpl(); }

bool ChessBoard::isSquareOnBoard(int row, char col) const { return isSquareOnBoardImpl(row, col); }
bool ChessBoard::setBoardSize(int newNumRows, int newNumCols) { return setBoardSizeImpl(newNumRows, newNumCols); }
void ChessBoard::applyStandardSetup() { applyStandardSetupImpl(); }

std::unique_ptr<FullMove> ChessBoard::generateFullMove(UserEnteredMove const &userEnteredMove) const { return generateFullMoveImpl(userEnteredMove); }
void ChessBoard::makeMove(FullMove const &move) { makeMoveImpl(move); }
bool ChessBoard::undoMove() { return undoMoveImpl(); }
bool ChessBoard::redoMove() { return redoMoveImpl(); }
