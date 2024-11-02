// ChessBoard.cc

#include <vector>
#include <stack>
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
#include "OldBoardMove.h"
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
    numRows(other.numRows), numCols(other.numCols), completedMoves(other.completedMoves), redoMoves(other.redoMoves) {

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
        completedMoves = other.completedMoves;
        redoMoves = other.redoMoves;
        
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
    completedMoves = std::stack<OldBoardMove>();
}

void ChessBoardImpl::clearRedoMoves() {
    redoMoves = std::stack<OldBoardMove>();
}

std::vector<OldBoardMove> ChessBoardImpl::generateAllPseudoLegalMovesAtSquare(BoardSquare const &boardSquare, bool onlyAttackingMoves) const {
    return isSquareOnBoard(boardSquare) && !isSquareEmpty(boardSquare)
        ? grid[boardSquare.getBoardRow()][boardSquare.getBoardCol()]->getMoves(*this, boardSquare, onlyAttackingMoves) 
        : std::vector<OldBoardMove>();
}

std::vector<OldBoardMove> ChessBoardImpl::generateAllPseudoLegalMoves(Team team, bool onlyAttackingMoves) const {
    std::vector<OldBoardMove> boardMoves;
    for (BoardSquare const &boardSquare : getAllBoardSquares()) {
        std::optional<PieceInfo> pieceInfo = getPieceInfoAt(boardSquare);
        if (pieceInfo.has_value() && pieceInfo.value().pieceData.team == team) {
            std::vector<OldBoardMove> pieceBoardMoves = generateAllPseudoLegalMovesAtSquare(boardSquare, onlyAttackingMoves);
            boardMoves.insert(boardMoves.end(), pieceBoardMoves.begin(), pieceBoardMoves.end());
        }
    }
    return boardMoves;
}

bool ChessBoardImpl::canMakeMove(Team team) const {
    return !generateAllLegalMoves(team).empty();
}

bool ChessBoardImpl::isMoveValid(OldBoardMove const &boardMove) const {
    if (isSquareOnBoard(boardMove.getFromSquare())) {
        std::vector<OldBoardMove> pieceBoardMoves = generateAllLegalMovesAtSquare(boardMove.getFromSquare());
        if (std::find(pieceBoardMoves.begin(), pieceBoardMoves.end(), boardMove) != pieceBoardMoves.end()) {
            return true;
        }
    }
    return false;
}

void ChessBoardImpl::performMove(OldBoardMove const &boardMove) {
    boardMove.makeBoardMove(*this);                 // Apply the move
    completedMoves.push(boardMove);                 // Track it for undoing 
    clearRedoMoves();                               // Clear redo moves (can't redo after making a move)
}

void ChessBoardImpl::performUndoMove() {
    OldBoardMove lastMove = completedMoves.top();      // Get the last made move
    completedMoves.pop();                           // Pop it off the completed moves stack
    lastMove.undoBoardMove(*this);                  // Undo the move
    redoMoves.push(lastMove);                       // Push it to the redo moves stack
}

void ChessBoardImpl::performRedoMove() {
    OldBoardMove lastUndoneMove = redoMoves.top();     // Get the last move to be undone
    redoMoves.pop();                                // Pop it off the redo moves stack
    lastUndoneMove.makeBoardMove(*this);            // Apply the move
    completedMoves.push(lastUndoneMove);            // Push it to the completed moves stack
}

bool ChessBoardImpl::doesMoveApplyCheck(OldBoardMove const &boardMove) const {
    std::optional<PieceInfo> movedPieceInfo = getPieceInfoAt(boardMove.getFromSquare());
    if (movedPieceInfo.has_value()) {
        ChessBoardImpl temp(*this);
        temp.performMove(boardMove);
        return temp.isInCheck(getOtherTeam(movedPieceInfo.value().pieceData.team));
    }
    assert(false);
}

bool ChessBoardImpl::doesMoveCapturePiece(OldBoardMove const &boardMove) const {
    std::optional<PieceInfo> movedPieceInfo = getPieceInfoAt(boardMove.getFromSquare());
    std::optional<PieceInfo> attackedPieceInfo = getPieceInfoAt(boardMove.getCaptureSquare());
    if (movedPieceInfo.has_value()) {
        return attackedPieceInfo.has_value() && attackedPieceInfo.value().pieceData.team != movedPieceInfo.value().pieceData.team;
    }
    assert(false);
}

bool ChessBoardImpl::doesMoveLeavePieceAttacked(OldBoardMove const &boardMove) const {
    std::optional<PieceInfo> movedPieceInfo = getPieceInfoAt(boardMove.getFromSquare());
    if (movedPieceInfo.has_value()) {
        ChessBoardImpl temp(*this);
        temp.performMove(boardMove);
        return temp.generateCapturingMoves(getOtherTeam(movedPieceInfo.value().pieceData.team)).empty();
    } 
    assert(false);
}

bool ChessBoardImpl::doesMoveLeaveTeamInCheck(OldBoardMove const &boardMove) const {
    std::optional<PieceInfo> movedPieceInfo = getPieceInfoAt(boardMove.getFromSquare());
    if (movedPieceInfo.has_value()) {
        ChessBoardImpl temp(*this);
        temp.performMove(boardMove);
        return temp.isInCheck(movedPieceInfo.value().pieceData.team);
    }
    assert(false);
} 


#pragma mark - ChessBoard Interface

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
        std::optional<PieceInfo> pieceInfoAtSquare = getPieceInfoAt(boardSquare);
        if (pieceInfoAtSquare.has_value() && pieceInfoAtSquare.value().pieceData.team == ownTeam) {
            return true;
        }
    }
    return false;
}

