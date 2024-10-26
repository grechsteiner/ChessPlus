// ChessBoard.cc

#include <vector>
#include <stack>
#include <optional>
#include <memory>
#include <cassert>
#include <algorithm>
#include <utility>

#include "ChessBoard.h"
#include "IChessBoard.h"
#include "Cloneable.h"
#include "Constants.h"
#include "BoardSquare.h"
#include "BoardMove.h"
#include "Piece.h"
#include "PieceInfo.h"
#include "ChessPieceFactory.h"


#pragma mark - Specific To Board Class

// Basic ctor
ChessBoard::ChessBoard(int numRows, int numCols) : 
    numRows(numRows), numCols(numCols) {

    grid.resize(numRows);
    for (int row = 0; row < numRows; ++row) {
        grid[row].resize(numCols);
    } 
}

// Copy ctor
ChessBoard::ChessBoard(ChessBoard const &other) : 
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
ChessBoard::ChessBoard(ChessBoard &&other) noexcept : 
    numRows(other.numRows), numCols(other.numCols), completedMoves(std::move(other.completedMoves)), redoMoves(std::move(other.redoMoves)), grid(std::move(other.grid)) {}

// Copy assignment
ChessBoard& ChessBoard::operator=(ChessBoard const &other) {
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
ChessBoard& ChessBoard::operator=(ChessBoard &&other) noexcept {
    if (this != &other) {
        numRows = other.numRows;
        numCols = other.numCols;
        completedMoves = std::move(other.completedMoves);
        redoMoves = std::move(other.redoMoves);
        grid = std::move(other.grid);
    }
    return *this;
}

Team ChessBoard::getOtherTeam(Team team) const { 
    return team == teamOne ? teamTwo : teamOne; 
}

void ChessBoard::clearCompletedMoves() {
    completedMoves = std::stack<BoardMove>();
}

void ChessBoard::clearRedoMoves() {
    redoMoves = std::stack<BoardMove>();
}

std::vector<BoardMove> ChessBoard::generateAllPseudoLegalMovesAtSquare(BoardSquare const &boardSquare, bool onlyAttackingMoves) const {
    return isSquareOnBoard(boardSquare) && !isSquareEmpty(boardSquare)
        ? grid[boardSquare.getBoardRow()][boardSquare.getBoardCol()]->getMoves(*this, boardSquare, onlyAttackingMoves) 
        : std::vector<BoardMove>();
}

std::vector<BoardMove> ChessBoard::generateAllPseudoLegalMoves(Team team, bool onlyAttackingMoves) const {
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

bool ChessBoard::canMakeMove(Team team) const {
    return !generateAllLegalMoves(team).empty();
}

bool ChessBoard::isMoveValid(BoardMove const &boardMove) const {
    if (isSquareOnBoard(boardMove.getFromSquare())) {
        std::vector<BoardMove> pieceBoardMoves = generateAllLegalMovesAtSquare(boardMove.getFromSquare());
        if (std::find(pieceBoardMoves.begin(), pieceBoardMoves.end(), boardMove) != pieceBoardMoves.end()) {
            return true;
        }
    }
    return false;
}

void ChessBoard::performMove(BoardMove const &boardMove) {
    boardMove.makeBoardMove(*this);                 // Apply the move
    completedMoves.push(boardMove);                 // Track it for undoing 
    clearRedoMoves();                               // Clear redo moves (can't redo after making a move)
}

void ChessBoard::performUndoMove() {
    BoardMove lastMove = completedMoves.top();      // Get the last made move
    completedMoves.pop();                           // Pop it off the completed moves stack
    lastMove.undoBoardMove(*this);                  // Undo the move
    redoMoves.push(lastMove);                       // Push it to the redo moves stack
}

void ChessBoard::performRedoMove() {
    BoardMove lastUndoneMove = redoMoves.top();     // Get the last move to be undone
    redoMoves.pop();                                // Pop it off the redo moves stack
    lastUndoneMove.makeBoardMove(*this);            // Apply the move
    completedMoves.push(lastUndoneMove);            // Push it to the completed moves stack
}

bool ChessBoard::doesMoveApplyCheck(BoardMove const &boardMove) const {
    std::optional<PieceInfo> movedPieceInfo = getPieceInfoAt(boardMove.getFromSquare());
    if (movedPieceInfo.has_value()) {
        ChessBoard temp(*this);
        temp.performMove(boardMove);
        return temp.isInCheck(getOtherTeam(movedPieceInfo.value().getTeam()));
    }
    assert(false);
}

bool ChessBoard::doesMoveCapturePiece(BoardMove const &boardMove) const {
    std::optional<PieceInfo> movedPieceInfo = getPieceInfoAt(boardMove.getFromSquare());
    std::optional<PieceInfo> attackedPieceInfo = getPieceInfoAt(boardMove.getCaptureSquare());
    if (movedPieceInfo.has_value()) {
        return attackedPieceInfo.has_value() && attackedPieceInfo.value().getTeam() != movedPieceInfo.value().getTeam();
    }
    assert(false);
}

bool ChessBoard::doesMoveLeavePieceAttacked(BoardMove const &boardMove) const {
    std::optional<PieceInfo> movedPieceInfo = getPieceInfoAt(boardMove.getFromSquare());
    if (movedPieceInfo.has_value()) {
        ChessBoard temp(*this);
        temp.performMove(boardMove);
        return temp.generateCapturingMoves(getOtherTeam(movedPieceInfo.value().getTeam())).empty();
    } 
    assert(false);
}

bool ChessBoard::doesMoveLeaveTeamInCheck(BoardMove const &boardMove) const {
    std::optional<PieceInfo> movedPieceInfo = getPieceInfoAt(boardMove.getFromSquare());
    if (movedPieceInfo.has_value()) {
        ChessBoard temp(*this);
        temp.performMove(boardMove);
        return temp.isInCheck(movedPieceInfo.value().getTeam());
    }
    assert(false);
} 


#pragma mark - ChessBoard Interface

std::optional<PieceInfo> ChessBoard::getPieceInfoAtImpl(BoardSquare const &boardSquare) const {
    return isSquareOnBoard(boardSquare) && grid[boardSquare.getBoardRow()][boardSquare.getBoardCol()] != nullptr
        ? std::make_optional<PieceInfo>(grid[boardSquare.getBoardRow()][boardSquare.getBoardCol()]->getPieceInfo())
        : std::nullopt;
}

std::vector<BoardSquare> ChessBoard::getAllBoardSquaresImpl() const {
    std::vector<BoardSquare> boardSquares;
    for (int row = 0; row < numRows; ++row) {
        for (int col = 0; col < numCols; ++col) {
            boardSquares.emplace_back(BoardSquare(row, col));
        }
    }
    return boardSquares;
}

bool ChessBoard::isSquareOnBoardImpl(BoardSquare const &boardSquare) const {
    int boardRow = boardSquare.getBoardRow();
    int boardCol = boardSquare.getBoardCol();
    return 
        boardRow >= 0 && 
        boardRow < numRows && 
        boardCol >= 0 && 
        boardCol < numCols;
}

bool ChessBoard::isSquareEmptyImpl(BoardSquare const &boardSquare) const {
    return 
        isSquareOnBoard(boardSquare) && 
        !getPieceInfoAt(boardSquare).has_value();
}

bool ChessBoard::isSquareSameTeamImpl(BoardSquare const &boardSquare, Team ownTeam) const {
    return 
        isSquareOnBoard(boardSquare) && 
        getPieceInfoAt(boardSquare).has_value() && 
        getPieceInfoAt(boardSquare).value().getTeam() == ownTeam;
}

bool ChessBoard::isSquareOtherTeamImpl(BoardSquare const &boardSquare, Team ownTeam) const {
    return 
        isSquareOnBoard(boardSquare) && 
        getPieceInfoAt(boardSquare).has_value() && 
        getPieceInfoAt(boardSquare).value().getTeam() == getOtherTeam(ownTeam);
}

bool ChessBoard::isSquareAttackedImpl(BoardSquare const &boardSquare, Team ownTeam) const {
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

bool ChessBoard::isInCheckImpl(Team team) const {
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

bool ChessBoard::isInCheckMateImpl(Team team) const {
    return isInCheck(team) && !canMakeMove(team);
}

bool ChessBoard::isInStaleMateImpl(Team team) const {
    return !canMakeMove(team) && !isInCheck(team);
}

std::vector<BoardMove> ChessBoard::generateAllLegalMovesAtSquareImpl(BoardSquare const &boardSquare) const {
    std::vector<BoardMove> legalBoardMoves;
    std::vector<BoardMove> pseudoLegalBoardMoves = generateAllPseudoLegalMovesAtSquare(boardSquare, false);
    for (BoardMove const &pseudoLegalBoardMove : pseudoLegalBoardMoves) {
        if (!doesMoveLeaveTeamInCheck(pseudoLegalBoardMove)) {
            legalBoardMoves.emplace_back(pseudoLegalBoardMove);
        }
    }
    return legalBoardMoves;
}

std::vector<BoardMove> ChessBoard::generateAllLegalMovesImpl(Team team) const { 
    std::vector<BoardMove> legalBoardMoves;
    std::vector<BoardMove> pseudoLegalBoardMoves = generateAllPseudoLegalMoves(team, false);
    for (BoardMove const &pseudoLegalBoardMove : pseudoLegalBoardMoves) {
        if (!doesMoveLeaveTeamInCheck(pseudoLegalBoardMove)) {
            legalBoardMoves.emplace_back(pseudoLegalBoardMove);
        }
    }
    return legalBoardMoves;
}

std::vector<BoardMove> ChessBoard::generateCapturingMovesImpl(Team team) const { 
    std::vector<BoardMove> capturingBoardMoves;
    std::vector<BoardMove> legalBoardMoves = generateAllLegalMoves(team);
    for (BoardMove const &legalBoardMove : legalBoardMoves) {
        if (doesMoveCapturePiece(legalBoardMove)) {
            capturingBoardMoves.emplace_back(legalBoardMove);
        }
    }
    return capturingBoardMoves;
}

std::vector<BoardMove> ChessBoard::generateCheckApplyingMovesImpl(Team team) const {
    std::vector<BoardMove> checkApplyingBoardMoves;
    std::vector<BoardMove> legalBoardMoves = generateAllLegalMoves(team);
    for (BoardMove const &legalBoardMove : legalBoardMoves) {
        if (doesMoveApplyCheck(legalBoardMove)) {
            checkApplyingBoardMoves.emplace_back(legalBoardMove);
        }
    }
    return checkApplyingBoardMoves;
}

std::vector<BoardMove> ChessBoard::generateCaptureAvoidingMovesImpl(Team team) const {
    std::vector<BoardMove> captureAvoidingBoardMoves;
    std::vector<BoardMove> legalBoardMoves = generateAllLegalMoves(team);
    for (BoardMove const &legalBoardMove : legalBoardMoves) {
        if (!doesMoveLeavePieceAttacked(legalBoardMove)) {
            captureAvoidingBoardMoves.emplace_back(legalBoardMove);
        }
    }
    return captureAvoidingBoardMoves;
}

bool ChessBoard::setPositionImpl(BoardSquare const &boardSquare, Team team, PieceType pieceType, PieceDirection pieceDirection, bool hasMoved, std::optional<int> pieceScore) {
    if (isSquareOnBoard(boardSquare)) {
        clearCompletedMoves();
        clearRedoMoves();
        grid[boardSquare.getBoardRow()][boardSquare.getBoardCol()] = ChessPieceFactory::createPiece(team, pieceType, pieceDirection, hasMoved, pieceScore);
        return true;
    }
    return false;
}

bool ChessBoard::clearPositionImpl(BoardSquare const &boardSquare) {
    if (isSquareOnBoard(boardSquare)) {
        clearCompletedMoves();
        clearRedoMoves();
        grid[boardSquare.getBoardRow()][boardSquare.getBoardCol()] = nullptr;
        return true;
    }
    return false;
}

void ChessBoard::clearBoardImpl() {
    for (BoardSquare const &boardSquare : getAllBoardSquares()) {
        clearPosition(boardSquare);
    }
    clearCompletedMoves();
    clearRedoMoves();
}

// TODO: This will need to be changed with the upcoming changes to BoadMove class
std::optional<BoardMove> ChessBoard::createBoardMoveImpl(BoardSquare const &fromSquare, BoardSquare const &toSquare, std::optional<PieceType> promotionPieceType) const { 
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

bool ChessBoard::makeMoveImpl(BoardMove const &boardMove) {
    if (isMoveValid(boardMove)) {
        performMove(boardMove);
        return true;
    }
    return false;                              
}

bool ChessBoard::undoMoveImpl() {
    if (completedMoves.empty()) {
        return false;
    } else {
        performUndoMove();
        return true;
    }
}

bool ChessBoard::redoMoveImpl() {
    if (redoMoves.empty()) {
        return false;
    } else {
        performRedoMove();
        return true;
    }
}

std::optional<BoardMove> ChessBoard::getLastCompletedMoveImpl() const {
    return completedMoves.empty() ? std::nullopt : std::make_optional<BoardMove>(completedMoves.top());
}

std::stack<BoardMove> const& ChessBoard::getAllCompletedMovesImpl() const {
    return completedMoves;
}

Team ChessBoard::getTeamOneImpl() const { 
    return teamOne;
}

Team ChessBoard::getTeamTwoImpl() const  { 
    return teamTwo;
}

int ChessBoard::getNumRowsImpl() const {
    return numRows;
}

int ChessBoard::getNumColsImpl() const {
    return numCols;
}
