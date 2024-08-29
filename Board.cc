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
    initializeBoard();
}

void Board::initializeBoard() {
    for (auto& row : grid) {
        for (auto& piece : row) {
            piece = ChessPieceFactory::createEmptyPiece();
        }
    }
}

std::vector<BoardMove> Board::getPseudoLegalMoves(Color color) const {
    std::vector<BoardMove> boardMoves;
    for (int row = 0; row < grid.size(); ++row) {
        for (int col = 0; col < grid[0].size(); ++col) {
            if (grid[row][col]->getPieceInfo().getPieceColor() == color) {
                std::vector<BoardMove> pieceMoves = grid[row][col]->getMoves(*this, BoardSquare(row, col), false);
                boardMoves.insert(boardMoves.end(), pieceMoves.begin(), pieceMoves.end());
            }
        }
    }
    return boardMoves;
}

std::vector<BoardMove> Board::getAllPseudoLegalAttackingMoves(Color color) const {
    std::vector<BoardMove> boardMoves;
    for (int row = 0; row < grid.size(); ++row) {
        for (int col = 0; col < grid[0].size(); ++col) {
            if (grid[row][col]->getPieceInfo().getPieceColor() == color) {
                std::vector<BoardMove> pieceMoves = grid[row][col]->getMoves(*this, BoardSquare(row, col), true);
                boardMoves.insert(boardMoves.end(), pieceMoves.begin(), pieceMoves.end());
            }  
        }
    }
    return boardMoves;
} 

bool Board::doesMoveApplyCheck(BoardMove const &boardMove) const {
    const_cast<Board*>(this)->makeMove(boardMove);
    bool isColorInCheck = isInCheck(oppositeColor(getPieceInfoAt(boardMove.getFromSquare()).getPieceColor()));
    const_cast<Board*>(this)->undoMove();
    return isColorInCheck;
}

bool Board::doesMoveCapturePiece(BoardMove const &boardMove) const {
    Color turnColor = getPieceInfoAt(boardMove.getFromSquare()).getPieceColor();
    Color attackedColor = getPieceInfoAt(boardMove.getCaptureSquare()).getPieceColor();
    return (attackedColor == oppositeColor(turnColor));
}

bool Board::doesMoveHavePieceAttackedAfter(BoardMove const &boardMove) const {
    Color turnColor = grid[boardMove.getFromSquare().getBoardRow()][boardMove.getFromSquare().getBoardCol()]->getPieceInfo().getPieceColor();
    const_cast<Board*>(this)->makeMove(boardMove);
    std::vector<BoardMove> boardMoves = getCapturingMoves(oppositeColor(turnColor));

    // Don't need to try every move if just two colours (I think) --> just check if capturingMoves.size() == 0
    for (BoardMove const &fMove : boardMoves) {
        if (getPieceInfoAt(fMove.getCaptureSquare()).getPieceColor() == turnColor) {
            const_cast<Board*>(this)->undoMove();
            return true;
        }
        const_cast<Board*>(this)->undoMove();
    }
    return false;
}

bool Board::canMakeMove(Color color) const {
    return getLegalMoves(color).size() > 0;
}

bool Board::isInCheckAfterMove(BoardMove const &boardMove) const {
    const_cast<Board*>(this)->makeMove(boardMove);
    bool isColorInCheck = isInCheck(getPieceInfoAt(boardMove.getFromSquare()).getPieceColor());
    const_cast<Board*>(this)->undoMove();
    return isColorInCheck;
} 

bool Board::isSquareOnBoard(int row, int col) const {
    return row >= 0 && row < grid.size() && col >= 0 && col < grid[row].size();
}


#pragma mark - ChessBoard Interface

PieceInfo Board::getPieceInfoAtImpl(BoardSquare const &boardSquare) const {
    return grid[boardSquare.getBoardRow()][boardSquare.getBoardCol()]->getPieceInfo();
}

