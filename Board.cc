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
#include "CompletedMove.h"
#include "ChessPieceFactory.h"

Board::Board() 
    : grid(8) {
    for (auto& row : grid) {
        row.resize(8);
    }
    initializeBoard();
}

Color Board::oppositeColor(Color color) const {
    return color == colorOne ? colorTwo : colorOne;
}

Color Board::getColorOne() const {
    return colorOne;
}

Color Board::getColorTwo() const {
    return colorTwo;
}

void Board::initializeBoard() {
    for (auto& row : grid) {
        for (auto& piece : row) {
            piece = ChessPieceFactory::createEmptyPiece();
        }
    }
}

std::vector<std::pair<std::string, std::string>> Board::getMatchingOpenings() const {
    return standardOpeningTrie.getMatchingOpenings(completedMoves);
}


bool Board::setBoardSize(int newNumRows, int newNumCols) {
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



#pragma mark - BoardPieceInterface
const std::unique_ptr<Piece>& Board::getPieceAtImplementation(int row, int col) const {
    return grid[row][col];
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
    std::vector<Move> moves = getAllPseudoLegalAttackingMoves(oppositeColor(color));
    for (const Move& move : moves) {
        CompletedMove completed(move, grid);
        int capturedRow = completed.getVectorRow(grid.size(), completed.getCapturedRow());
        int capturedCol = completed.getVectorCol(completed.getCapturedCol());
        if (capturedRow == attackedRow && capturedCol == attackedCol) {
            return true;
        }
    }
    return false;
}

bool Board::lastMoveImplementation() const {
    return completedMoves.size() > 0;
}

const CompletedMove& Board::getLastMoveImplementation() const {
    return completedMoves.back();
}

int Board::getNumRowsImplementation() const {
    return grid.size();
}

int Board::getNumColsImplementation() const {
    return grid[0].size();
}

bool Board::isSquareOnBoard(int row, char col) const {
    int vectorRow = grid.size() - row;
    int vectorCol = col - 'a';
    return vectorRow >= 0 && vectorRow < grid.size() && vectorCol >= 0 && vectorCol < grid[vectorRow].size();
}

bool Board::isSquareOnBoard(int row, int col) const {
    return row >= 0 && row < grid.size() && col >= 0 && col < grid[row].size();
}

bool Board::doesMoveApplyCheck(Move const &move) const {
    Color turnColor = grid[move.getVectorRow(grid.size(), move.getFromRow())][move.getVectorCol(move.getFromCol())]->getPieceColor();
    const_cast<Board*>(this)->makeMove(move);
    if (isInCheck(oppositeColor(turnColor))) {
        const_cast<Board*>(this)->undoMove();
        return true;
    }
    const_cast<Board*>(this)->undoMove();
    return false;
}

bool Board::doesMoveCapturePiece(Move const &move) const {
    Color turnColor = grid[move.getVectorRow(grid.size(), move.getFromRow())][move.getVectorCol(move.getFromCol())]->getPieceColor();
    CompletedMove completed(move, grid);
    int vectorRow = completed.getVectorRow(grid.size(), completed.getCapturedRow());
    int vectorCol = completed.getVectorCol(completed.getCapturedCol());
    Color attackedColor = grid[vectorRow][vectorCol]->getPieceColor();
    return (attackedColor == oppositeColor(turnColor));
}

bool Board::doesMoveHavePieceAttackedAfter(Move const &move) const {
    Color turnColor = grid[move.getVectorRow(grid.size(), move.getFromRow())][move.getVectorCol(move.getFromCol())]->getPieceColor();
    const_cast<Board*>(this)->makeMove(move);
    std::vector<Move> moves = getCapturingMoves(oppositeColor(turnColor));

    // Don't need to try every move if just two colours (I think) --> just check if capturingMoves.size() == 0
    for (Move const &cmove : moves) {
        CompletedMove completed(cmove, grid);
        int vectorRow = completed.getVectorRow(grid.size(), completed.getCapturedRow());
        int vectorCol = completed.getVectorCol(completed.getCapturedCol());
        if (grid[vectorRow][vectorCol]->getPieceColor() == turnColor) {
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

bool Board::isInCheckAfterMove(Move const &move) const {
    Color turnColor = grid[move.getVectorRow(grid.size(), move.getFromRow())][move.getVectorCol(move.getFromCol())]->getPieceColor();
    const_cast<Board*>(this)->makeMove(move);
    if (isInCheck(turnColor)) {
        const_cast<Board*>(this)->undoMove();
        return true;
    }
    const_cast<Board*>(this)->undoMove();
    return false;
} 

std::vector<Move> Board::getLegalMoves(Color color) const {
    std::vector<Move> moves = getPseudoLegalMoves(color);
    for (auto it = moves.begin(); it != moves.end();) {
        if (isInCheckAfterMove(*it)) {
            it = moves.erase(it);
        } else {
            ++it;
        }
    }
    return moves;
}

std::vector<Move> Board::getPseudoLegalMoves(Color color) const {
    std::vector<Move> moves;
    for (int row = 0; row < grid.size(); ++row) {
        for (int col = 0; col < grid[0].size(); ++col) {
            if (grid[row][col]->getPieceColor() == color) {
                std::vector<Move> pieceMoves = grid[row][col]->getMoves(*this, row, col, false);
                moves.insert(moves.end(), pieceMoves.begin(), pieceMoves.end());
            }
        }
    }
    return moves;
}

std::vector<Move> Board::getAllPseudoLegalAttackingMoves(Color color) const {
    std::vector<Move> moves;
    for (int row = 0; row < grid.size(); ++row) {
        for (int col = 0; col < grid[0].size(); ++col) {
            if (grid[row][col]->getPieceColor() == color) {
                std::vector<Move> pieceMoves = grid[row][col]->getMoves(*this, row, col, true);
                moves.insert(moves.end(), pieceMoves.begin(), pieceMoves.end());
            }  
        }
    }
    return moves;
}

std::vector<Move> Board::getCapturingMoves(Color color) const {
    std::vector<Move> moves = getLegalMoves(color);
    for (auto it = moves.begin(); it != moves.end();) {
        if (!doesMoveCapturePiece(*it)) {
            it = moves.erase(it);
        } else {
            ++it;
        }
    }
    return moves;
}

std::vector<Move> Board::getCheckApplyingMoves(Color color) const {
    std::vector<Move> moves = getLegalMoves(color);
    for (auto it = moves.begin(); it != moves.end();) {
        if (!doesMoveApplyCheck(*it)) {
            it = moves.erase(it);
        } else {
            ++it;
        }
    }
    return moves;
}

std::vector<Move> Board::getCaptureAvoidingMoves(Color color) const {
    std::vector<Move> moves = getLegalMoves(color);
    for (auto it = moves.begin(); it != moves.end();) {
        if (doesMoveHavePieceAttackedAfter(*it)) {
            it = moves.erase(it);
        } else {
            ++it;
        }
    }
    return moves;
}

bool Board::isInCheckMate(Color color) const {
    return isInCheck(color) && !canMakeMove(color);
}

bool Board::isInCheck(Color color) const {
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

bool Board::isMoveLegal(Move const &move) const {
    int fromRow = move.getVectorRow(grid.size(), move.getFromRow());
    int fromCol = move.getVectorCol(move.getFromCol());
    std::vector<Move> legalMoves = getLegalMoves(grid[fromRow][fromCol]->getPieceColor());
    return std::find(legalMoves.begin(), legalMoves.end(), move) != legalMoves.end();
}

void Board::makeMove(Move const &move) {

    CompletedMove completedMove(move, grid);

    int fromRow = completedMove.getVectorRow(grid.size(), completedMove.getFromRow());
    int fromCol = completedMove.getVectorCol(completedMove.getFromCol());

    int toRow = completedMove.getVectorRow(grid.size(), completedMove.getToRow());
    int toCol = completedMove.getVectorCol(completedMove.getToCol());

    int capturedRow = completedMove.getVectorRow(grid.size(), completedMove.getCapturedRow());
    int capturedCol = completedMove.getVectorCol(completedMove.getCapturedCol());

    // Apply move
    grid[capturedRow][capturedCol] = ChessPieceFactory::createEmptyPiece();
    std::swap(grid[fromRow][fromCol], grid[toRow][toCol]);
    grid[toRow][toCol]->setHasMoved(true);

    // Apply promotion
    if (completedMove.getPromotionPieceType() != PieceType::EMPTY) {
        std::unique_ptr<Piece> const &existingPiece = grid[toRow][toCol];
        grid[toRow][toCol] = ChessPieceFactory::createPiece(existingPiece->getPieceColor(), completedMove.getPromotionPieceType(), existingPiece->getPieceDirection(), true);
    }

    // Apply castle
    if (completedMove.getCastleMove() != nullptr) {
        std::unique_ptr<CompletedMove> const &castleMove = completedMove.getCastleMove();

        int castleFromRow = castleMove->getVectorRow(grid.size(), castleMove->getFromRow());
        int castleFromCol = castleMove->getVectorCol(castleMove->getFromCol());

        int castleToRow = castleMove->getVectorRow(grid.size(), castleMove->getToRow());
        int castleToCol = castleMove->getVectorCol(castleMove->getToCol());

        // Move the rook
        std::swap(grid[castleFromRow][castleFromCol], grid[castleToRow][castleToCol]);
        grid[castleToRow][castleToCol]->setHasMoved(true);
    }

    // Track completed move 
    completedMoves.emplace_back(std::move(completedMove));
}

bool Board::undoMove() {
    if (completedMoves.size() == 0) {
        return false;
    }

    CompletedMove const &lastMove = completedMoves.back();
    

    int fromRow = lastMove.getVectorRow(grid.size(), lastMove.getFromRow());
    int fromCol = lastMove.getVectorCol(lastMove.getFromCol());

    int toRow = lastMove.getVectorRow(grid.size(), lastMove.getToRow());
    int toCol = lastMove.getVectorCol(lastMove.getToCol());

    int capturedRow = lastMove.getVectorRow(grid.size(), lastMove.getCapturedRow());
    int capturedCol = lastMove.getVectorCol(lastMove.getCapturedCol());

    std::swap(grid[fromRow][fromCol], grid[toRow][toCol]);                  // Undo moved piece
    grid[fromRow][fromCol]->setHasMoved(lastMove.getMovedHasMoved());       // Set moved piece move field to what it was before
    grid[capturedRow][capturedCol] =                                        // Place captured piece
        ChessPieceFactory::createPiece(lastMove.getCapturedColor(), lastMove.getCapturedPieceType(), lastMove.getCapturedPieceDirection(), lastMove.getCapturedHasMoved(), lastMove.getCapturedScore());
    
    if (lastMove.getCastleMove() != nullptr) {
        std::unique_ptr<CompletedMove> const &castleMove = lastMove.getCastleMove();

        int castleFromRow = castleMove->getVectorRow(grid.size(), castleMove->getFromRow());
        int castleFromCol = castleMove->getVectorCol(castleMove->getFromCol());

        int castleToRow = castleMove->getVectorRow(grid.size(), castleMove->getToRow());
        int castleToCol = castleMove->getVectorCol(castleMove->getToCol());

        // Move the rook
        std::swap(grid[castleFromRow][castleFromCol], grid[castleToRow][castleToCol]);
        grid[castleFromRow][castleFromCol]->setHasMoved(false);
    }

    if (lastMove.getPromotionPieceType() != PieceType::EMPTY) {
        std::unique_ptr<Piece> const &promotedPiece = grid[fromRow][fromCol];       // Already moved back
        grid[fromRow][fromCol] = 
            ChessPieceFactory::createPiece(promotedPiece->getPieceColor(), PieceType::PAWN, promotedPiece->getPieceDirection(), promotedPiece->getHasMoved());
    }
    completedMoves.pop_back();
    return true;
}

bool Board::hasGameFinished() const {
    return (isInStaleMate() || isInCheckMate(colorOne) || isInCheckMate(colorTwo));
}

bool Board::isInStaleMate(Color color) const {
    return !canMakeMove(color) && !isInCheck(color);
}

bool Board::isInStaleMate() const {
    return (isInStaleMate(colorOne) || isInStaleMate(colorTwo));
}

void Board::setPosition(int row, char col, Color pieceColor, PieceType pieceType, PieceDirection pieceDirection, bool hasMoved, int pieceScore) {
    int vectorRow = grid.size() - row;
    int vectorCol = col - 'a';
    setPosition(vectorRow, vectorCol, pieceColor, pieceType, pieceDirection, hasMoved, pieceScore);
}

void Board::setPosition(int row, int col, Color pieceColor, PieceType pieceType, PieceDirection pieceDirection, bool hasMoved, int pieceScore) {
    grid[row][col] = ChessPieceFactory::createPiece(pieceColor, pieceType, pieceDirection, hasMoved, pieceScore);
}

bool Board::clearPosition(int row, char col) {
    int vectorRow = grid.size() - row;
    int vectorCol = col - 'a';
    return clearPosition(vectorRow, vectorCol);
}

bool Board::clearPosition(int row, int col) {
    if (grid[row][col]->getPieceType() == PieceType::EMPTY) {
        return false;
    }
    else {
        grid[row][col] = ChessPieceFactory::createEmptyPiece();
        return true;
    }
}

void Board::clearBoard() {
    for (int row = 0; row < grid.size(); ++row) {
        for (int col = 0; col < grid[0].size(); ++col) {
            grid[row][col] = ChessPieceFactory::createEmptyPiece();
        }
    }
    completedMoves.clear();
}

void Board::applyStandardSetup() {
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

bool Board::isBoardInValidState() const {
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

int Board::getAlphaBetaBoardScore(Color color) const {
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