bool ChessBoardImpl::isSquareOtherTeamImpl(BoardSquare const &boardSquare, Team ownTeam) const {
    if (isSquareOnBoard(boardSquare)) {
        std::optional<PieceInfo> pieceInfoAtSquare = getPieceInfoAt(boardSquare);
        if (pieceInfoAtSquare && pieceInfoAtSquare.value().pieceData.team == getOtherTeam(ownTeam)) {
            return true;
        }
    }
    return false;
}

bool ChessBoardImpl::isSquareAttackedImpl(BoardSquare const &boardSquare, Team ownTeam) const {
    if (isSquareOnBoard(boardSquare)) {
        std::vector<OldBoardMove> attackingBoardMoves = generateAllPseudoLegalMoves(getOtherTeam(ownTeam), true);
        for (OldBoardMove const& boardMove : attackingBoardMoves) {
            if (boardMove.getCaptureSquare() == boardSquare) {
                return true;
            }
        }
    }
    return false;
}

bool ChessBoardImpl::isInCheckImpl(Team team) const {
    for (BoardSquare const &boardSquare : getAllBoardSquares()) {
        std::optional<PieceInfo> pieceInfo = getPieceInfoAt(boardSquare);
        if (pieceInfo.has_value() && pieceInfo.value().pieceData.pieceType == PieceType::KING && pieceInfo.value().pieceData.team == team) {
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

std::vector<OldBoardMove> ChessBoardImpl::generateAllLegalMovesAtSquareImpl(BoardSquare const &boardSquare) const {
    std::vector<OldBoardMove> legalBoardMoves;
    std::vector<OldBoardMove> pseudoLegalBoardMoves = generateAllPseudoLegalMovesAtSquare(boardSquare, false);
    for (OldBoardMove const &pseudoLegalBoardMove : pseudoLegalBoardMoves) {
        if (!doesMoveLeaveTeamInCheck(pseudoLegalBoardMove)) {
            legalBoardMoves.emplace_back(pseudoLegalBoardMove);
        }
    }
    return legalBoardMoves;
}

std::vector<OldBoardMove> ChessBoardImpl::generateAllLegalMovesImpl(Team team) const { 
    std::vector<OldBoardMove> legalBoardMoves;
    std::vector<OldBoardMove> pseudoLegalBoardMoves = generateAllPseudoLegalMoves(team, false);
    for (OldBoardMove const &pseudoLegalBoardMove : pseudoLegalBoardMoves) {
        if (!doesMoveLeaveTeamInCheck(pseudoLegalBoardMove)) {
            legalBoardMoves.emplace_back(pseudoLegalBoardMove);
        }
    }
    return legalBoardMoves;
}

std::vector<OldBoardMove> ChessBoardImpl::generateCapturingMovesImpl(Team team) const { 
    std::vector<OldBoardMove> capturingBoardMoves;
    std::vector<OldBoardMove> legalBoardMoves = generateAllLegalMoves(team);
    for (OldBoardMove const &legalBoardMove : legalBoardMoves) {
        if (doesMoveCapturePiece(legalBoardMove)) {
            capturingBoardMoves.emplace_back(legalBoardMove);
        }
    }
    return capturingBoardMoves;
}

std::vector<OldBoardMove> ChessBoardImpl::generateCheckApplyingMovesImpl(Team team) const {
    std::vector<OldBoardMove> checkApplyingBoardMoves;
    std::vector<OldBoardMove> legalBoardMoves = generateAllLegalMoves(team);
    for (OldBoardMove const &legalBoardMove : legalBoardMoves) {
        if (doesMoveApplyCheck(legalBoardMove)) {
            checkApplyingBoardMoves.emplace_back(legalBoardMove);
        }
    }
    return checkApplyingBoardMoves;
}

std::vector<OldBoardMove> ChessBoardImpl::generateCaptureAvoidingMovesImpl(Team team) const {
    std::vector<OldBoardMove> captureAvoidingBoardMoves;
    std::vector<OldBoardMove> legalBoardMoves = generateAllLegalMoves(team);
    for (OldBoardMove const &legalBoardMove : legalBoardMoves) {
        if (!doesMoveLeavePieceAttacked(legalBoardMove)) {
            captureAvoidingBoardMoves.emplace_back(legalBoardMove);
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

// TODO: This will need to be changed with the upcoming changes to BoadMove class
std::optional<OldBoardMove> ChessBoardImpl::createBoardMoveImpl(BoardSquare const &fromSquare, BoardSquare const &toSquare, std::optional<PieceType> promotionPieceType) const { 
    if (!isSquareOnBoard(fromSquare)) {
        return std::nullopt;
    }

    // Try to match "fromSquare toSquare promotionPieceType" to a legal BoardMove
    std::vector<OldBoardMove> legalBoardMoves = generateAllLegalMovesAtSquare(fromSquare);
    auto it = std::find_if(legalBoardMoves.begin(), legalBoardMoves.end(), [&fromSquare, &toSquare, &promotionPieceType](OldBoardMove const &boardMove) {
        return
            fromSquare == boardMove.getFromSquare() &&
            toSquare == boardMove.getToSquare() &&
            promotionPieceType == boardMove.getPromotionPieceType();
    });
    return it != legalBoardMoves.end() ? std::make_optional<OldBoardMove>(*it) : std::nullopt;
}

bool ChessBoardImpl::makeMoveImpl(OldBoardMove const &boardMove) {
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

std::optional<OldBoardMove> ChessBoardImpl::getLastCompletedMoveImpl() const {
    return completedMoves.empty() ? std::nullopt : std::make_optional<OldBoardMove>(completedMoves.top());
}

std::stack<OldBoardMove> const& ChessBoardImpl::getAllCompletedMovesImpl() const {
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
