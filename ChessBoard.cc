// ChessBoard.cc

#include <vector>

#include "ChessBoard.h"
#include "Constants.h"
#include "BoardMove.h"
#include "PieceInfo.h"

class UserMove;


PieceInfo ChessBoard::getPieceInfoAt(BoardSquare const &boardSquare) const { return getPieceInfoAtImpl(boardSquare); }
std::vector<BoardSquare> ChessBoard::allBoardSquares() const { return allBoardSquaresImpl(); }

bool ChessBoard::isSquareOnBoard(BoardSquare const &boardSquare) const { return isSquareOnBoardImpl(boardSquare); }
bool ChessBoard::isSquareEmpty(BoardSquare const &boardSquare) const { return isSquareEmptyImpl(boardSquare); }
bool ChessBoard::isSquareOwnTeam(BoardSquare const &boardSquare, Team team) const { return isSquareOwnTeamImpl(boardSquare, team); }
bool ChessBoard::isSquareOtherTeam(BoardSquare const &boardSquare, Team team) const { return isSquareOtherTeamImpl(boardSquare, team); }
bool ChessBoard::isSquareAttacked(BoardSquare const &boardSquare, Team team) const { return isSquareAttackedImpl(boardSquare, team); }

void ChessBoard::setPosition(BoardSquare const &boardSquare, Team team, PieceType pieceType, PieceDirection pieceDirection, bool hasMoved, std::optional<int> pieceScore) { setPositionImpl(boardSquare, team, pieceType, pieceDirection, hasMoved, pieceScore); }
bool ChessBoard::clearPosition(BoardSquare const &boardSquare) { return clearPositionImpl(boardSquare); }
void ChessBoard::clearBoard() { clearBoardImpl(); }
bool ChessBoard::setBoardSize(int newNumRows, int newNumCols) { return setBoardSizeImpl(newNumRows, newNumCols); }

std::vector<BoardMove> ChessBoard::getLegalMovesAtSquare(BoardSquare const &boardSquare) const { return getLegalMovesAtSquareImpl(boardSquare); }
std::vector<BoardMove> ChessBoard::getLegalMoves(Team team) const { return getLegalMovesImpl(team); }
std::vector<BoardMove> ChessBoard::getCapturingMoves(Team team) const { return getCapturingMovesImpl(team); }
std::vector<BoardMove> ChessBoard::getCheckApplyingMoves(Team team) const { return getCheckApplyingMovesImpl(team); }
std::vector<BoardMove> ChessBoard::getCaptureAvoidingMoves(Team team) const { return getCaptureAvoidingMovesImpl(team); }

Team ChessBoard::getTeamOne() const { return getTeamOneImpl(); }
Team ChessBoard::getTeamTwo() const { return getTeamTwoImpl(); }
Team ChessBoard::getOtherTeam(Team team) const { return getOtherTeamImpl(team); }

std::optional<BoardMove> ChessBoard::createBoardMove(BoardSquare const &fromSquare, BoardSquare const &toSquare, PieceType promotionPieceType) const { return createBoardMoveImpl(fromSquare, toSquare, promotionPieceType); }
std::optional<BoardMove> ChessBoard::getLastCompletedMove() const { return getLastCompletedMoveImpl(); }
std::vector<BoardMove> const& ChessBoard::getAllCompletedMoves() const { return getAllCompletedMovesImpl(); }

bool ChessBoard::makeMove(BoardMove const &move) { return makeMoveImpl(move); }
bool ChessBoard::undoMove() { return undoMoveImpl(); }
bool ChessBoard::redoMove() { return redoMoveImpl(); }

int ChessBoard::getNumRows() const { return getNumRowsImpl(); }
int ChessBoard::getNumCols() const { return getNumColsImpl(); }

bool ChessBoard::isInCheck(Team team) const { return isInCheckImpl(team); }
bool ChessBoard::isInCheckMate(Team team) const { return isInCheckMateImpl(team); }
bool ChessBoard::isInStaleMate(Team team) const { return isInStaleMateImpl(team); }