bool Board::isEmptySquareOnBoardImpl(BoardSquare const &boardSquare) const {
    int boardRow = boardSquare.getBoardRow();
    int boardCol = boardSquare.getBoardCol();
    return isSquareOnBoard(boardRow, boardCol) && grid[boardRow][boardCol]->getPieceInfo().getPieceType() == PieceType::EMPTY;
}

bool Board::isOpposingColorOnBoardImpl(BoardSquare const &boardSquare, Color color) const {
    int boardRow = boardSquare.getBoardRow();
    int boardCol = boardSquare.getBoardCol();
    return isSquareOnBoard(boardRow, boardCol) && grid[boardRow][boardCol]->getPieceInfo().getPieceColor() != color && grid[boardRow][boardCol]->getPieceInfo().getPieceColor() != Color::NONE;
}

bool Board::isEmptySquareOrOpposingColorOnBoardImpl(BoardSquare const &boardSquare, Color color) const {
    int boardRow = boardSquare.getBoardRow();
    int boardCol = boardSquare.getBoardCol();
    return isSquareOnBoard(boardRow, boardCol) && grid[boardRow][boardCol]->getPieceInfo().getPieceColor() != color;
}

bool Board::isSquareCheckAttackedImpl(BoardSquare const &boardSquare, Color color) const {
    std::vector<BoardMove> boardMoves = getAllPseudoLegalAttackingMoves(oppositeColor(color));
    for (BoardMove const& boardMove : boardMoves) {
        if (boardMove.getCaptureSquare() == boardSquare) {
            return true;
        }
    }
    return false;
}

bool Board::isSquareOnCurrentBoardImpl(UserSquare const &userSquare) const { 
    int gridRow = userSquare.getBoardRow(getNumRows());
    int gridCol = userSquare.getBoardCol(getNumCols());
    return gridRow >= 0 && gridRow < getNumRows() && gridCol >= 0 && gridCol < getNumCols();
}

void Board::setPositionImpl(UserSquare const &userSquare, Color pieceColor, PieceType pieceType, PieceDirection pieceDirection, bool hasMoved, int pieceScore) {
    int boardRow = userSquare.getBoardRow(getNumRows());
    int boardCol = userSquare.getBoardCol(getNumCols());
    BoardSquare boardSquare(boardRow, boardCol);
    setPosition(boardSquare, pieceColor, pieceType, pieceDirection, hasMoved, pieceScore);
}

void Board::setPositionImpl(BoardSquare const &boardSquare, Color pieceColor, PieceType pieceType, PieceDirection pieceDirection, bool hasMoved, int pieceScore) {
    int boardRow = boardSquare.getBoardRow();
    int boardCol = boardSquare.getBoardCol();
    grid[boardRow][boardCol] = ChessPieceFactory::createPiece(pieceColor, pieceType, pieceDirection, hasMoved, pieceScore);
}

bool Board::clearPositionImpl(UserSquare const &userSquare) {
    int boardRow = userSquare.getBoardRow(getNumRows());
    int boardCol = userSquare.getBoardCol(getNumCols());
    BoardSquare boardSquare(boardRow, boardCol);
    return clearPosition(boardSquare);
}

bool Board::clearPositionImpl(BoardSquare const &boardSquare) {
    int boardRow = boardSquare.getBoardRow();
    int boardCol = boardSquare.getBoardCol();
    if (grid[boardRow][boardCol]->getPieceInfo().getPieceType() == PieceType::EMPTY) {
        return false;
    }
    else {
        grid[boardRow][boardCol] = ChessPieceFactory::createEmptyPiece();
        return true;
    }
}

void Board::clearBoardImpl() {
    for (int boardRow = 0; boardRow < getNumRows(); ++boardRow) {
        for (int boardCol = 0; boardCol < getNumCols(); ++boardCol) {
            grid[boardRow][boardCol] = ChessPieceFactory::createEmptyPiece();
        }
    }
    completedMoves.clear();
}

