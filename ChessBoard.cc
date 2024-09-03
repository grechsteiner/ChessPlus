// Board.cc

#include <vector>
#include <stack>
#include <optional>
#include <memory>
#include <cassert>
#include <algorithm>
#include <utility>

#include "Board.h"
#include "Constants.h"
#include "BoardSquare.h"
#include "BoardMove.h"
#include "Piece.h"
#include "PieceInfo.h"
#include "ChessPieceFactory.h"


#pragma mark - Specific To Board Class

// Basic ctor
SmartChessBoard::SmartChessBoard(int numRows, int numCols) : 
    numRows(numRows), numCols(numCols) {

    grid.resize(numRows);
    for (int row = 0; row < numRows; ++row) {
        grid[row].resize(numCols);
    } 
}

// Copy ctor
SmartChessBoard::SmartChessBoard(SmartChessBoard const &other) : 
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
SmartChessBoard::SmartChessBoard(SmartChessBoard &&other) noexcept : 
    numRows(other.numRows), numCols(other.numCols), completedMoves(std::move(other.completedMoves)), redoMoves(std::move(other.redoMoves)), grid(std::move(other.grid)) {}

// Copy assignment
SmartChessBoard& SmartChessBoard::operator=(SmartChessBoard const &other) {
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
SmartChessBoard& SmartChessBoard::operator=(SmartChessBoard &&other) noexcept {
    if (this != &other) {
        numRows = other.numRows;
        numCols = other.numCols;
        completedMoves = std::move(other.completedMoves);
        redoMoves = std::move(other.redoMoves);
        grid = std::move(other.grid);
    }
    return *this;
}

Team SmartChessBoard::getOtherTeam(Team team) const { 
    return team == teamOne ? teamTwo : teamOne; 
}

void SmartChessBoard::clearCompletedMoves() {
    completedMoves = std::stack<BoardMove>();
}

void SmartChessBoard::clearRedoMoves() {
    redoMoves = std::stack<BoardMove>();
}

std::vector<BoardMove> SmartChessBoard::generateAllPseudoLegalMovesAtSquare(BoardSquare const &boardSquare, bool onlyAttackingMoves) const {
    return isSquareOnBoard(boardSquare) && !isSquareEmpty(boardSquare)
        ? grid[boardSquare.getBoardRow()][boardSquare.getBoardCol()]->getMoves(*this, boardSquare, onlyAttackingMoves) 
        : std::vector<BoardMove>();
}

std::vector<BoardMove> SmartChessBoard::generateAllPseudoLegalMoves(Team team, bool onlyAttackingMoves) const {
    std::vector<BoardMove> boardMoves;
    for (BoardSquare const &boardSquare : getAllBoardSquares()) {
        std::optional<PieceInfo> pieceInfo = getPieceInfoAt(boardSquare);
        if (pieceInfo.has_value() && pieceInfo.value().getTeam() == team) {
            std::vector<BoardMove> pieceBoardMoves = generateAllPseudoLegalMovesAtSquare(boardSquare, onlyAttackingMoves);
            boardMoves.insert(boardMoves.end(), pieceBoardMoves.begin(), pieceBoardMoves.end());
        }
    }
    return boardMoves;
}

bool SmartChessBoard::canMakeMove(Team team) const {
    return !generateAllLegalMoves(team).empty();
}

bool SmartChessBoard::isMoveValid(BoardMove const &boardMove) const {
    if (isSquareOnBoard(boardMove.getFromSquare())) {
        std::vector<BoardMove> pieceBoardMoves = generateAllLegalMovesAtSquare(boardMove.getFromSquare());
        if (std::find(pieceBoardMoves.begin(), pieceBoardMoves.end(), boardMove) != pieceBoardMoves.end()) {
            return true;
        }
    }
    return false;
}

void SmartChessBoard::performMove(BoardMove const &boardMove) {
    boardMove.makeBoardMove(*this);         // Apply the move
    completedMoves.push(boardMove);         // Track it for undoing 
    clearRedoMoves();                       // Clear redo moves (can't redo after making a move)
}

bool SmartChessBoard::doesMoveApplyCheck(BoardMove const &boardMove) const {
    std::optional<PieceInfo> movedPieceInfo = getPieceInfoAt(boardMove.getFromSquare());
    if (movedPieceInfo.has_value()) {
        const_cast<SmartChessBoard*>(this)->performMove(boardMove);
        bool doesMoveApplyCheck = isInCheck(getOtherTeam(movedPieceInfo.value().getTeam()));
        const_cast<SmartChessBoard*>(this)->undoMove();
        return doesMoveApplyCheck;
    }
    assert(false);
}

bool SmartChessBoard::doesMoveCapturePiece(BoardMove const &boardMove) const {
    std::optional<PieceInfo> movedPieceInfo = getPieceInfoAt(boardMove.getFromSquare());
    std::optional<PieceInfo> attackedPieceInfo = getPieceInfoAt(boardMove.getCaptureSquare());
    if (movedPieceInfo.has_value()) {
        return attackedPieceInfo.has_value() && attackedPieceInfo.value().getTeam() != movedPieceInfo.value().getTeam();
    }
    assert(false);
}

bool SmartChessBoard::doesMoveLeavePieceAttacked(BoardMove const &boardMove) const {
    std::optional<PieceInfo> movedPieceInfo = getPieceInfoAt(boardMove.getFromSquare());
    if (movedPieceInfo.has_value()) {
        const_cast<SmartChessBoard*>(this)->performMove(boardMove);
        bool doesMoveLeavePieceAttacked = generateCapturingMoves(getOtherTeam(movedPieceInfo.value().getTeam())).empty();
        const_cast<SmartChessBoard*>(this)->undoMove();
        return doesMoveLeavePieceAttacked;
    } 
    assert(false);
}

bool SmartChessBoard::doesMoveLeaveTeamInCheck(BoardMove const &boardMove) const {
    std::optional<PieceInfo> movedPieceInfo = getPieceInfoAt(boardMove.getFromSquare());
    if (movedPieceInfo.has_value()) {
        const_cast<SmartChessBoard*>(this)->performMove(boardMove);
        bool isInCheckAfterMove = isInCheck(movedPieceInfo.value().getTeam());
        const_cast<SmartChessBoard*>(this)->undoMove();
        return isInCheckAfterMove;
    }
    assert(false);
} 


#pragma mark - ChessBoard Interface

std::optional<PieceInfo> SmartChessBoard::getPieceInfoAtImpl(BoardSquare const &boardSquare) const {
    return isSquareOnBoard(boardSquare) && grid[boardSquare.getBoardRow()][boardSquare.getBoardCol()] != nullptr
        ? std::make_optional<PieceInfo>(grid[boardSquare.getBoardRow()][boardSquare.getBoardCol()]->getPieceInfo())
        : std::nullopt;
}

std::vector<BoardSquare> SmartChessBoard::getAllBoardSquaresImpl() const {
    std::vector<BoardSquare> boardSquares;
    for (int row = 0; row < numRows; ++row) {
        for (int col = 0; col < numCols; ++col) {
            boardSquares.emplace_back(BoardSquare(row, col));
        }
    }
    return boardSquares;
}

bool SmartChessBoard::isSquareOnBoardImpl(BoardSquare const &boardSquare) const {
    int boardRow = boardSquare.getBoardRow();
    int boardCol = boardSquare.getBoardCol();
    return 
        boardRow >= 0 && 
        boardRow < numRows && 
        boardCol >= 0 && 
        boardCol < numCols;
}

bool SmartChessBoard::isSquareEmptyImpl(BoardSquare const &boardSquare) const {
    return 
        isSquareOnBoard(boardSquare) && 
        !getPieceInfoAt(boardSquare).has_value();
}

bool SmartChessBoard::isSquareSameTeamImpl(BoardSquare const &boardSquare, Team ownTeam) const {
    return 
        isSquareOnBoard(boardSquare) && 
        getPieceInfoAt(boardSquare).has_value() && 
        getPieceInfoAt(boardSquare).value().getTeam() == ownTeam;
}

bool SmartChessBoard::isSquareOtherTeamImpl(BoardSquare const &boardSquare, Team ownTeam) const {
    return 
        isSquareOnBoard(boardSquare) && 
        getPieceInfoAt(boardSquare).has_value() && 
        getPieceInfoAt(boardSquare).value().getTeam() == getOtherTeam(ownTeam);
}

bool SmartChessBoard::isSquareAttackedImpl(BoardSquare const &boardSquare, Team ownTeam) const {
    if (isSquareOnBoard(boardSquare)) {
        std::vector<BoardMove> attackingBoardMoves = generateAllPseudoLegalMoves(getOtherTeam(ownTeam), true);
        for (BoardMove const& boardMove : attackingBoardMoves) {
            if (boardMove.getCaptureSquare() == boardSquare) {
                return true;
            }
        }
    }
    return false;
}

bool SmartChessBoard::isInCheckImpl(Team team) const {
    for (BoardSquare const &boardSquare : getAllBoardSquares()) {
        std::optional<PieceInfo> pieceInfo = getPieceInfoAt(boardSquare);
        if (pieceInfo.has_value() && pieceInfo.value().getPieceType() == PieceType::KING && pieceInfo.value().getTeam() == team) {
            if (isSquareAttacked(boardSquare, team)) {
                return true;
            }
        }
    }
    return false;
}

bool SmartChessBoard::isInCheckMateImpl(Team team) const {
    return isInCheck(team) && !canMakeMove(team);
}

bool SmartChessBoard::isInStaleMateImpl(Team team) const {
    return !canMakeMove(team) && !isInCheck(team);
}

std::vector<BoardMove> SmartChessBoard::generateAllLegalMovesAtSquareImpl(BoardSquare const &boardSquare) const {
    std::vector<BoardMove> legalBoardMoves;
    std::vector<BoardMove> pseudoLegalBoardMoves = generateAllPseudoLegalMovesAtSquare(boardSquare, false);
    for (BoardMove const &pseudoLegalBoardMove : pseudoLegalBoardMoves) {
        if (!doesMoveLeaveTeamInCheck(pseudoLegalBoardMove)) {
            legalBoardMoves.emplace_back(pseudoLegalBoardMove);
        }
    }
    return legalBoardMoves;
}

std::vector<BoardMove> SmartChessBoard::generateAllLegalMovesImpl(Team team) const { 
    std::vector<BoardMove> legalBoardMoves;
    std::vector<BoardMove> pseudoLegalBoardMoves = generateAllPseudoLegalMoves(team, false);
    for (BoardMove const &pseudoLegalBoardMove : pseudoLegalBoardMoves) {
        if (!doesMoveLeaveTeamInCheck(pseudoLegalBoardMove)) {
            legalBoardMoves.emplace_back(pseudoLegalBoardMove);
        }
    }
    return legalBoardMoves;
}

std::vector<BoardMove> SmartChessBoard::generateCapturingMovesImpl(Team team) const { 
    std::vector<BoardMove> capturingBoardMoves;
    std::vector<BoardMove> legalBoardMoves = generateAllLegalMoves(team);
    for (BoardMove const &legalBoardMove : legalBoardMoves) {
        if (doesMoveCapturePiece(legalBoardMove)) {
            capturingBoardMoves.emplace_back(legalBoardMove);
        }
    }
    return capturingBoardMoves;
}

std::vector<BoardMove> SmartChessBoard::generateCheckApplyingMovesImpl(Team team) const {
    std::vector<BoardMove> checkApplyingBoardMoves;
    std::vector<BoardMove> legalBoardMoves = generateAllLegalMoves(team);
    for (BoardMove const &legalBoardMove : legalBoardMoves) {
        if (doesMoveApplyCheck(legalBoardMove)) {
            checkApplyingBoardMoves.emplace_back(legalBoardMove);
        }
    }
    return checkApplyingBoardMoves;
}

std::vector<BoardMove> SmartChessBoard::generateCaptureAvoidingMovesImpl(Team team) const {
    std::vector<BoardMove> captureAvoidingBoardMoves;
    std::vector<BoardMove> legalBoardMoves = generateAllLegalMoves(team);
    for (BoardMove const &legalBoardMove : legalBoardMoves) {
        if (!doesMoveLeavePieceAttacked(legalBoardMove)) {
            captureAvoidingBoardMoves.emplace_back(legalBoardMove);
        }
    }
    return captureAvoidingBoardMoves;
}

bool SmartChessBoard::setPositionImpl(BoardSquare const &boardSquare, Team team, PieceType pieceType, PieceDirection pieceDirection, bool hasMoved, std::optional<int> pieceScore) {
    if (isSquareOnBoard(boardSquare)) {
        clearCompletedMoves();
        clearRedoMoves();
        grid[boardSquare.getBoardRow()][boardSquare.getBoardCol()] = ChessPieceFactory::createPiece(team, pieceType, pieceDirection, hasMoved, pieceScore);
        return true;
    }
    return false;
}

bool SmartChessBoard::clearPositionImpl(BoardSquare const &boardSquare) {
    if (isSquareOnBoard(boardSquare)) {
        clearCompletedMoves();
        clearRedoMoves();
        grid[boardSquare.getBoardRow()][boardSquare.getBoardCol()] = nullptr;
        return true;
    }
    return false;
}

void SmartChessBoard::clearBoardImpl() {
    for (BoardSquare const &boardSquare : getAllBoardSquares()) {
        clearPosition(boardSquare);
    }
    clearCompletedMoves();
    clearRedoMoves();
}

std::optional<BoardMove> SmartChessBoard::createBoardMoveImpl(BoardSquare const &fromSquare, BoardSquare const &toSquare, std::optional<PieceType> promotionPieceType) const { 
    if (!isSquareOnBoard(fromSquare)) {
        return std::nullopt;
    }

    // Try to match "fromSquare toSquare promotionPieceType" to a legal BoardMove
    std::vector<BoardMove> legalBoardMoves = generateAllLegalMovesAtSquare(fromSquare);
    auto it = std::find_if(legalBoardMoves.begin(), legalBoardMoves.end(), [&fromSquare, &toSquare, &promotionPieceType](BoardMove const &boardMove) {
        return
            fromSquare == boardMove.getFromSquare() &&
            toSquare == boardMove.getToSquare() &&
            promotionPieceType == boardMove.getPromotionPieceType();
    });
    return it != legalBoardMoves.end() ? std::make_optional<BoardMove>(*it) : std::nullopt;
}

bool SmartChessBoard::makeMoveImpl(BoardMove const &boardMove) {
    if (isMoveValid(boardMove)) {
        performMove(boardMove);
        return true;
    }
    return false;                              
}

bool SmartChessBoard::undoMoveImpl() {
    if (completedMoves.empty()) {
        return false;
    }

    BoardMove lastMove = completedMoves.top();      // Get the last made move
    completedMoves.pop();                           // Pop it off the completed moves stack
    lastMove.undoBoardMove(*this);                  // Undo the move
    redoMoves.push(lastMove);                       // Push it to the redo moves stack
    return true;
}

bool SmartChessBoard::redoMoveImpl() {
    if (redoMoves.empty()) {
        return false;
    }

    BoardMove lastUndoneMove = redoMoves.top();     // Get the last move to be undone
    redoMoves.pop();                                // Pop it off the redo moves stack
    lastUndoneMove.makeBoardMove(*this);            // Apply the move
    completedMoves.push(lastUndoneMove);            // Push it to the completed moves stack
    return true;
}

std::optional<BoardMove> SmartChessBoard::getLastCompletedMoveImpl() const {
    return completedMoves.empty() ? std::nullopt : std::make_optional<BoardMove>(completedMoves.top());
}

std::stack<BoardMove> const& SmartChessBoard::getAllCompletedMovesImpl() const {
    return completedMoves;
}

Team SmartChessBoard::getTeamOneImpl() const { 
    return teamOne;
}

Team SmartChessBoard::getTeamTwoImpl() const  { 
    return teamTwo;
}

int SmartChessBoard::getNumRowsImpl() const {
    return numRows;
}

int SmartChessBoard::getNumColsImpl() const {
    return numCols;
}
