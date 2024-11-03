// ChessBoard.cc

#include <vector>
#include <optional>
#include <memory>
#include <cassert>
#include <algorithm>
#include <utility>

#include "ChessBoardImpl.h"
#include "ChessBoard.h"
#include "Cloneable.h"
#include "Constants.h"
#include "BoardSquare.h"
#include "BoardMove.h"
#include "Piece.h"
#include "PieceData.h"
#include "PieceFactory.h"


#pragma mark - Specific To Board Class

// Basic ctor
ChessBoardImpl::ChessBoardImpl(int numRows, int numCols) : 
    numRows(numRows), numCols(numCols) {

    grid.resize(numRows);
    for (int row = 0; row < numRows; ++row) {
        grid[row].resize(numCols);
    } 
}

// Copy ctor
ChessBoardImpl::ChessBoardImpl(ChessBoardImpl const &other) : 
    numRows(other.numRows), numCols(other.numCols) {

    // Copy completed moves
    for (std::unique_ptr<BoardMove> const &completedMove : other.completedMoves) {
        completedMoves.emplace_back(completedMove->clone());
    }

    // Copy redo moves
    for (std::unique_ptr<BoardMove> const &redoMove : other.redoMoves) {
        redoMoves.emplace_back(redoMove->clone());
    }

    grid.resize(numRows);
    for (int row = 0; row < numRows; ++row) {
        grid[row].resize(numCols);
        for (int col = 0; col < numCols; ++col) {
            if (other.grid[row][col] != nullptr) {
                grid[row][col] = other.grid[row][col]->clone();
            }
        }
    } 
}

// Move ctor
ChessBoardImpl::ChessBoardImpl(ChessBoardImpl &&other) noexcept : 
    numRows(other.numRows), numCols(other.numCols), completedMoves(std::move(other.completedMoves)), redoMoves(std::move(other.redoMoves)), grid(std::move(other.grid)) {}

// Copy assignment
ChessBoardImpl& ChessBoardImpl::operator=(ChessBoardImpl const &other) {
    if (this != &other) {
        numRows = other.numRows;
        numCols = other.numCols;
        
        // Copy completed moves
        for (std::unique_ptr<BoardMove> const &completedMove : other.completedMoves) {
            completedMoves.emplace_back(completedMove->clone());
        }

        // Copy redo moves
        for (std::unique_ptr<BoardMove> const &redoMove : other.redoMoves) {
            redoMoves.emplace_back(redoMove->clone());
        }
        
        grid.resize(numRows);
        for (int row = 0; row < numRows; ++row) {
            grid[row].resize(numCols);
            for (int col = 0; col < numCols; ++col) {
                if (other.grid[row][col] != nullptr) {
                    grid[row][col] = other.grid[row][col]->clone();
                }
            }
        }
    }
    return *this;
}

// Move assignment
ChessBoardImpl& ChessBoardImpl::operator=(ChessBoardImpl &&other) noexcept {
    if (this != &other) {
        numRows = other.numRows;
        numCols = other.numCols;
        completedMoves = std::move(other.completedMoves);
        redoMoves = std::move(other.redoMoves);
        grid = std::move(other.grid);
    }
    return *this;
}

Team ChessBoardImpl::getOtherTeam(Team team) const { 
    return team == teamOne ? teamTwo : teamOne; 
}

void ChessBoardImpl::clearCompletedMoves() {
    completedMoves = std::vector<std::unique_ptr<BoardMove>>();
}

void ChessBoardImpl::clearRedoMoves() {
    redoMoves = std::vector<std::unique_ptr<BoardMove>>();
}

std::vector<std::unique_ptr<BoardMove>> ChessBoardImpl::generateAllPseudoLegalMovesAtSquare(BoardSquare const &boardSquare, bool onlyAttackingMoves) const {
    return isSquareOnBoard(boardSquare) && !isSquareEmpty(boardSquare)
        ? grid[boardSquare.getBoardRow()][boardSquare.getBoardCol()]->getMoves(*this, boardSquare, onlyAttackingMoves) 
        : std::vector<std::unique_ptr<BoardMove>>();
}

std::vector<std::unique_ptr<BoardMove>> ChessBoardImpl::generateAllPseudoLegalMoves(Team team, bool onlyAttackingMoves) const {
    std::vector<std::unique_ptr<BoardMove>> boardMoves;
    for (BoardSquare const &boardSquare : getAllBoardSquares()) {
        std::optional<PieceData> pieceData = getPieceDataAt(boardSquare);
        if (pieceData.has_value() && pieceData.value().team == team) {
            std::vector<std::unique_ptr<BoardMove>> pieceBoardMoves = generateAllPseudoLegalMovesAtSquare(boardSquare, onlyAttackingMoves);
            for (std::unique_ptr<BoardMove> &pieceBoardMove : pieceBoardMoves) {
                boardMoves.emplace_back(std::move(pieceBoardMove));
            }
            pieceBoardMoves.clear();
        }
    }
    return boardMoves;
}

