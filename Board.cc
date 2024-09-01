// Board.cc

#include <cassert>
#include <vector>
#include <memory>
#include <cctype>
#include <utility>
#include <algorithm>
#include <iostream>

#include "Board.h"
#include "Piece.h"
#include "ChessPieceFactory.h"
#include "BoardMove.h"
#include "UserSquare.h"
#include "BoardSquare.h"



#pragma mark - Internal Utility

Board::Board() 
    : grid(8) {
    for (auto& row : grid) {
        row.resize(8);
    } 
    initializeBoard(grid);
}

void Board::initializeBoard(std::vector<std::vector<std::unique_ptr<Piece>>> &grid) {
    for (auto& row : grid) {
        for (auto& piece : row) {
            piece = nullptr;
        }
    }
}

std::vector<BoardMove> Board::getPseudoLegalMovesAtSquare(BoardSquare const &boardSquare, bool onlyAttackingMoves) const {
    return isSquareOnBoard(boardSquare) && !isSquareEmpty(boardSquare)
        ? grid[boardSquare.getBoardRow()][boardSquare.getBoardCol()]->getMoves(*this, boardSquare, onlyAttackingMoves) 
        : std::vector<BoardMove>();
}

std::vector<BoardMove> Board::getPseudoLegalMoves(Team team, bool onlyAttackingMoves) const {
    std::vector<BoardMove> boardMoves;
    for (BoardSquare const &boardSquare : allBoardSquares()) {
        std::optional<PieceInfo> pieceInfo = getPieceInfoAt(boardSquare);
        if (pieceInfo.has_value() && pieceInfo.value().team == team) {
            std::vector<BoardMove> pieceMoves = getPseudoLegalMovesAtSquare(boardSquare, onlyAttackingMoves);
            boardMoves.insert(boardMoves.end(), pieceMoves.begin(), pieceMoves.end());
        }
    }
    return boardMoves;
}

void Board::makeMoveInternal(BoardMove const &boardMove) {
    boardMove.makeMove(*this);                               // Apply the move
    completedMoves.emplace_back(boardMove);                  // Track it for undoing 
    redoMoves.clear();                                  // Clear redo moves (can't redo after making a move)
}

bool Board::performMove(Team team) const {
    return !getLegalMoves(team).empty();
}

bool Board::isMoveValid(BoardMove const &boardMove) const {
    if (isSquareOnBoard(boardMove.getFromSquare())) {
        std::vector<BoardMove> pieceMoves = getLegalMovesAtSquare(boardMove.getFromSquare());
        if (std::find(pieceMoves.begin(), pieceMoves.end(), boardMove) != pieceMoves.end()) {
            return true;
        }
    }
    return false;
}

bool Board::doesMoveApplyCheck(BoardMove const &boardMove) const {
    Team turnTeam = getPieceInfoAt(boardMove.getFromSquare()).value().team;
    const_cast<Board*>(this)->makeMoveInternal(boardMove);
    bool doesMoveApplyCheck = isInCheck(getOtherTeam(turnTeam));
    const_cast<Board*>(this)->undoMove();
    return doesMoveApplyCheck;
}

bool Board::doesMoveCapturePiece(BoardMove const &boardMove) const {
    Team turnTeam = getPieceInfoAt(boardMove.getFromSquare()).value().team;
    std::optional<PieceInfo> attackedPieceInfo = getPieceInfoAt(boardMove.getCaptureSquare());
    return 
        attackedPieceInfo.has_value() && 
        attackedPieceInfo.value().team != turnTeam;
}

bool Board::doesMoveLeavePieceAttacked(BoardMove const &boardMove) const {
    Team turnTeam = getPieceInfoAt(boardMove.getFromSquare()).value().team;
    const_cast<Board*>(this)->makeMoveInternal(boardMove);
    bool doesMoveLeavePieceAttacked = getCapturingMoves(getOtherTeam(turnTeam)).empty();
    const_cast<Board*>(this)->undoMove();
    return doesMoveLeavePieceAttacked;

    /*
    std::vector<BoardMove> opponentMoves = getCapturingMoves(getOtherTeam(turnTeam));
    // Don't need to try every move if just two colours (I think) --> just check if capturingMoves.size() == 0
    for (BoardMove const &opponentMove : opponentMoves) {
        std::optional<PieceInfo> attackedPieceInfo = getPieceInfoAt(opponentMove.getCaptureSquare());
        if (attackedPieceInfo.has_value() && attackedPieceInfo.value().team == turnTeam) {
            const_cast<Board*>(this)->undoMove();
            return true;
        }
        
    }
    const_cast<Board*>(this)->undoMove();
    return false;
    */
}

bool Board::isInCheckAfterMove(BoardMove const &boardMove) const {
    Team turnTeam = getPieceInfoAt(boardMove.getFromSquare()).value().team;
    const_cast<Board*>(this)->makeMoveInternal(boardMove);
    bool isInCheckAfterMove = isInCheck(turnTeam);
    const_cast<Board*>(this)->undoMove();
    return isInCheckAfterMove;
} 


