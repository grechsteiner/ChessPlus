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
#include "FullMove.h"
#include "Square.h"


#pragma mark - Board Game Interface


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
            if (grid[row][col]->getPieceType() == PieceType::KING) {
                Color pieceColor = grid[row][col]->getPieceColor();
                if (isSquareCheckAttacked(row, col, pieceColor)) {
                    return false;
                }

                if (pieceColor == colorOne) {
                    whiteKingCount++;
                } else if (pieceColor == colorTwo) {
                    blackKingCount++;
                }
            }

            if ((row == topRow || row == bottomRow) && grid[row][col]->getPieceType() == PieceType::PAWN) {
                return false;
            }
        }
    }

    return (whiteKingCount != 1 || blackKingCount != 1) ? false : true;
}

void Board::setPositionImpl(int row, char col, Color pieceColor, PieceType pieceType, PieceDirection pieceDirection, bool hasMoved, int pieceScore) {
    int vectorRow = grid.size() - row;
    int vectorCol = col - 'a';
    setPosition(vectorRow, vectorCol, pieceColor, pieceType, pieceDirection, hasMoved, pieceScore);
}
bool Board::clearPositionImpl(int row, char col) {
    int vectorRow = grid.size() - row;
    int vectorCol = col - 'a';
    return clearPosition(vectorRow, vectorCol);
}
void Board::clearBoardImpl() {
    for (int row = 0; row < grid.size(); ++row) {
        for (int col = 0; col < grid[0].size(); ++col) {
            grid[row][col] = ChessPieceFactory::createEmptyPiece();
        }
    }
    completedMoves.clear();
}

bool Board::isSquareOnBoardImpl(int row, char col) const { 
    int vectorRow = grid.size() - row;
    int vectorCol = col - 'a';
    return vectorRow >= 0 && vectorRow < grid.size() && vectorCol >= 0 && vectorCol < grid[vectorRow].size();
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
        setPosition(topRow, col, Color::BLACK, pieceType, PieceDirection::SOUTH, false);               // Black
        setPosition(bottomRow, col, Color::WHITE, pieceType, PieceDirection::NORTH, false);            // White

        // Pawns
        setPosition(topRow + 1, col, Color::BLACK, PieceType::PAWN, PieceDirection::SOUTH, false);     // Black
        setPosition(bottomRow - 1, col, Color::WHITE, PieceType::PAWN, PieceDirection::NORTH, false);  // Black
    }
}

std::unique_ptr<FullMove> Board::generateFullMoveImpl(UserEnteredMove const &userEnteredMove) const { 
    std::vector<FullMove> legalMoves = getLegalMoves(grid[Square::getGridRow(userEnteredMove.getFromRow(), grid.size())][Square::getGridCol(userEnteredMove.getFromCol(), grid[0].size())]->getPieceColor());
    auto it = std::find_if(legalMoves.begin(), legalMoves.end(), [this, &userEnteredMove](FullMove const &fullMove) {
        return isUserEqualToFull(fullMove, userEnteredMove, grid.size(), grid[0].size());
    });
    return it != legalMoves.end() ? std::make_unique<FullMove>(*it) : nullptr;
}
//void makeMoveImpl(FullMove const &move) override;                    
//bool undoMoveImpl() override;            
bool Board::redoMoveImpl() {
    // Check if there is a move to redo
    if (redoMoves.size() == 0) {
        return false;
    }

    FullMove lastUndoneMove = redoMoves.back();     // Get the last move to be undone
    redoMoves.pop_back();                           // Pop it off the redo moves stack
    lastUndoneMove.makeMove(*this);                 // Apply the move
    completedMoves.emplace_back(lastUndoneMove);    // Push it to the completed moves stack
    return true;                                    // Success
}


#pragma mark - Board Display Interface

int Board::getNumRowsImpl() const { return grid.size(); }
int Board::getNumColsImpl() const { return grid[0].size(); }

// Piece const& Board::getPieceAtImpl(int row, int col) const = 0;
std::vector<std::pair<std::string, std::string>> Board::getMatchingOpeningsImpl() const { 
    return standardOpeningTrie.getMatchingOpenings(completedMoves);
}

