// King.cc

#include <vector>
#include <cassert>

#include "Constants.h"
#include "King.h"
#include "ChessBoard.h"
#include "Piece.h"
#include "Move.h"

std::vector<std::pair<int, int>> const King::kingDirections = { 
    {-1, -1}, 
    {-1, 0}, 
    {-1, 1}, 
    {0, -1}, 
    {0, 1}, 
    {1, -1}, 
    {1, 0}, 
    {1, 1} 
};

King::King(Color pieceColor, PieceDirection pieceDirection, bool hasMoved, int pieceScore) : 
    Piece(pieceColor, PieceType::KING, pieceDirection, hasMoved, "♚", "K", pieceScore) {}

std::vector<BoardMove> King::getMovesImplementation(ChessBoard const &board, int pieceRow, int pieceCol, bool attackingMoves) const {
    std::vector<BoardMove> moves;

    // Standard moves
    for (std::pair<int, int> const &kingDirection : kingDirections) {
        int newRow = pieceRow + kingDirection.first;
        int newCol = pieceCol + kingDirection.second;
        if (board.isEmptySquareOrOpposingColorOnBoard(newRow, newCol, pieceColor)) {
            moves.emplace_back(createFullMove(board, pieceRow, pieceCol, newRow, newCol, newRow, newCol, MoveType::STANDARD, true));
        }
    }

    if (!attackingMoves) {

        // Castle
        if (!hasMoved && !board.isSquareCheckAttacked(pieceRow, pieceCol, pieceColor)) {
            switch (pieceDirection) {
                case PieceDirection::NORTH:
                case PieceDirection::SOUTH:

                    // Left
                    // Check that don't end up in check during other check calculation
                    if ((pieceRow == 0 || pieceRow == board.getNumRows() - 1) &&                                                                    // Top or bottom row
                        pieceCol >= 4 &&                                                                                                            // Enough space on left
                        board.getPieceAt(pieceRow, pieceCol - 4).getPieceColor() == pieceColor &&                                                  // Must be same colour
                        board.getPieceAt(pieceRow, pieceCol - 4).getPieceType() == PieceType::ROOK &&                                              // Must be rook
                        board.getPieceAt(pieceRow, pieceCol - 4).getPieceDirection() == pieceDirection &&                                          // With same direction
                        board.isEmptySquareOnBoard(pieceRow, pieceCol - 1) && !board.isSquareCheckAttacked(pieceRow, pieceCol - 1, pieceColor) &&   // Move through square not attacked
                        board.isEmptySquareOnBoard(pieceRow, pieceCol - 2) &&                                                                       // Other empty move through
                        board.isEmptySquareOnBoard(pieceRow, pieceCol - 3)) {                                                                       // Other empty move through
                        
                        moves.emplace_back(createFullMove(board, pieceRow, pieceCol, pieceRow, pieceCol - 2, pieceRow, pieceCol - 2, MoveType::CASTLE, false));
                    }

                    // Right
                    // Check that don't end up in check during other check calculation
                    if ((pieceRow == 0 || pieceRow == board.getNumRows() - 1) &&                                                                    // Top or bottom row
                        pieceCol <= board.getNumCols() - 4 &&                                                                                       // Enough space on right
                        board.getPieceAt(pieceRow, pieceCol + 3).getPieceColor() == pieceColor &&                                                  // Must be same colour
                        board.getPieceAt(pieceRow, pieceCol + 3).getPieceType() == PieceType::ROOK &&                                              // Must be rook
                        board.getPieceAt(pieceRow, pieceCol + 3).getPieceDirection() == pieceDirection &&                                          // With same direction
                        board.isEmptySquareOnBoard(pieceRow, pieceCol + 1) && !board.isSquareCheckAttacked(pieceRow, pieceCol + 1, pieceColor) &&   // Move through square not attacked
                        board.isEmptySquareOnBoard(pieceRow, pieceCol + 2)) {                                                                       // Other empty move through

                        moves.emplace_back(createFullMove(board, pieceRow, pieceCol, pieceRow, pieceCol + 2, pieceRow, pieceCol + 2, MoveType::CASTLE, false));
                    }
                    

                    break;
                case PieceDirection::EAST:
                case PieceDirection::WEST:

                    // Up (left)
                    // Check that don't end up in check during other check calculation
                    if ((pieceCol == 0 || pieceCol == board.getNumCols() - 1) &&
                        pieceRow >= 4 &&
                        board.getPieceAt(pieceRow - 4, pieceCol).getPieceColor() == pieceColor &&
                        board.getPieceAt(pieceRow - 4, pieceCol).getPieceType() == PieceType::ROOK &&
                        board.getPieceAt(pieceRow - 4, pieceCol).getPieceDirection() == pieceDirection &&
                        board.isEmptySquareOnBoard(pieceRow - 1, pieceCol) && !board.isSquareCheckAttacked(pieceRow - 1, pieceCol, pieceColor) &&
                        board.isEmptySquareOnBoard(pieceRow - 2, pieceCol) && 
                        board.isEmptySquareOnBoard(pieceRow - 3, pieceCol)) {

                        moves.emplace_back(createFullMove(board, pieceRow, pieceCol, pieceRow - 2, pieceCol, pieceRow - 2, pieceCol, MoveType::CASTLE, false));
                    }
                    
                    // Down (right)
                    // Check that don't end up in check during other check calculation
                    if ((pieceCol == 0 || pieceCol == board.getNumCols() - 1) &&
                        pieceCol <= board.getNumRows() - 4 &&
                        board.getPieceAt(pieceRow + 3, pieceCol).getPieceColor() == pieceColor &&
                        board.getPieceAt(pieceRow + 3, pieceCol).getPieceType() == PieceType::ROOK &&
                        board.getPieceAt(pieceRow + 3, pieceCol).getPieceDirection() == pieceDirection &&
                        board.isEmptySquareOnBoard(pieceRow + 1, pieceCol) && !board.isSquareCheckAttacked(pieceRow + 1, pieceCol, pieceColor) &&
                        board.isEmptySquareOnBoard(pieceRow + 2, pieceCol)) {

                        moves.emplace_back(createFullMove(board, pieceRow, pieceCol, pieceRow + 2, pieceCol, pieceRow + 2, pieceCol, MoveType::CASTLE, false));
                    }

                    break;
                default:
                    break;
            }
        }
    }

    return moves;
}