#pragma mark - ChessBoard Interface

std::optional<PieceInfo> Board::getPieceInfoAtImpl(BoardSquare const &boardSquare) const {
    return isSquareOnBoard(boardSquare) && grid[boardSquare.getBoardRow()][boardSquare.getBoardCol()] != nullptr
        ? std::make_optional<PieceInfo>(grid[boardSquare.getBoardRow()][boardSquare.getBoardCol()]->getPieceInfo())
        : std::nullopt;
}

std::vector<BoardSquare> Board::allBoardSquaresImpl() const {
    std::vector<BoardSquare> boardSquares;
    for (int row = 0; row < grid.size(); ++row) {
        for (int col = 0; col < grid[row].size(); ++col) {
            boardSquares.emplace_back(BoardSquare(row, col));
        }
    }
    return boardSquares;
}

bool Board::isSquareOnBoardImpl(BoardSquare const &boardSquare) const {
    int boardRow = boardSquare.getBoardRow();
    int boardCol = boardSquare.getBoardCol();
    return boardRow >= 0 && boardRow < grid.size() && boardCol >= 0 && boardCol < grid[boardRow].size();
}

bool Board::isSquareEmptyImpl(BoardSquare const &boardSquare) const {
    return isSquareOnBoard(boardSquare) && !getPieceInfoAt(boardSquare).has_value();
}

bool Board::isSquareOwnTeamImpl(BoardSquare const &boardSquare, Team team) const {
    return isSquareOnBoard(boardSquare) && !isSquareEmpty(boardSquare) && getPieceInfoAt(boardSquare).value().team == team;
}

bool Board::isSquareOtherTeamImpl(BoardSquare const &boardSquare, Team team) const {
    return isSquareOnBoard(boardSquare) && !isSquareEmpty(boardSquare) && getPieceInfoAt(boardSquare).value().team == getOtherTeam(team);
}

bool Board::isSquareAttackedImpl(BoardSquare const &boardSquare, Team team) const {
    if (isSquareOnBoard(boardSquare)) {
        std::vector<BoardMove> attackingBoardMoves = getPseudoLegalMoves(getOtherTeam(team), true);
        for (BoardMove const& boardMove : attackingBoardMoves) {
            if (boardMove.getCaptureSquare() == boardSquare) {
                return true;
            }
        }
    }
    return false;
}

bool Board::setPositionImpl(BoardSquare const &boardSquare, Team team, PieceType pieceType, PieceDirection pieceDirection, bool hasMoved, std::optional<int> pieceScore) {
    if (isSquareOnBoard(boardSquare)) {
        grid[boardSquare.getBoardRow()][boardSquare.getBoardCol()] = ChessPieceFactory::createPiece(team, pieceType, pieceDirection, hasMoved, pieceScore);
        return true;
    }
    return false;
}

bool Board::clearPositionImpl(BoardSquare const &boardSquare) {
    if (!isSquareOnBoard(boardSquare) || !getPieceInfoAt(boardSquare).has_value()) {
        return false;
    } else {
        grid[boardSquare.getBoardRow()][boardSquare.getBoardCol()] = nullptr;
        return true;
    }
}

void Board::clearBoardImpl() {
    for (BoardSquare const &boardSquare : allBoardSquares()) {
        clearPosition(boardSquare);
    }
    completedMoves.clear();     // TODO: Is this needed?
    redoMoves.clear();          // TODO: Is this needed?
}

bool Board::setBoardSizeImpl(int newNumRows, int newNumCols) { 
    if (newNumRows >= minNumRows && newNumRows <= maxNumRows && newNumCols >= minNumCols && newNumCols <= maxNumCols) {
        int oldNumRows = getNumRows();
        int oldNumCols = getNumCols();

        // Create new grid
        std::vector<std::vector<std::unique_ptr<Piece>>> newGrid(newNumRows);
        for (int boardRow = 0; boardRow < newNumRows; ++boardRow) {
            newGrid[boardRow].resize(newNumCols);
        }
        initializeBoard(newGrid);

        for (BoardSquare const &boardSquare : allBoardSquares()) {
            int oldRow = boardSquare.getBoardRow();
            int oldCol = boardSquare.getBoardCol();
            int newRow = oldRow + (newNumRows - oldNumRows);
            int newCol = oldCol;
            if (newRow >= 0 && newRow < newNumRows && newCol >= 0 && newCol < newNumCols) {
                newGrid[newRow][newCol] = std::move(grid[oldRow][oldCol]);
            }
        }

        // Replace the old grid with the new grid
        grid = std::move(newGrid);
    
        return true;
    } else {
        return false;
    }
}

std::vector<BoardMove> Board::getLegalMovesAtSquareImpl(BoardSquare const &boardSquare) const {
    std::vector<BoardMove> boardMoves = getPseudoLegalMovesAtSquare(boardSquare, false);
    for (auto it = boardMoves.begin(); it != boardMoves.end();) {
        if (isInCheckAfterMove(*it)) {
            it = boardMoves.erase(it);
        } else {
            ++it;
        }
    }
    return boardMoves;
}

