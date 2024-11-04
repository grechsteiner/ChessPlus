// ChessBoard.cc

#include <vector>
#include <optional>
#include <memory>

#include "ChessBoard.h"
#include "Constants.h"
#include "BoardSquare.h"
#include "BoardMove.h"
#include "PieceInfo.h"
#include "PieceData.h"

#pragma mark - BoardSquareIterator

ChessBoard::BoardSquareIterator ChessBoard::createBoardSquareIterator(int row, int col, int numRows, int numCols) const {
    return BoardSquareIterator(row, col, numRows, numCols);
}

ChessBoard::BoardSquareIterator::BoardSquareIterator(int row, int col, int numRows, int numCols) :
    boardSquare(BoardSquare(row, col)), numRows(numRows), numCols(numCols) {}

BoardSquare ChessBoard::BoardSquareIterator::operator*() const {
    return boardSquare;
}

ChessBoard::BoardSquareIterator& ChessBoard::BoardSquareIterator::operator++() {
    if (boardSquare.boardCol + 1 < numCols) {
        ++boardSquare.boardCol;
    } else {
        boardSquare.boardCol = 0;
        ++boardSquare.boardRow;
    }
    return *this;
}

bool ChessBoard::BoardSquareIterator::operator==(BoardSquareIterator const &other) const {
    return 
        boardSquare == other.boardSquare &&
        numRows == other.numRows &&
        numCols == other.numCols;
}
bool ChessBoard::BoardSquareIterator::operator!=(BoardSquareIterator const &other) const {
    return !(*this ==other);
}


#pragma mark - ReverseBoardSquareIterator

ChessBoard::ReverseBoardSquareIterator ChessBoard::createReverseBoardSquareIterator(int row, int col, int numRows, int numCols) const {
    return ReverseBoardSquareIterator(row, col, numRows, numCols);
}

ChessBoard::ReverseBoardSquareIterator::ReverseBoardSquareIterator(int row, int col, int numRows, int numCols) :
    boardSquare(BoardSquare(row, col)), numRows(numRows), numCols(numCols) {}

BoardSquare ChessBoard::ReverseBoardSquareIterator::operator*() const {
    return boardSquare;
}

ChessBoard::ReverseBoardSquareIterator& ChessBoard::ReverseBoardSquareIterator::operator++() {
    if (boardSquare.boardCol > 0) {
        --boardSquare.boardCol;
    } else {
        boardSquare.boardCol = numCols - 1;
        --boardSquare.boardRow;
    }
    return *this;
}

bool ChessBoard::ReverseBoardSquareIterator::operator==(ReverseBoardSquareIterator const &other) const {
    return 
        boardSquare == other.boardSquare &&
        numRows == other.numRows &&
        numCols == other.numCols;
}
bool ChessBoard::ReverseBoardSquareIterator::operator!=(ReverseBoardSquareIterator const &other) const {
    return !(*this ==other);
}


#pragma mark - ChessBoard

std::unique_ptr<ChessBoard> ChessBoard::clone() const { return cloneImpl(); }

std::optional<PieceData> ChessBoard::getPieceDataAt(BoardSquare const &boardSquare) const { return getPieceDataAtImpl(boardSquare); }
std::optional<PieceInfo> ChessBoard::getPieceInfoAt(BoardSquare const &boardSquare) const { return getPieceInfoAtImpl(boardSquare); }
std::vector<BoardSquare> ChessBoard::getAllBoardSquares() const { return getAllBoardSquaresImpl(); }

bool ChessBoard::isSquareOnBoard(BoardSquare const &boardSquare) const { return isSquareOnBoardImpl(boardSquare); }
bool ChessBoard::isSquareEmpty(BoardSquare const &boardSquare) const { return isSquareEmptyImpl(boardSquare); }
bool ChessBoard::isSquareSameTeam(BoardSquare const &boardSquare, Team ownTeam) const { return isSquareSameTeamImpl(boardSquare, ownTeam); }
bool ChessBoard::isSquareOtherTeam(BoardSquare const &boardSquare, Team ownTeam) const { return isSquareOtherTeamImpl(boardSquare, ownTeam); }
bool ChessBoard::isSquareAttacked(BoardSquare const &boardSquare, Team ownTeam) const { return isSquareAttackedImpl(boardSquare, ownTeam); }

