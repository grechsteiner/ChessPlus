// IChessBoard.cc

#include <vector>
#include <stack>
#include <optional>
#include <memory>

#include "IChessBoard.h"
#include "Constants.h"
#include "BoardSquare.h"
#include "BoardMove.h"
#include "PieceData.h"


std::unique_ptr<IChessBoard> IChessBoard::clone() const { return cloneImpl(); }

std::optional<PieceData> IChessBoard::getPieceDataAt(BoardSquare const &boardSquare) const { return getPieceDataAtImpl(boardSquare); }
std::vector<BoardSquare> IChessBoard::getAllBoardSquares() const { return getAllBoardSquaresImpl(); }

bool IChessBoard::isSquareOnBoard(BoardSquare const &boardSquare) const { return isSquareOnBoardImpl(boardSquare); }
bool IChessBoard::isSquareEmpty(BoardSquare const &boardSquare) const { return isSquareEmptyImpl(boardSquare); }
bool IChessBoard::isSquareSameTeam(BoardSquare const &boardSquare, Team ownTeam) const { return isSquareSameTeamImpl(boardSquare, ownTeam); }
bool IChessBoard::isSquareOtherTeam(BoardSquare const &boardSquare, Team ownTeam) const { return isSquareOtherTeamImpl(boardSquare, ownTeam); }
bool IChessBoard::isSquareAttacked(BoardSquare const &boardSquare, Team ownTeam) const { return isSquareAttackedImpl(boardSquare, ownTeam); }

bool IChessBoard::isInCheck(Team team) const { return isInCheckImpl(team); }
bool IChessBoard::isInCheckMate(Team team) const { return isInCheckMateImpl(team); }
bool IChessBoard::isInStaleMate(Team team) const { return isInStaleMateImpl(team); }

std::vector<BoardMove> IChessBoard::generateAllLegalMovesAtSquare(BoardSquare const &boardSquare) const { return generateAllLegalMovesAtSquareImpl(boardSquare); }
std::vector<BoardMove> IChessBoard::generateAllLegalMoves(Team team) const { return generateAllLegalMovesImpl(team); }
std::vector<BoardMove> IChessBoard::generateCapturingMoves(Team team) const { return generateCapturingMovesImpl(team); }
std::vector<BoardMove> IChessBoard::generateCheckApplyingMoves(Team team) const { return generateCheckApplyingMovesImpl(team); }
std::vector<BoardMove> IChessBoard::generateCaptureAvoidingMoves(Team team) const { return generateCaptureAvoidingMovesImpl(team); }

bool IChessBoard::setPosition(BoardSquare const &boardSquare, Team team, PieceType pieceType, PieceDirection pieceDirection, bool hasMoved, std::optional<int> pieceScore) { return setPositionImpl(boardSquare, team, pieceType, pieceDirection, hasMoved, pieceScore); }
bool IChessBoard::clearPosition(BoardSquare const &boardSquare) { return clearPositionImpl(boardSquare); }
void IChessBoard::clearBoard() { clearBoardImpl(); }

std::optional<BoardMove> IChessBoard::createBoardMove(BoardSquare const &fromSquare, BoardSquare const &toSquare, std::optional<PieceType> promotionPieceType) const { return createBoardMoveImpl(fromSquare, toSquare, promotionPieceType); }
bool IChessBoard::makeMove(BoardMove const &boardMove) { return makeMoveImpl(boardMove); }
bool IChessBoard::undoMove() { return undoMoveImpl(); }
bool IChessBoard::redoMove() { return redoMoveImpl(); }

std::optional<BoardMove> IChessBoard::getLastCompletedMove() const { return getLastCompletedMoveImpl(); }
std::stack<BoardMove> const& IChessBoard::getAllCompletedMoves() const { return getAllCompletedMovesImpl(); }

Team IChessBoard::getTeamOne() const { return getTeamOneImpl(); }
Team IChessBoard::getTeamTwo() const { return getTeamTwoImpl(); }

int IChessBoard::getNumRows() const { return getNumRowsImpl(); }
int IChessBoard::getNumCols() const { return getNumColsImpl(); }