bool Board::isInCheckImpl(Color color) const {
    for (int row = 0; row < grid.size(); ++row) {
        for (int col = 0; col < grid[0].size(); ++col) {
            if (grid[row][col]->getPieceType() == PieceType::KING && grid[row][col]->getPieceColor() == color) {
                if (isSquareCheckAttacked(row, col, color)) {
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
//bool Board::isInStaleMateImpl(Color color) const { return isInStaleMate(color); }


#pragma mark - Board Computer Interface

std::vector<FullMove> Board::getLegalMovesImpl(Color color) const { 
    std::vector<FullMove> fullMoves = getPseudoLegalMoves(color);
    for (auto it = fullMoves.begin(); it != fullMoves.end();) {
        if (isInCheckAfterMove(*it)) {
            it = fullMoves.erase(it);
        } else {
            ++it;
        }
    }
    return fullMoves;
}
std::vector<FullMove> Board::getCapturingMovesImpl(Color color) const { 
    std::vector<FullMove> fullMoves = getLegalMoves(color);
    for (auto it = fullMoves.begin(); it != fullMoves.end();) {
        if (!doesMoveCapturePiece(*it)) {
            it = fullMoves.erase(it);
        } else {
            ++it;
        }
    }
    return fullMoves;
}
std::vector<FullMove> Board::getCheckApplyingMovesImpl(Color color) const {
    std::vector<FullMove> fullMoves = getLegalMoves(color);
    for (auto it = fullMoves.begin(); it != fullMoves.end();) {
        if (!doesMoveApplyCheck(*it)) {
            it = fullMoves.erase(it);
        } else {
            ++it;
        }
    }
    return fullMoves;
}
std::vector<FullMove> Board::getCaptureAvoidingMovesImpl(Color color) const { 
    std::vector<FullMove> fullMoves = getLegalMoves(color);
    for (auto it = fullMoves.begin(); it != fullMoves.end();) {
        if (doesMoveHavePieceAttackedAfter(*it)) {
            it = fullMoves.erase(it);
        } else {
            ++it;
        }
    }
    return fullMoves;
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

void Board::makeMoveImpl(FullMove const &move) {
    move.makeMove(*this);                               // Apply the move
    completedMoves.emplace_back(std::move(move));       // Track it for undoing 
    redoMoves.clear();                                      // Clear redo moves (can't redo after making a move)
}
bool Board::undoMoveImpl() {
    // Check if there is a move to undo
    if (completedMoves.size() == 0) {
        return false;
    }

    FullMove lastMove = completedMoves.back();      // Get the last made move
    completedMoves.pop_back();                      // Pop it off the completed moves stack
    lastMove.undoMove(*this);                       // Undo the move
    redoMoves.emplace_back(lastMove);               // Push it to the redo moves stack
    return true;      
}

// Piece const& Board::getPieceAtImpl(int row, int col) const;
bool Board::isInStaleMateImpl(Color color) const {
    return !canMakeMove(color) && !isInCheck(color);
}
int Board::getAlphaBetaBoardScoreImpl(Color color) const {
    int totalScore = 0;
    for (int row = 0; row < grid.size(); ++row) {
        for (int col = 0; col < grid[0].size(); ++col) {

            if (grid[row][col]->getPieceColor() == colorOne) {
                totalScore += grid[row][col]->getPieceScore() * 10;
                // Advance bonus, only until row before pawns so no stupid sacrifice
                switch (grid[row][col]->getPieceDirection()) {
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
            } else if (grid[row][col]->getPieceColor() == colorTwo) {
                totalScore -= grid[row][col]->getPieceScore() * 10;
                // Advance bonus, only until row before pawns so no stupid sacrifice
                switch (grid[row][col]->getPieceDirection()) {
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

#pragma mark - Board Move Interface

void Board::setPositionImpl(int row, int col, Color pieceColor, PieceType pieceType, PieceDirection pieceDirection, bool hasMoved, int pieceScore) {
    grid[row][col] = ChessPieceFactory::createPiece(pieceColor, pieceType, pieceDirection, hasMoved, pieceScore);
}

void Board::clearPositionImpl(int row, int col) {
    if (grid[row][col]->getPieceType() == PieceType::EMPTY) {
        return false;
    }
    else {
        grid[row][col] = ChessPieceFactory::createEmptyPiece();
        return true;
    }
}

void Board::swapPositionsImpl(int rowOne, int colOne, int rowTwo, int colTwo) {
    std::swap(grid[rowOne][colOne], grid[rowTwo][colTwo]);
}

void Board::setHasMovedImpl(int row, int col, bool hasMoved) {
    grid[row][col]->setHasMoved(hasMoved);
}


#pragma mark - Basic Board

Board::Board() 
    : grid(8), context(std::make_unique<Context>(*this)) {
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




#pragma mark - BoardPieceInterface

Piece const& Board::getPieceAtImpl(int row, int col) const {
    return *(grid[row][col]);
}

bool Board::isEmptySquareOnBoardImplementation(int row, int col) const {
    return isSquareOnBoard(row, col) && grid[row][col]->getPieceType() == PieceType::EMPTY;
}

bool Board::isOpposingColorOnBoardImplementation(int row, int col, Color color) const {
    return isSquareOnBoard(row, col) && grid[row][col]->getPieceColor() != color && grid[row][col]->getPieceColor() != Color::NONE;
}

bool Board::isEmptySquareOrOpposingColorOnBoardImplementation(int row, int col, Color color) const {
    return isSquareOnBoard(row, col) && grid[row][col]->getPieceColor() != color;
}

bool Board::isSquareCheckAttackedImplementation(int attackedRow, int attackedCol, Color color) const {
    std::vector<FullMove> fullMoves = getAllPseudoLegalAttackingMoves(oppositeColor(color));
    for (FullMove const& fullMove : fullMoves) {
        if (fullMove.getCaptureRow() == attackedRow && fullMove.getCaptureCol() == attackedCol) {
            return true;
        }
    }
    return false;
}

bool Board::hasMoveBeenMadeImplementation() const {
    return completedMoves.size() > 0;
}

FullMove const& Board::getLastMoveImplementation() const {
    return completedMoves.back();
}

int Board::getNumRowsImplementation() const {
    return grid.size();
}

int Board::getNumColsImplementation() const {
    return grid[0].size();
}

bool Board::isSquareOnBoard(int row, int col) const {
    return row >= 0 && row < grid.size() && col >= 0 && col < grid[row].size();
}

bool Board::doesMoveApplyCheck(FullMove const &fullMove) const {
    const_cast<Board*>(this)->makeMove(fullMove);
    bool isColorInCheck = isInCheck(oppositeColor(grid[fullMove.getFromRow()][fullMove.getFromCol()]->getPieceColor()));
    const_cast<Board*>(this)->undoMove();
    return isColorInCheck;
}

bool Board::doesMoveCapturePiece(FullMove const &fullMove) const {
    Color turnColor = grid[fullMove.getFromRow()][fullMove.getFromCol()]->getPieceColor();
    Color attackedColor = grid[fullMove.getCaptureRow()][fullMove.getCaptureCol()]->getPieceColor();
    return (attackedColor == oppositeColor(turnColor));
}

bool Board::doesMoveHavePieceAttackedAfter(FullMove const &fullMove) const {
    Color turnColor = grid[fullMove.getFromRow()][fullMove.getFromCol()]->getPieceColor();
    const_cast<Board*>(this)->makeMove(fullMove);
    std::vector<FullMove> fullMoves = getCapturingMoves(oppositeColor(turnColor));

    // Don't need to try every move if just two colours (I think) --> just check if capturingMoves.size() == 0
    for (FullMove const &fMove : fullMoves) {
        if (grid[fMove.getCaptureRow()][fMove.getCaptureCol()]->getPieceColor() == turnColor) {
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

bool Board::isInCheckAfterMove(FullMove const &fullMove) const {
    const_cast<Board*>(this)->makeMove(fullMove);
    bool isColorInCheck = isInCheck(grid[fullMove.getFromRow()][fullMove.getFromCol()]->getPieceColor());
    const_cast<Board*>(this)->undoMove();
    return isColorInCheck;
} 

std::vector<FullMove> Board::getPseudoLegalMoves(Color color) const {
    std::vector<FullMove> fullMoves;
    for (int row = 0; row < grid.size(); ++row) {
        for (int col = 0; col < grid[0].size(); ++col) {
            if (grid[row][col]->getPieceColor() == color) {
                std::vector<FullMove> pieceMoves = grid[row][col]->getMoves(*this, row, col, false);
                fullMoves.insert(fullMoves.end(), pieceMoves.begin(), pieceMoves.end());
            }
        }
    }
    return fullMoves;
}

std::vector<FullMove> Board::getAllPseudoLegalAttackingMoves(Color color) const {
    std::vector<FullMove> fullMoves;
    for (int row = 0; row < grid.size(); ++row) {
        for (int col = 0; col < grid[0].size(); ++col) {
            if (grid[row][col]->getPieceColor() == color) {
                std::vector<FullMove> pieceMoves = grid[row][col]->getMoves(*this, row, col, true);
                fullMoves.insert(fullMoves.end(), pieceMoves.begin(), pieceMoves.end());
            }  
        }
    }
    return fullMoves;
} 
