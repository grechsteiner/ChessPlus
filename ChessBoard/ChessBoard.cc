// ChessBoard.cc

#include "ChessBoard.h"

#include <memory>
#include <optional>
#include <utility>
#include <vector>

#include "BoardMove.h"
#include "BoardSquare.h"
#include "Constants.h"
#include "PieceData.h"
#include "PieceInfo.h"


#pragma mark - BoardSquareIterator

/*
 * Creates an instance of a BoardSquareIterator
 * To be used by concrete ChessBoard implementations
 */
ChessBoard::BoardSquareIterator ChessBoard::createBoardSquareIterator(int row, int col, int numRowsOnBoard, int numColsOnBoard) const {
    return BoardSquareIterator(row, col, numRowsOnBoard, numColsOnBoard);
}

// Basic ctor
ChessBoard::BoardSquareIterator::BoardSquareIterator(int row, int col, int numRowsOnBoard, int numColsOnBoard) :
    boardSquare(BoardSquare(row, col)), numRowsOnBoard(numRowsOnBoard), numColsOnBoard(numColsOnBoard) { }

// Copy ctor
ChessBoard::BoardSquareIterator::BoardSquareIterator(BoardSquareIterator const &other) :
    boardSquare(other.boardSquare), numRowsOnBoard(other.numRowsOnBoard), numColsOnBoard(other.numColsOnBoard) { }

// Move ctor
ChessBoard::BoardSquareIterator::BoardSquareIterator(BoardSquareIterator &&other) noexcept :
    boardSquare(std::move(other.boardSquare)), numRowsOnBoard(other.numRowsOnBoard), numColsOnBoard(other.numColsOnBoard) { }

// Copy assignmnet
ChessBoard::BoardSquareIterator& ChessBoard::BoardSquareIterator::operator=(BoardSquareIterator const &other) {
    if (this != &other) {
        boardSquare = other.boardSquare;
        numRowsOnBoard = other.numRowsOnBoard;
        numColsOnBoard = other.numColsOnBoard;
    }
    return *this;
}

// Move assignment
ChessBoard::BoardSquareIterator& ChessBoard::BoardSquareIterator::operator=(BoardSquareIterator &&other) noexcept {
    if (this != &other) {
        boardSquare = std::move(other.boardSquare);
        numRowsOnBoard = other.numRowsOnBoard;
        numColsOnBoard = other.numColsOnBoard;
    }
    return *this;
}

// Dereference
BoardSquare ChessBoard::BoardSquareIterator::operator*() const {
    return boardSquare;
}

// Pre-increment
ChessBoard::BoardSquareIterator& ChessBoard::BoardSquareIterator::operator++() {
    if (boardSquare.boardCol + 1 < numColsOnBoard) {
        ++boardSquare.boardCol;
    } else {
        boardSquare.boardCol = 0;
        ++boardSquare.boardRow;
    }
    return *this;
}

// Equality
bool ChessBoard::BoardSquareIterator::operator==(BoardSquareIterator const &other) const {
    return 
        boardSquare == other.boardSquare &&
        numRowsOnBoard == other.numRowsOnBoard &&
        numColsOnBoard == other.numColsOnBoard;
}

// Inequality
bool ChessBoard::BoardSquareIterator::operator!=(BoardSquareIterator const &other) const {
    return !(*this ==other);
}


#pragma mark - ReverseBoardSquareIterator

/*
 * Creates an instance of a ReverseBoardSquareIterator
 * To be used by concrete ChessBoard implementations
 */
ChessBoard::ReverseBoardSquareIterator ChessBoard::createReverseBoardSquareIterator(int row, int col, int numRowsOnBoard, int numColsOnBoard) const {
    return ReverseBoardSquareIterator(row, col, numRowsOnBoard, numColsOnBoard);
}

// Basic ctor
ChessBoard::ReverseBoardSquareIterator::ReverseBoardSquareIterator(int row, int col, int numRowsOnBoard, int numColsOnBoard) :
    boardSquare(BoardSquare(row, col)), numRowsOnBoard(numRowsOnBoard), numColsOnBoard(numColsOnBoard) { }

// Copy ctor
ChessBoard::ReverseBoardSquareIterator::ReverseBoardSquareIterator(ReverseBoardSquareIterator const &other) :
    boardSquare(other.boardSquare), numRowsOnBoard(other.numRowsOnBoard), numColsOnBoard(other.numColsOnBoard) { }