bool ChessBoard::isInCheck(Team team) const { return isInCheckImpl(team); }
bool ChessBoard::isInCheckMate(Team team) const { return isInCheckMateImpl(team); }
bool ChessBoard::isInStaleMate(Team team) const { return isInStaleMateImpl(team); }

std::vector<std::unique_ptr<BoardMove>> ChessBoard::generateAllLegalMovesAtSquare(BoardSquare const &boardSquare) const { return generateAllLegalMovesAtSquareImpl(boardSquare); }
std::vector<std::unique_ptr<BoardMove>> ChessBoard::generateAllLegalMoves(Team team) const { return generateAllLegalMovesImpl(team); }
std::vector<std::unique_ptr<BoardMove>> ChessBoard::generateCheckApplyingMoves(Team team) const { return generateCheckApplyingMovesImpl(team); }
std::vector<std::unique_ptr<BoardMove>> ChessBoard::generateCapturingMoves(Team team) const { return generateCapturingMovesImpl(team); }
std::vector<std::unique_ptr<BoardMove>> ChessBoard::generateCaptureAvoidingMoves(Team team) const { return generateCaptureAvoidingMovesImpl(team); }
std::vector<std::unique_ptr<BoardMove>> ChessBoard::generateWinningMoves(Team team) const { return generateWinningMovesImpl(team); }

bool ChessBoard::setPosition(BoardSquare const &boardSquare, PieceData const &pieceData) { return setPositionImpl(boardSquare, pieceData); }
bool ChessBoard::clearPosition(BoardSquare const &boardSquare) { return clearPositionImpl(boardSquare); }
void ChessBoard::clearBoard() { clearBoardImpl(); }

std::optional<std::unique_ptr<BoardMove>> ChessBoard::createBoardMove(BoardSquare const &fromSquare, BoardSquare const &toSquare, std::optional<PieceType> promotionPieceType) const { return createBoardMoveImpl(fromSquare, toSquare, promotionPieceType); }
bool ChessBoard::makeMove(std::unique_ptr<BoardMove> const &boardMove) { return makeMoveImpl(boardMove); }
bool ChessBoard::undoMove() { return undoMoveImpl(); }
bool ChessBoard::redoMove() { return redoMoveImpl(); }

std::vector<std::unique_ptr<BoardMove>> const& ChessBoard::getCompletedMoves() const { return getCompletedMovesImpl(); }

Team ChessBoard::getTeamOne() const { return getTeamOneImpl(); }
Team ChessBoard::getTeamTwo() const { return getTeamTwoImpl(); }

int ChessBoard::getNumRows() const { return getNumRowsImpl(); }
int ChessBoard::getNumCols() const { return getNumColsImpl(); }

ChessBoard::BoardSquareIterator ChessBoard::begin() { return beginImpl(); }
ChessBoard::BoardSquareIterator ChessBoard::begin() const { return beginImpl(); }
ChessBoard::BoardSquareIterator ChessBoard::cbegin() const { return cbeginImpl(); }
ChessBoard::BoardSquareIterator ChessBoard::end() { return endImpl(); }
ChessBoard::BoardSquareIterator ChessBoard::end() const { return endImpl(); }
ChessBoard::BoardSquareIterator ChessBoard::cend() const { return cendImpl(); }

ChessBoard::ReverseBoardSquareIterator ChessBoard::rbegin() { return rbeginImpl(); }
ChessBoard::ReverseBoardSquareIterator ChessBoard::rbegin() const { return rbeginImpl(); }
ChessBoard::ReverseBoardSquareIterator ChessBoard::crbegin() const { return crbeginImpl(); }
ChessBoard::ReverseBoardSquareIterator ChessBoard::rend() { return rendImpl(); }
ChessBoard::ReverseBoardSquareIterator ChessBoard::rend() const { return rendImpl(); }
ChessBoard::ReverseBoardSquareIterator ChessBoard::crend() const { return crendImpl(); }
