// ChessBoard.cc

#include <vector>

#include "ChessBoard.h"
#include "Constants.h"
#include "BoardMove.h"
#include "PieceInfo.h"

class UserMove;


PieceInfo ChessBoard::getPieceInfoAt(BoardSquare const &boardSquare) const { return getPieceInfoAtImpl(boardSquare); }
std::vector<BoardSquare> ChessBoard::allBoardSquares() const { return allBoardSquaresImpl(); }

bool ChessBoard::isEmptySquareOnBoard(BoardSquare const &boardSquare) const { return isEmptySquareOnBoardImpl(boardSquare); }
bool ChessBoard::isOpposingTeamOnBoard(BoardSquare const &boardSquare, Team team) const { return isOpposingTeamOnBoardImpl(boardSquare, team); }
bool ChessBoard::isEmptySquareOrOpposingTeamOnBoard(BoardSquare const &boardSquare, Team team) const { return isEmptySquareOrOpposingTeamOnBoardImpl(boardSquare, team); }
bool ChessBoard::isSquareAttacked(BoardSquare const &boardSquare, Team team) const { return isSquareAttackedImpl(boardSquare, team); }

bool ChessBoard::isSquareOnBoard(BoardSquare const &boardSquare) const { return isSquareOnBoardImpl(boardSquare); }
void ChessBoard::setPosition(BoardSquare const &boardSquare, Team team, PieceType pieceType, PieceDirection pieceDirection, bool hasMoved, int pieceScore) {
    setPositionImpl(boardSquare, team, pieceType, pieceDirection, hasMoved, pieceScore);
}
bool ChessBoard::clearPosition(BoardSquare const &boardSquare) { return clearPositionImpl(boardSquare); }
void ChessBoard::clearBoard() { clearBoardImpl(); }
void ChessBoard::swapPositions(BoardSquare const &boardSquareOne, BoardSquare const &boardSquareTwo) { swapPositionsImpl(boardSquareOne, boardSquareTwo); }
void ChessBoard::setHasMoved(BoardSquare const &boardSquare, bool hasMoved) { setHasMovedImpl(boardSquare, hasMoved); }
bool ChessBoard::setBoardSize(int newNumRows, int newNumCols) { return setBoardSizeImpl(newNumRows, newNumCols); }
void ChessBoard::applyStandardSetup() { applyStandardSetupImpl(); }

std::vector<BoardMove> ChessBoard::getLegalMoves(Team team) const { return getLegalMovesImpl(team); }
std::vector<BoardMove> ChessBoard::getCapturingMoves(Team team) const { return getCapturingMovesImpl(team); }
std::vector<BoardMove> ChessBoard::getCheckApplyingMoves(Team team) const { return getCheckApplyingMovesImpl(team); }
std::vector<BoardMove> ChessBoard::getCaptureAvoidingMoves(Team team) const { return getCaptureAvoidingMovesImpl(team); }

Team ChessBoard::getTeamOne() const { return getTeamOneImpl(); }
Team ChessBoard::getTeamTwo() const { return getTeamTwoImpl(); }
Team ChessBoard::getOtherTeam(Team team) const { return getOtherTeamImpl(team); }

std::unique_ptr<BoardMove> ChessBoard::generateBoardMove(UserMove const &userMove) const { return generateBoardMoveImpl(userMove); }
BoardMove const& ChessBoard::getLastMadeMove() const { return getLastMadeMoveImpl(); }
std::vector<BoardMove> const& ChessBoard::getAllMadeMoves() const { return getAllMadeMovesImpl(); }
bool ChessBoard::hasMoveBeenMade() const { return hasMoveBeenMadeImpl(); }
void ChessBoard::makeMove(BoardMove const &move) { makeMoveImpl(move); }
bool ChessBoard::undoMove() { return undoMoveImpl(); }
bool ChessBoard::redoMove() { return redoMoveImpl(); }

int ChessBoard::getNumRows() const { return getNumRowsImpl(); }
int ChessBoard::getNumCols() const { return getNumColsImpl(); }

bool ChessBoard::isInCheck(Team team) const { return isInCheckImpl(team); }
bool ChessBoard::isInCheckMate(Team team) const { return isInCheckMateImpl(team); }
bool ChessBoard::isInStaleMate(Team team) const { return isInStaleMateImpl(team); }
bool ChessBoard::isInStaleMate() const { return isInStaleMateImpl(); }
bool ChessBoard::hasGameFinished() const { return hasGameFinishedImpl(); }
bool ChessBoard::isBoardInValidState() const { return isBoardInValidStateImpl(); }
