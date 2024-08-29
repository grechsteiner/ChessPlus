// ChessBoard.cc

#include "ChessBoard.h"
#include "Constants.h"
#include "FullMove.h"


Piece const& ChessBoard::getPieceAt(int row, int col) const { return getPieceAtImpl(row, col); }
void ChessBoard::setPosition(int row, int col, Color pieceColor, PieceType pieceType, PieceDirection pieceDirection, bool hasMoved, int pieceScore) { setPositionImpl(row, col, pieceColor, pieceType, pieceDirection, hasMoved, pieceScore); }
void ChessBoard::clearPosition(int row, int col) { clearPositionImpl(row, col); }
void ChessBoard::swapPositions(int rowOne, int colOne, int rowTwo, int colTwo) { swapPositionsImpl(rowOne, colOne, rowTwo, colTwo); }
void ChessBoard::setHasMoved(int row, int col, bool hasMoved) { setHasMovedImpl(row, col, hasMoved); }