bool ChessBoardImpl::canMakeMove(Team team) const {
    return !generateAllLegalMoves(team).empty();
}

bool ChessBoardImpl::isMoveValid(std::unique_ptr<BoardMove> const &boardMove) const {
    if (isSquareOnBoard(boardMove->getFromSquare())) {
        std::vector<std::unique_ptr<BoardMove>> pieceBoardMoves = generateAllLegalMovesAtSquare(boardMove->getFromSquare());
        if (std::find(pieceBoardMoves.begin(), pieceBoardMoves.end(), boardMove) != pieceBoardMoves.end()) {
            return true;
        }
    }
    return false;
}

void ChessBoardImpl::performMove(std::unique_ptr<BoardMove> const &boardMove) {
    boardMove->makeBoardMove(*this);                                            // Apply the move
    completedMoves.emplace_back(boardMove->clone());                            // Track it for undoing 
    clearRedoMoves();                                                           // Clear redo moves (can't redo after making a move)
}

void ChessBoardImpl::performUndoMove() {
    std::unique_ptr<BoardMove> lastMove = std::move(completedMoves.back());     // Get the last made move
    completedMoves.pop_back();                                                  // Pop it off the completed moves stack
    lastMove->undoBoardMove(*this);                                             // Undo the move
    redoMoves.emplace_back(std::move(lastMove));                                // Push it to the redo moves stack
}

void ChessBoardImpl::performRedoMove() {
    std::unique_ptr<BoardMove> lastUndoneMove = std::move(redoMoves.back());    // Get the last move to be undone
    redoMoves.pop_back();                                                       // Pop it off the redo moves stack
    lastUndoneMove->makeBoardMove(*this);                                       // Apply the move
    completedMoves.emplace_back(std::move(lastUndoneMove));                     // Push it to the completed moves stack
}

bool ChessBoardImpl::doesMoveApplyCheck(std::unique_ptr<BoardMove> const &boardMove) const {
    std::optional<PieceData> movedPieceData = getPieceDataAt(boardMove->getFromSquare());
    if (movedPieceData.has_value()) {
        ChessBoardImpl temp(*this);
        temp.performMove(boardMove);
        return temp.isInCheck(getOtherTeam(movedPieceData.value().team));
    }
    assert(false);
}

bool ChessBoardImpl::doesMoveCapturePiece(std::unique_ptr<BoardMove> const &boardMove) const {
    std::optional<PieceData> movedPieceData = getPieceDataAt(boardMove->getFromSquare());
    std::optional<PieceData> attackedPieceData = getPieceDataAt(boardMove->getCaptureSquare());
    if (movedPieceData.has_value()) {
        return attackedPieceData.has_value() && attackedPieceData.value().team != movedPieceData.value().team;
    }
    assert(false);
}

bool ChessBoardImpl::doesMoveLeavePieceAttacked(std::unique_ptr<BoardMove> const &boardMove) const {
    std::optional<PieceData> movedPieceData = getPieceDataAt(boardMove->getFromSquare());
    if (movedPieceData.has_value()) {
        ChessBoardImpl temp(*this);
        temp.performMove(boardMove);
        return temp.generateCapturingMoves(getOtherTeam(movedPieceData.value().team)).empty();
    } 
    assert(false);
}

bool ChessBoardImpl::doesMoveLeaveTeamInCheck(std::unique_ptr<BoardMove> const &boardMove) const {
    std::optional<PieceData> movedPieceData = getPieceDataAt(boardMove->getFromSquare());
    if (movedPieceData.has_value()) {
        ChessBoardImpl temp(*this);
        temp.performMove(boardMove);
        return temp.isInCheck(movedPieceData.value().team);
    }
    assert(false);
} 


#pragma mark - ChessBoard Interface

std::optional<PieceData> ChessBoardImpl::getPieceDataAtImpl(BoardSquare const &boardSquare) const {
    return isSquareOnBoard(boardSquare) && grid[boardSquare.getBoardRow()][boardSquare.getBoardCol()] != nullptr
        ? std::make_optional<PieceData>(grid[boardSquare.getBoardRow()][boardSquare.getBoardCol()]->getPieceData())
        : std::nullopt;
}

std::optional<PieceInfo> ChessBoardImpl::getPieceInfoAtImpl(BoardSquare const &boardSquare) const {
    return isSquareOnBoard(boardSquare) && grid[boardSquare.getBoardRow()][boardSquare.getBoardCol()] != nullptr
        ? std::make_optional<PieceInfo>(grid[boardSquare.getBoardRow()][boardSquare.getBoardCol()]->getPieceInfo())
        : std::nullopt;
}

