// ChessBoard.cc

#include <vector>

#include "ChessBoard.h"
#include "Constants.h"
#include "BoardMove.h"

class Piece;
class UserMove;


Piece const& ChessBoard::getPieceAt(int row, int col) const { return getPieceAtImpl(row, col); }

bool ChessBoard::isEmptySquareOnBoard(int row, int col) const { return isEmptySquareOnBoardImpl(row, col); }
bool ChessBoard::isOpposingColorOnBoard(int row, int col, Color color) const { return isOpposingColorOnBoardImpl(row, col, color); }
bool ChessBoard::isEmptySquareOrOpposingColorOnBoard(int row, int col, Color color) const { return isEmptySquareOrOpposingColorOnBoardImpl(row, col, color); }
bool ChessBoard::isSquareCheckAttacked(int attackedRow, int attackedCol, Color color) const { return isSquareCheckAttackedImpl(attackedRow, attackedCol, color); }

bool ChessBoard::isSquareOnCurrentBoard(UserSquare const &userSquare) const { return isSquareOnCurrentBoardImpl(userSquare); }
void ChessBoard::setPosition(UserSquare const &userSquare, Color pieceColor, PieceType pieceType, PieceDirection pieceDirection, bool hasMoved, int pieceScore) { 
    setPositionImpl(userSquare, pieceColor, pieceType, pieceDirection, hasMoved, pieceScore);
}
void ChessBoard::setPosition(int row, int col, Color pieceColor, PieceType pieceType, PieceDirection pieceDirection, bool hasMoved, int pieceScore) {
    setPositionImpl(row, col, pieceColor, pieceType, pieceDirection, hasMoved, pieceScore);
}
bool ChessBoard::clearPosition(UserSquare const &userSquare) { return clearPositionImpl(userSquare); }
bool ChessBoard::clearPosition(int row, int col) { clearPositionImpl(row, col); }
void ChessBoard::clearBoard() { clearBoardImpl(); }
void ChessBoard::swapPositions(int rowOne, int colOne, int rowTwo, int colTwo) { swapPositionsImpl(rowOne, colOne, rowTwo, colTwo); }
void ChessBoard::setHasMoved(int row, int col, bool hasMoved) { setHasMovedImpl(row, col, hasMoved); }
bool ChessBoard::setBoardSize(int newNumRows, int newNumCols) { return setBoardSizeImpl(newNumRows, newNumCols); }
void ChessBoard::applyStandardSetup() { applyStandardSetupImpl(); }

std::vector<BoardMove> ChessBoard::getLegalMoves(Color color) const { return getLegalMovesImpl(color); }
std::vector<BoardMove> ChessBoard::getCapturingMoves(Color color) const { return getCapturingMovesImpl(color); }
std::vector<BoardMove> ChessBoard::getCheckApplyingMoves(Color color) const { return getCheckApplyingMovesImpl(color); }
std::vector<BoardMove> ChessBoard::getCaptureAvoidingMoves(Color color) const { return getCaptureAvoidingMovesImpl(color); }

Color ChessBoard::getColorOne() const { return getColorOneImpl(); }
Color ChessBoard::getColorTwo() const { return getColorTwoImpl(); }
Color ChessBoard::oppositeColor(Color color) const { return oppositeColorImpl(color); }

std::unique_ptr<BoardMove> ChessBoard::generateBoardMove(UserMove const &userMove) const { return generateBoardMoveImpl(userMove); }
BoardMove const& ChessBoard::getLastMove() const { return getLastMoveImpl(); }
bool ChessBoard::hasMoveBeenMade() const { return hasMoveBeenMadeImpl(); }
void ChessBoard::makeMove(BoardMove const &move) { makeMoveImpl(move); }
bool ChessBoard::undoMove() { return undoMoveImpl(); }
bool ChessBoard::redoMove() { return redoMoveImpl(); }

int ChessBoard::getNumRows() const { return getNumRowsImpl(); }
int ChessBoard::getNumCols() const { return getNumColsImpl(); }

bool ChessBoard::isInCheck(Color color) const { return isInCheckImpl(color); }
bool ChessBoard::isInCheckMate(Color color) const { return isInCheckMateImpl(color); }
bool ChessBoard::isInStaleMate(Color color) const { return isInStaleMateImpl(color); }
bool ChessBoard::isInStaleMate() const { return isInStaleMateImpl(); }
bool ChessBoard::hasGameFinished() const { return hasGameFinishedImpl(); }
bool ChessBoard::isBoardInValidState() const { return isBoardInValidStateImpl(); }

int ChessBoard::getAlphaBetaBoardScore(Color color) const { return getAlphaBetaBoardScoreImpl(color); }
std::vector<std::pair<std::string, std::string>> ChessBoard::getMatchingOpenings() const { return getMatchingOpeningsImpl(); }