std::vector<BoardMove> Board::getLegalMovesImpl(Team team) const { 
    std::vector<BoardMove> boardMoves = getPseudoLegalMoves(team, false);
    for (auto it = boardMoves.begin(); it != boardMoves.end();) {
        if (isInCheckAfterMove(*it)) {
            it = boardMoves.erase(it);
        } else {
            ++it;
        }
    }
    return boardMoves;
}

std::vector<BoardMove> Board::getCapturingMovesImpl(Team team) const { 
    std::vector<BoardMove> boardMoves = getLegalMoves(team);
    for (auto it = boardMoves.begin(); it != boardMoves.end();) {
        if (!doesMoveCapturePiece(*it)) {
            it = boardMoves.erase(it);
        } else {
            ++it;
        }
    }
    return boardMoves;
}

std::vector<BoardMove> Board::getCheckApplyingMovesImpl(Team team) const {
    std::vector<BoardMove> boardMoves = getLegalMoves(team);
    for (auto it = boardMoves.begin(); it != boardMoves.end();) {
        if (!doesMoveApplyCheck(*it)) {
            it = boardMoves.erase(it);
        } else {
            ++it;
        }
    }
    return boardMoves;
}

std::vector<BoardMove> Board::getCaptureAvoidingMovesImpl(Team team) const { 
    std::vector<BoardMove> boardMoves = getLegalMoves(team);
    for (auto it = boardMoves.begin(); it != boardMoves.end();) {
        if (doesMoveLeavePieceAttacked(*it)) {
            it = boardMoves.erase(it);
        } else {
            ++it;
        }
    }
    return boardMoves;
}

Team Board::getTeamOneImpl() const { 
    return teamOne;
}

Team Board::getTeamTwoImpl() const  { 
    return teamTwo;
}

Team Board::getOtherTeamImpl(Team team) const { 
    return team == teamOne ? teamTwo : teamOne; 
}

std::optional<BoardMove> Board::createBoardMoveImpl(BoardSquare const &fromSquare, BoardSquare const &toSquare, std::optional<PieceType> promotionPieceType) const { 
    if (!isSquareOnBoard(fromSquare)) {
        return std::nullopt;
    }

    std::vector<BoardMove> legalMoves = getLegalMovesAtSquare(fromSquare);
    auto it = std::find_if(legalMoves.begin(), legalMoves.end(), [&fromSquare, &toSquare, &promotionPieceType](BoardMove const &boardMove) {
        return
            fromSquare == boardMove.getFromSquare() &&
            toSquare == boardMove.getToSquare() &&
            promotionPieceType == boardMove.getPromotionPieceType();
    });
    return it != legalMoves.end() ? std::make_optional<BoardMove>(*it) : std::nullopt;
}

std::optional<BoardMove> Board::getLastCompletedMoveImpl() const {
    return completedMoves.empty() ? std::nullopt : std::make_optional<BoardMove>(completedMoves.back());
}

std::vector<BoardMove> const& Board::getAllCompletedMovesImpl() const {
    return completedMoves;
}

bool Board::makeMoveImpl(BoardMove const &move) {
    if (isMoveValid(move)) {
        makeMoveInternal(move);
        return true;
    }
    return false;                              
}

bool Board::undoMoveImpl() {
    // Check if there is a move to undo
    if (completedMoves.size() == 0) {
        return false;
    }

    BoardMove lastMove = completedMoves.back();      // Get the last made move
    completedMoves.pop_back();                      // Pop it off the completed moves stack
    lastMove.undoMove(*this);                       // Undo the move
    redoMoves.emplace_back(lastMove);               // Push it to the redo moves stack
    return true;      
}

bool Board::redoMoveImpl() {
    // Check if there is a move to redo
    if (redoMoves.size() == 0) {
        return false;
    }

    BoardMove lastUndoneMove = redoMoves.back();     // Get the last move to be undone
    redoMoves.pop_back();                           // Pop it off the redo moves stack
    lastUndoneMove.makeMove(*this);                 // Apply the move
    completedMoves.emplace_back(lastUndoneMove);    // Push it to the completed moves stack
    return true;                                    // Success
}

int Board::getNumRowsImpl() const {
    return grid.size();
}

int Board::getNumColsImpl() const {
    return grid[0].size();
}

bool Board::isInCheckImpl(Team team) const {
    for (BoardSquare const &boardSquare : allBoardSquares()) {
        std::optional<PieceInfo> pieceInfo = getPieceInfoAt(boardSquare);
        if (pieceInfo.has_value() && pieceInfo.value().pieceType == PieceType::KING && pieceInfo.value().team == team) {
            if (isSquareAttacked(boardSquare, team)) {
                return true;
            }
        }
    }
    return false;
}

bool Board::isInCheckMateImpl(Team team) const {
    return isInCheck(team) && !performMove(team);
}

bool Board::isInStaleMateImpl(Team team) const {
    return !performMove(team) && !isInCheck(team);
}