void Board::swapPositionsImpl(BoardSquare const &boardSquareOne, BoardSquare const &boardSquareTwo) {
    int boardRowOne = boardSquareOne.getBoardRow();
    int boardColOne = boardSquareOne.getBoardCol();
    int boardRowTwo = boardSquareTwo.getBoardRow();
    int boardColTwo = boardSquareTwo.getBoardCol();
    std::swap(grid[boardRowOne][boardColOne], grid[boardRowTwo][boardColTwo]);
}

void Board::setHasMovedImpl(BoardSquare const &boardSquare, bool hasMoved) {
    int boardRow = boardSquare.getBoardRow();
    int boardCol = boardSquare.getBoardCol();
    grid[boardRow][boardCol]->getPieceInfo().setHasMoved(hasMoved);
}

bool Board::setBoardSizeImpl(int newNumRows, int newNumCols) { 
    if (newNumRows >= 8 && newNumRows <= maxRows && newNumCols >= 8 && newNumCols <= maxCols) {
        int oldNumRows = grid.size();
        int oldNumCols = oldNumRows > 0 ? grid[0].size() : 0;

        // Create a new grid with the desired size
        std::vector<std::vector<std::unique_ptr<Piece>>> newGrid(newNumRows);

        for (int row = 0; row < newNumRows; ++row) {
            newGrid[row].resize(newNumCols);
        }

        // Copy existing pieces to the new grid, focusing on the bottom-left portion
        int rowOffset = std::max(0, oldNumRows - newNumRows);
        int colOffset = 0; // Always start from the first column to preserve bottom-left

        for (int row = 0; row < newNumRows; ++row) {
            for (int col = 0; col < newNumCols; ++col) {
                if (row + rowOffset < oldNumRows && col + colOffset < oldNumCols) {
                    newGrid[row][col] = std::move(grid[row + rowOffset][col + colOffset]);
                } else {
                    newGrid[row][col] = ChessPieceFactory::createEmptyPiece();
                }
            }
        }

        // Replace the old grid with the new grid
        grid = std::move(newGrid);
    
        return true;
    } else {
        return false;
    }
}

void Board::applyStandardSetupImpl() {
    clearBoard();
 
    int startCol = (grid[0].size() - 8) / 2;

    int topRow = 0;                     // Black
    int bottomRow = grid.size() - 1;    // White
    for (int col = startCol; col < startCol + 8; ++col) {
        
        // Normal Pieces
        PieceType pieceType;
        if (col == startCol || col == startCol + 8 - 1) {
            // Rook
            pieceType = PieceType::ROOK;
        } else if (col == startCol + 1 || col == startCol + 8 - 2) {
            // Knight
            pieceType = PieceType::KNIGHT;
        } else if (col == startCol + 2 || col == startCol + 8 - 3) {
            // Bishop
            pieceType = PieceType::BISHOP;
        } else if (col == startCol + 3) {
            // Queen
            pieceType = PieceType::QUEEN;
        } else if (col == startCol + 4) {
            // King
            pieceType = PieceType::KING;
        }
        BoardSquare blackPieceSquare(topRow, col);
        BoardSquare whitePieceSquare(bottomRow, col);
        setPosition(blackPieceSquare, Color::BLACK, pieceType, PieceDirection::SOUTH, false);               // Black
        setPosition(whitePieceSquare, Color::WHITE, pieceType, PieceDirection::NORTH, false);            // White

        // Pawns
        BoardSquare blackPawnSquare(topRow + 1, col);
        BoardSquare whitePawnSquare(bottomRow - 1, col);
        setPosition(blackPawnSquare, Color::BLACK, PieceType::PAWN, PieceDirection::SOUTH, false);     // Black
        setPosition(whitePawnSquare, Color::WHITE, PieceType::PAWN, PieceDirection::NORTH, false);  // Black
    }
}

