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
            piece = ChessPieceFactory::createEmptyPiece();
        }
    }
}

std::vector<BoardMove> Board::getPseudoLegalMoves(Color color) const {
    std::vector<BoardMove> boardMoves;
    for (BoardSquare const &boardSquare : allBoardSquares()) {
        if (getPieceInfoAt(boardSquare).pieceColor == color) {
            std::vector<BoardMove> pieceMoves = getPieceMovesAtSquare(boardSquare, false);
            boardMoves.insert(boardMoves.end(), pieceMoves.begin(), pieceMoves.end());
        }
    }
    return boardMoves;
}

std::vector<BoardMove> Board::getAllPseudoLegalAttackingMoves(Color color) const {
    std::vector<BoardMove> boardMoves;
    for (BoardSquare const &boardSquare : allBoardSquares()) {
        if (getPieceInfoAt(boardSquare).pieceColor == color) {
            std::vector<BoardMove> pieceMoves = getPieceMovesAtSquare(boardSquare, true);
            boardMoves.insert(boardMoves.end(), pieceMoves.begin(), pieceMoves.end());
        }
    }
    return boardMoves;
} 

bool Board::doesMoveApplyCheck(BoardMove const &boardMove) const {
    Color turnColor = getPieceInfoAt(boardMove.getFromSquare()).pieceColor;
    const_cast<Board*>(this)->makeMove(boardMove);
    bool doesMoveApplyCheck = isInCheck(oppositeColor(turnColor));
    const_cast<Board*>(this)->undoMove();
    return doesMoveApplyCheck;
}

bool Board::doesMoveCapturePiece(BoardMove const &boardMove) const {
    Color turnColor = getPieceInfoAt(boardMove.getFromSquare()).pieceColor;
    Color attackedColor = getPieceInfoAt(boardMove.getCaptureSquare()).pieceColor;
    return 
        attackedColor != turnColor && 
        attackedColor != Color::NONE;
}

bool Board::doesMoveHavePieceAttackedAfter(BoardMove const &boardMove) const {
    Color turnColor = getPieceInfoAt(boardMove.getFromSquare()).pieceColor;
    const_cast<Board*>(this)->makeMove(boardMove);
    std::vector<BoardMove> opponentMoves = getCapturingMoves(oppositeColor(turnColor));

    // Don't need to try every move if just two colours (I think) --> just check if capturingMoves.size() == 0
    for (BoardMove const &opponentMove : opponentMoves) {
        if (getPieceInfoAt(opponentMove.getCaptureSquare()).pieceColor == turnColor) {
            const_cast<Board*>(this)->undoMove();
            return true;
        }
        
    }
    const_cast<Board*>(this)->undoMove();
    return false;
}

bool Board::canMakeMove(Color color) const {
    return getLegalMoves(color).size() > 0;
}

bool Board::isInCheckAfterMove(BoardMove const &boardMove) const {
    Color turnColor = getPieceInfoAt(boardMove.getFromSquare()).pieceColor;
    const_cast<Board*>(this)->makeMove(boardMove);
    bool isInCheckAfterMove = isInCheck(turnColor);
    const_cast<Board*>(this)->undoMove();
    return isInCheckAfterMove;
} 

std::vector<BoardMove> Board::getPieceMovesAtSquare(BoardSquare const &boardSquare, bool onlyAttackingMoves) const {
    return grid[boardSquare.getBoardRow()][boardSquare.getBoardCol()]->getMoves(*this, boardSquare, onlyAttackingMoves);
}


#pragma mark - ChessBoard Interface