std::vector<BoardSquare> ChessBoardImpl::getAllBoardSquaresImpl() const {
    std::vector<BoardSquare> boardSquares;
    for (int row = 0; row < numRows; ++row) {
        for (int col = 0; col < numCols; ++col) {
            boardSquares.emplace_back(BoardSquare(row, col));
        }
    }
    return boardSquares;
}

bool ChessBoardImpl::isSquareOnBoardImpl(BoardSquare const &boardSquare) const {
    int boardRow = boardSquare.getBoardRow();
    int boardCol = boardSquare.getBoardCol();
    return 
        boardRow >= 0 && 
        boardRow < numRows && 
        boardCol >= 0 && 
        boardCol < numCols;
}

bool ChessBoardImpl::isSquareEmptyImpl(BoardSquare const &boardSquare) const {
    return 
        isSquareOnBoard(boardSquare) && 
        !getPieceInfoAt(boardSquare).has_value();
}

bool ChessBoardImpl::isSquareSameTeamImpl(BoardSquare const &boardSquare, Team ownTeam) const {
    if (isSquareOnBoard(boardSquare)) {
        std::optional<PieceData> pieceDataAtSquare = getPieceDataAt(boardSquare);
        if (pieceDataAtSquare.has_value() && pieceDataAtSquare.value().team == ownTeam) {
            return true;
        }
    }
    return false;
}

bool ChessBoardImpl::isSquareOtherTeamImpl(BoardSquare const &boardSquare, Team ownTeam) const {
    if (isSquareOnBoard(boardSquare)) {
        std::optional<PieceData> pieceDataAtSquare = getPieceDataAt(boardSquare);
        if (pieceDataAtSquare && pieceDataAtSquare.value().team == getOtherTeam(ownTeam)) {
            return true;
        }
    }
    return false;
}

bool ChessBoardImpl::isSquareAttackedImpl(BoardSquare const &boardSquare, Team ownTeam) const {
    if (isSquareOnBoard(boardSquare)) {
        std::vector<std::unique_ptr<BoardMove>> attackingBoardMoves = generateAllPseudoLegalMoves(getOtherTeam(ownTeam), true);
        for (std::unique_ptr<BoardMove> const& boardMove : attackingBoardMoves) {
            if (boardMove->getCaptureSquare() == boardSquare) {
                return true;
            }
        }
    }
    return false;
}

bool ChessBoardImpl::isInCheckImpl(Team team) const {
    for (BoardSquare const &boardSquare : getAllBoardSquares()) {
        std::optional<PieceData> pieceData = getPieceDataAt(boardSquare);
        if (pieceData.has_value() && pieceData.value().pieceType == PieceType::KING && pieceData.value().team == team) {
            if (isSquareAttacked(boardSquare, team)) {
                return true;
            }
        }
    }
    return false;
}

bool ChessBoardImpl::isInCheckMateImpl(Team team) const {
    return isInCheck(team) && !canMakeMove(team);
}

bool ChessBoardImpl::isInStaleMateImpl(Team team) const {
    return !canMakeMove(team) && !isInCheck(team);
}

std::vector<std::unique_ptr<BoardMove>> ChessBoardImpl::generateAllLegalMovesAtSquareImpl(BoardSquare const &boardSquare) const {
    std::vector<std::unique_ptr<BoardMove>> legalBoardMoves;
    std::vector<std::unique_ptr<BoardMove>> pseudoLegalBoardMoves = generateAllPseudoLegalMovesAtSquare(boardSquare, false);
    for (std::unique_ptr<BoardMove> &pseudoLegalBoardMove : pseudoLegalBoardMoves) {
        if (!doesMoveLeaveTeamInCheck(pseudoLegalBoardMove)) {
            legalBoardMoves.emplace_back(std::move(pseudoLegalBoardMove));
        }
    }
    return legalBoardMoves;
}

std::vector<std::unique_ptr<BoardMove>> ChessBoardImpl::generateAllLegalMovesImpl(Team team) const { 
    std::vector<std::unique_ptr<BoardMove>> legalBoardMoves;
    std::vector<std::unique_ptr<BoardMove>> pseudoLegalBoardMoves = generateAllPseudoLegalMoves(team, false);
    for (std::unique_ptr<BoardMove> &pseudoLegalBoardMove : pseudoLegalBoardMoves) {
        if (!doesMoveLeaveTeamInCheck(pseudoLegalBoardMove)) {
            legalBoardMoves.emplace_back(std::move(pseudoLegalBoardMove));
        }
    }
    return legalBoardMoves;
}