std::vector<BoardMove> Board::getLegalMovesImpl(Color color) const { 
    std::vector<BoardMove> boardMoves = getPseudoLegalMoves(color);
    for (auto it = boardMoves.begin(); it != boardMoves.end();) {
        if (isInCheckAfterMove(*it)) {
            it = boardMoves.erase(it);
        } else {
            ++it;
        }
    }
    return boardMoves;
}

std::vector<BoardMove> Board::getCapturingMovesImpl(Color color) const { 
    std::vector<BoardMove> boardMoves = getLegalMoves(color);
    for (auto it = boardMoves.begin(); it != boardMoves.end();) {
        if (!doesMoveCapturePiece(*it)) {
            it = boardMoves.erase(it);
        } else {
            ++it;
        }
    }
    return boardMoves;
}

std::vector<BoardMove> Board::getCheckApplyingMovesImpl(Color color) const {
    std::vector<BoardMove> boardMoves = getLegalMoves(color);
    for (auto it = boardMoves.begin(); it != boardMoves.end();) {
        if (!doesMoveApplyCheck(*it)) {
            it = boardMoves.erase(it);
        } else {
            ++it;
        }
    }
    return boardMoves;
}

std::vector<BoardMove> Board::getCaptureAvoidingMovesImpl(Color color) const { 
    std::vector<BoardMove> boardMoves = getLegalMoves(color);
    for (auto it = boardMoves.begin(); it != boardMoves.end();) {
        if (doesMoveHavePieceAttackedAfter(*it)) {
            it = boardMoves.erase(it);
        } else {
            ++it;
        }
    }
    return boardMoves;
}

Color Board::getColorOneImpl() const { 
    return colorOne;
}

Color Board::getColorTwoImpl() const  { 
    return colorTwo;
}

Color Board::oppositeColorImpl(Color color) const { 
    return color == colorOne ? colorTwo : colorOne; 
}

std::unique_ptr<BoardMove> Board::generateBoardMoveImpl(UserMove const &userMove) const { 
    int boardFromRow = userMove.getFromSquare().getBoardRow(getNumRows());
    int boardFromCol = userMove.getFromSquare().getBoardCol(getNumCols());
    std::vector<BoardMove> legalMoves = getLegalMoves(grid[boardFromRow][boardFromCol]->getPieceInfo().getPieceColor());
    auto it = std::find_if(legalMoves.begin(), legalMoves.end(), [this, &userMove](BoardMove const &boardMove) {
        return 
            userMove.getFromSquare().getBoardRow(getNumRows()) == boardMove.getFromSquare().getBoardRow() &&
            userMove.getFromSquare().getBoardCol(getNumCols()) == boardMove.getFromSquare().getBoardCol() && 
            userMove.getToSquare().getBoardRow(getNumRows()) == boardMove.getToSquare().getBoardRow() &&
            userMove.getToSquare().getBoardCol(getNumCols()) == boardMove.getToSquare().getBoardCol() &&
            userMove.getPromotionPieceType() == boardMove.getPromotionPieceType();
    });
    return it != legalMoves.end() ? std::make_unique<BoardMove>(*it) : nullptr;
}

BoardMove const& Board::getLastMoveImpl() const {
    return completedMoves.back();
}

bool Board::hasMoveBeenMadeImpl() const {
    return completedMoves.size() > 0;
}