PieceInfo Board::getPieceInfoAtImpl(BoardSquare const &boardSquare) const {
    return grid[boardSquare.getBoardRow()][boardSquare.getBoardCol()]->getPieceInfo();
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

bool Board::isEmptySquareOnBoardImpl(BoardSquare const &boardSquare) const {
    return isSquareOnBoard(boardSquare) && getPieceInfoAt(boardSquare).pieceType == PieceType::EMPTY;
}

bool Board::isOpposingColorOnBoardImpl(BoardSquare const &boardSquare, Color color) const {
    return isSquareOnBoard(boardSquare) && getPieceInfoAt(boardSquare).pieceColor != color && getPieceInfoAt(boardSquare).pieceColor != Color::NONE;
}

bool Board::isEmptySquareOrOpposingColorOnBoardImpl(BoardSquare const &boardSquare, Color color) const {
    return isSquareOnBoard(boardSquare) && getPieceInfoAt(boardSquare).pieceColor != color;
}

bool Board::isSquareAttackedImpl(BoardSquare const &boardSquare, Color color) const {
    std::vector<BoardMove> boardMoves = getAllPseudoLegalAttackingMoves(oppositeColor(color));
    for (BoardMove const& boardMove : boardMoves) {
        if (boardMove.getCaptureSquare() == boardSquare) {
            return true;
        }
    }
    return false;
}

bool Board::isSquareOnBoardImpl(BoardSquare const &boardSquare) const {
    int boardRow = boardSquare.getBoardRow();
    int boardCol = boardSquare.getBoardCol();
    return boardRow >= 0 && boardRow < grid.size() && boardCol >= 0 && boardCol < grid[boardRow].size();
}

bool Board::isSquareOnBoardImpl(UserSquare const &userSquare) const { 
    return isSquareOnBoard(userSquare.toBoardSquare(getNumRows(), getNumCols()));
}

void Board::setPositionImpl(UserSquare const &userSquare, Color pieceColor, PieceType pieceType, PieceDirection pieceDirection, bool hasMoved, int pieceScore) {
    setPosition(userSquare.toBoardSquare(getNumRows(), getNumCols()), pieceColor, pieceType, pieceDirection, hasMoved, pieceScore);
}

void Board::setPositionImpl(BoardSquare const &boardSquare, Color pieceColor, PieceType pieceType, PieceDirection pieceDirection, bool hasMoved, int pieceScore) {
    grid[boardSquare.getBoardRow()][boardSquare.getBoardCol()] = ChessPieceFactory::createPiece(pieceColor, pieceType, pieceDirection, hasMoved, pieceScore);
}

bool Board::clearPositionImpl(UserSquare const &userSquare) {
    return clearPosition(userSquare.toBoardSquare(getNumRows(), getNumCols()));
}

bool Board::clearPositionImpl(BoardSquare const &boardSquare) {
    if (getPieceInfoAt(boardSquare).pieceType == PieceType::EMPTY) {
        return false;
    } else {
        grid[boardSquare.getBoardRow()][boardSquare.getBoardCol()] = ChessPieceFactory::createEmptyPiece();
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
    grid[boardRow][boardCol]->setHasMoved(hasMoved);
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
    std::vector<BoardMove> legalMoves = getLegalMoves(getPieceInfoAt(userMove.getFromSquare().toBoardSquare(getNumRows(), getNumCols())).pieceColor);
    auto it = std::find_if(legalMoves.begin(), legalMoves.end(), [this, &userMove](BoardMove const &boardMove) {
        return userMove.isEqualToBoardMove(boardMove, getNumRows(), getNumCols());
    });
    return it != legalMoves.end() ? std::make_unique<BoardMove>(*it) : nullptr;
}

BoardMove const& Board::getLastMadeMoveImpl() const {
    return completedMoves.back();
}

std::vector<BoardMove> const& Board::getAllMadeMovesImpl() const {
    return completedMoves;
}

bool Board::hasMoveBeenMadeImpl() const {
    return completedMoves.size() > 0;
}

void Board::makeMoveImpl(BoardMove const &move) {
    move.makeMove(*this);                               // Apply the move
    completedMoves.emplace_back(move);                  // Track it for undoing 
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

// TODO: Need max col
int Board::getNumColsImpl() const {
    return grid[0].size();
}

bool Board::isInCheckImpl(Color color) const {
    for (BoardSquare const &boardSquare : allBoardSquares()) {
        if (getPieceInfoAt(boardSquare).pieceType == PieceType::KING && getPieceInfoAt(boardSquare).pieceColor == color) {
            if (isSquareAttacked(boardSquare, color)) {
                return true;
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

    for (BoardSquare const &boardSquare : allBoardSquares()) {
        if (getPieceInfoAt(boardSquare).pieceType == PieceType::KING) {
            Color pieceColor = getPieceInfoAt(boardSquare).pieceColor;
            if (isSquareAttacked(boardSquare, pieceColor)) {
                return false;
            }
            if (pieceColor == colorOne) {
                whiteKingCount++;
            } else if (pieceColor == colorTwo) {
                blackKingCount++;
            }
        }

        if (getPieceInfoAt(boardSquare).pieceType == PieceType::PAWN && (boardSquare.getBoardRow() == topRow || boardSquare.getBoardRow() == bottomRow)) {
            return false;
        }
    }

    return (whiteKingCount != 1 || blackKingCount != 1) ? false : true;
}