// Move ctor
ChessBoard::ReverseBoardSquareIterator::ReverseBoardSquareIterator(ReverseBoardSquareIterator &&other) noexcept :
    boardSquare(std::move(other.boardSquare)), numRowsOnBoard(other.numRowsOnBoard), numColsOnBoard(other.numColsOnBoard) { }

// Copy assignmnent
ChessBoard::ReverseBoardSquareIterator& ChessBoard::ReverseBoardSquareIterator::operator=(ReverseBoardSquareIterator const &other) {
    if (this != &other) {
        boardSquare = other.boardSquare;
        numRowsOnBoard = other.numRowsOnBoard;
        numColsOnBoard = other.numColsOnBoard;
    }
    return *this;
}

// Move assignment
ChessBoard::ReverseBoardSquareIterator& ChessBoard::ReverseBoardSquareIterator::operator=(ReverseBoardSquareIterator &&other) noexcept {
    if (this != &other) {
        boardSquare = std::move(other.boardSquare);
        numRowsOnBoard = other.numRowsOnBoard;
        numColsOnBoard = other.numColsOnBoard;
    }
    return *this;
}

// Dereference
BoardSquare ChessBoard::ReverseBoardSquareIterator::operator*() const {
    return boardSquare;
}

// Pre-increment
ChessBoard::ReverseBoardSquareIterator& ChessBoard::ReverseBoardSquareIterator::operator++() {
    if (boardSquare.boardCol > 0) {
        --boardSquare.boardCol;
    } else {
        boardSquare.boardCol = numColsOnBoard - 1;
        --boardSquare.boardRow;
    }
    return *this;
}

// Equality
bool ChessBoard::ReverseBoardSquareIterator::operator==(ReverseBoardSquareIterator const &other) const {
    return 
        boardSquare == other.boardSquare &&
        numRowsOnBoard == other.numRowsOnBoard &&
        numColsOnBoard == other.numColsOnBoard;
}

// Inequality
bool ChessBoard::ReverseBoardSquareIterator::operator!=(ReverseBoardSquareIterator const &other) const {
    return !(*this ==other);
}


#pragma mark - ChessBoard

// Basic ctor
ChessBoard::ChessBoard() { }

// Copy ctor
ChessBoard::ChessBoard(ChessBoard const &other) { }

// Move ctor
ChessBoard::ChessBoard(ChessBoard &&other) noexcept { }

// Copy assignment
ChessBoard& ChessBoard::operator=(ChessBoard const &other) {
    if (this != &other) {
        return *this;
    }
    return *this;
}

// Move assignment
ChessBoard& ChessBoard::operator=(ChessBoard &&other) noexcept {
    if (this != &other) {
        return *this;
    }
    return *this;
}

/* Virtual methods */
std::unique_ptr<ChessBoard> ChessBoard::clone() const { return cloneImpl(); }

std::optional<PieceData> ChessBoard::getPieceDataAt(BoardSquare const &boardSquare) const { return getPieceDataAtImpl(boardSquare); }
std::optional<PieceInfo> ChessBoard::getPieceInfoAt(BoardSquare const &boardSquare) const { return getPieceInfoAtImpl(boardSquare); }

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

void ChessBoard::setPosition(BoardSquare const &boardSquare, PieceData const &pieceData) { return setPositionImpl(boardSquare, pieceData); }
void ChessBoard::clearPosition(BoardSquare const &boardSquare) { return clearPositionImpl(boardSquare); }
void ChessBoard::clearBoard() { clearBoardImpl(); }

std::optional<std::unique_ptr<BoardMove>> ChessBoard::createBoardMove(BoardSquare const &fromSquare, BoardSquare const &toSquare, std::optional<PieceType> promotionPieceType) const { return createBoardMoveImpl(fromSquare, toSquare, promotionPieceType); }
void ChessBoard::makeMove(std::unique_ptr<BoardMove> const &boardMove) { return makeMoveImpl(boardMove); }
bool ChessBoard::isMoveLegal(std::unique_ptr<BoardMove> const &boardMove) const { return isMoveLegalImpl(boardMove); }
bool ChessBoard::undoMove() { return undoMoveImpl(); }
bool ChessBoard::redoMove() { return redoMoveImpl(); }

std::vector<std::unique_ptr<BoardMove>> const& ChessBoard::getCompletedMoves() const { return getCompletedMovesImpl(); }

Team ChessBoard::getTeamOne() const { return getTeamOneImpl(); }
Team ChessBoard::getTeamTwo() const { return getTeamTwoImpl(); }

int ChessBoard::getNumRowsOnBoard() const { return getNumRowsOnBoardImpl(); }
int ChessBoard::getNumColsOnBoard() const { return getNumColsOnBoardImpl(); }

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