void Board::makeMoveImpl(BoardMove const &move) {
    move.makeMove(*this);                               // Apply the move
    completedMoves.emplace_back(std::move(move));       // Track it for undoing 
    redoMoves.clear();                                      // Clear redo moves (can't redo after making a move)
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

bool Board::isInCheckImpl(Color color) const {
    for (int row = 0; row < grid.size(); ++row) {
        for (int col = 0; col < grid[0].size(); ++col) {
            if (grid[row][col]->getPieceInfo().getPieceType() == PieceType::KING && grid[row][col]->getPieceInfo().getPieceColor() == color) {
                if (isSquareCheckAttacked(BoardSquare(row, col), color)) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool Board::isInCheckMateImpl(Color color) const {
    return isInCheck(color) && !canMakeMove(color);
}

bool Board::isInStaleMateImpl(Color color) const {
    return !canMakeMove(color) && !isInCheck(color);
}

bool Board::isInStaleMateImpl() const {
    return (isInStaleMate(colorOne) || isInStaleMate(colorTwo));
}
bool Board::hasGameFinishedImpl() const {
    return (isInStaleMate() || isInCheckMate(colorOne) || isInCheckMate(colorTwo));
}
bool Board::isBoardInValidStateImpl() const {
    int whiteKingCount = 0;
    int blackKingCount = 0;

    int topRow = 0;
    int bottomRow = grid.size() - 1;

    for (int row = 0; row < grid.size(); ++row) {
        for (int col = 0; col < grid[0].size(); ++col) {
            if (grid[row][col]->getPieceInfo().getPieceType() == PieceType::KING) {
                Color pieceColor = grid[row][col]->getPieceInfo().getPieceColor();
                if (isSquareCheckAttacked(BoardSquare(row, col), pieceColor)) {
                    return false;
                }

                if (pieceColor == colorOne) {
                    whiteKingCount++;
                } else if (pieceColor == colorTwo) {
                    blackKingCount++;
                }
            }

            if ((row == topRow || row == bottomRow) && grid[row][col]->getPieceInfo().getPieceType() == PieceType::PAWN) {
                return false;
            }
        }
    }

    return (whiteKingCount != 1 || blackKingCount != 1) ? false : true;
}




std::vector<std::pair<std::string, std::string>> Board::getMatchingOpeningsImpl() const { 
    return standardOpeningTrie.getMatchingOpenings(completedMoves);
}

int Board::getAlphaBetaBoardScoreImpl(Color color) const {
    int totalScore = 0;
    for (int row = 0; row < grid.size(); ++row) {
        for (int col = 0; col < grid[0].size(); ++col) {

            if (grid[row][col]->getPieceInfo().getPieceColor() == colorOne) {
                totalScore += grid[row][col]->getPieceInfo().getPieceScore() * 10;
                // Advance bonus, only until row before pawns so no stupid sacrifice
                switch (grid[row][col]->getPieceInfo().getPieceDirection()) {
                    case PieceDirection::NORTH:
                        totalScore += min(grid.size() - 1 - row, grid.size() - 4);
                        break;
                    case PieceDirection::SOUTH:
                        totalScore += min(grid.size(), grid.size() - 4);
                        break;
                    case PieceDirection::EAST:
                        totalScore += min(grid[0].size() - 1 - col, grid[0].size() - 4);
                        break;
                    case PieceDirection::WEST:
                        totalScore += min(grid[0].size(), grid[0].size() - 4);
                        break;
                    default:
                        break;
                }
            } else if (grid[row][col]->getPieceInfo().getPieceColor() == colorTwo) {
                totalScore -= grid[row][col]->getPieceInfo().getPieceScore() * 10;
                // Advance bonus, only until row before pawns so no stupid sacrifice
                switch (grid[row][col]->getPieceInfo().getPieceDirection()) {
                    case PieceDirection::NORTH:
                        totalScore -= min(grid.size() - 1 - row, grid.size() - 4);
                        break;
                    case PieceDirection::SOUTH:
                        totalScore -= min(grid.size(), grid.size() - 4);
                        break;
                    case PieceDirection::EAST:
                        totalScore -= min(grid[0].size() - 1 - col, grid[0].size() - 4);
                        break;
                    case PieceDirection::WEST:
                        totalScore -= min(grid[0].size(), grid[0].size() - 4);
                        break;
                    default:
                        break;
                }
            }
        }
    }

    // Checkmate
    if (isInCheckMate(color)) {
        if (color == colorTwo) {
            totalScore += 1000;
        } else {
            totalScore -= 1000;
        }
    }

    return totalScore;
}
