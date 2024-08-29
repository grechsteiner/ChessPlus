// ChessBoard.cc

#include <memory>

#include "ChessBoard.h"
#include "Constants.h"
#include "Piece.h"
#include "FullMove.h"


Piece const& ChessBoard::getPieceAt(int row, int col) const { return getPieceAtImpl(row, col); }
bool ChessBoard::isEmptySquareOnBoard(int row, int col) const { return isEmptySquareOnBoardImplementation(row, col); }
bool ChessBoard::isOpposingColorOnBoard(int row, int col, Color color) const { return isOpposingColorOnBoardImplementation(row, col, color); }
bool ChessBoard::isEmptySquareOrOpposingColorOnBoard(int row, int col, Color color) const { return isEmptySquareOrOpposingColorOnBoardImplementation(row, col, color); }
bool ChessBoard::isSquareCheckAttacked(int attackedRow, int attackedCol, Color color) const { return isSquareCheckAttackedImplementation(attackedRow, attackedCol, color); }

bool ChessBoard::hasMoveBeenMade() const { return hasMoveBeenMadeImplementation(); }
BoardMove const& ChessBoard::getLastMove() const { return getLastMoveImplementation(); }

int ChessBoard::getNumRows() const { return getNumRowsImplementation(); }
int ChessBoard::getNumCols() const { return getNumColsImplementation(); }