std::vector<std::unique_ptr<BoardMove>> ChessBoardImpl::generateCapturingMovesImpl(Team team) const { 
    std::vector<std::unique_ptr<BoardMove>> capturingBoardMoves;
    std::vector<std::unique_ptr<BoardMove>> legalBoardMoves = generateAllLegalMoves(team);
    for (std::unique_ptr<BoardMove> &legalBoardMove : legalBoardMoves) {
        if (doesMoveCapturePiece(legalBoardMove)) {
            capturingBoardMoves.emplace_back(std::move(legalBoardMove));
        }
    }
    return capturingBoardMoves;
}

std::vector<std::unique_ptr<BoardMove>> ChessBoardImpl::generateCheckApplyingMovesImpl(Team team) const {
    std::vector<std::unique_ptr<BoardMove>> checkApplyingBoardMoves;
    std::vector<std::unique_ptr<BoardMove>> legalBoardMoves = generateAllLegalMoves(team);
    for (std::unique_ptr<BoardMove> &legalBoardMove : legalBoardMoves) {
        if (doesMoveApplyCheck(legalBoardMove)) {
            checkApplyingBoardMoves.emplace_back(std::move(legalBoardMove));
        }
    }
    return checkApplyingBoardMoves;
}

std::vector<std::unique_ptr<BoardMove>> ChessBoardImpl::generateCaptureAvoidingMovesImpl(Team team) const {
    std::vector<std::unique_ptr<BoardMove>> captureAvoidingBoardMoves;
    std::vector<std::unique_ptr<BoardMove>> legalBoardMoves = generateAllLegalMoves(team);
    for (std::unique_ptr<BoardMove> &legalBoardMove : legalBoardMoves) {
        if (!doesMoveLeavePieceAttacked(legalBoardMove)) {
            captureAvoidingBoardMoves.emplace_back(std::move(legalBoardMove));
        }
    }
    return captureAvoidingBoardMoves;
}

bool ChessBoardImpl::setPositionImpl(BoardSquare const &boardSquare, PieceData const &pieceData) {
    if (isSquareOnBoard(boardSquare)) {
        clearCompletedMoves();
        clearRedoMoves();
        grid[boardSquare.getBoardRow()][boardSquare.getBoardCol()] = PieceFactory::createPiece(pieceData);
        return true;
    }
    return false;
}

bool ChessBoardImpl::clearPositionImpl(BoardSquare const &boardSquare) {
    if (isSquareOnBoard(boardSquare)) {
        clearCompletedMoves();
        clearRedoMoves();
        grid[boardSquare.getBoardRow()][boardSquare.getBoardCol()] = nullptr;
        return true;
    }
    return false;
}

void ChessBoardImpl::clearBoardImpl() {
    for (BoardSquare const &boardSquare : getAllBoardSquares()) {
        clearPosition(boardSquare);
    }
    clearCompletedMoves();
    clearRedoMoves();
}

std::optional<std::unique_ptr<BoardMove>> ChessBoardImpl::createBoardMoveImpl(BoardSquare const &fromSquare, BoardSquare const &toSquare, std::optional<PieceType> promotionPieceType) const { 
    if (!isSquareOnBoard(fromSquare)) {
        return std::nullopt;
    }

    // Try to match "fromSquare toSquare promotionPieceType" to a legal BoardMove
    std::vector<std::unique_ptr<BoardMove>> legalBoardMoves = generateAllLegalMovesAtSquare(fromSquare);
    auto it = std::find_if(legalBoardMoves.begin(), legalBoardMoves.end(), [&fromSquare, &toSquare, &promotionPieceType](std::unique_ptr<BoardMove> const &boardMove) {
        return
            fromSquare == boardMove->getFromSquare() &&
            toSquare == boardMove->getToSquare() &&
            promotionPieceType == boardMove->getPromotionPieceType();
    });
    return it != legalBoardMoves.end() ? std::make_optional<std::unique_ptr<BoardMove>>(std::move(*it)) : std::nullopt;
}

bool ChessBoardImpl::makeMoveImpl(std::unique_ptr<BoardMove> const &boardMove) {
    if (isMoveValid(boardMove)) {
        performMove(boardMove);
        return true;
    }
    return false;                              
}

bool ChessBoardImpl::undoMoveImpl() {
    if (completedMoves.empty()) {
        return false;
    } else {
        performUndoMove();
        return true;
    }
}

bool ChessBoardImpl::redoMoveImpl() {
    if (redoMoves.empty()) {
        return false;
    } else {
        performRedoMove();
        return true;
    }
}

std::vector<std::unique_ptr<BoardMove>> const& ChessBoardImpl::getCompletedMovesImpl() const {
    return completedMoves;
}

Team ChessBoardImpl::getTeamOneImpl() const { 
    return teamOne;
}

Team ChessBoardImpl::getTeamTwoImpl() const  { 
    return teamTwo;
}

int ChessBoardImpl::getNumRowsImpl() const {
    return numRows;
}

int ChessBoardImpl::getNumColsImpl() const {
    return numCols;
}
