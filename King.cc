// King.cc

#include <vector>
#include <cassert>

#include "Constants.h"
#include "King.h"
#include "ChessBoard.h"
#include "Piece.h"


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

std::vector<BoardMove> King::getMovesImplementation(ChessBoard const &board, BoardSquare const &boardSquare, bool onlyAttackingMoves) const {
    std::vector<BoardMove> moves;

    int pieceRow = boardSquare.getBoardRow();
    int pieceCol = boardSquare.getBoardCol();

    // Standard moves
    for (std::pair<int, int> const &kingDirection : kingDirections) {
        int newRow = pieceRow + kingDirection.first;
        int newCol = pieceCol + kingDirection.second;
        if (board.isEmptySquareOrOpposingColorOnBoard(BoardSquare(newRow, newCol), pieceInfo.pieceColor)) {
            moves.emplace_back(createBoardMove(board, BoardSquare(pieceRow, pieceCol), BoardSquare(newRow, newCol), BoardSquare(newRow, newCol), MoveType::STANDARD, true));
        }
    }

    // Only get castle moves if not only getting attacking moves
    if (!onlyAttackingMoves) {

        // Castle
        if (!pieceInfo.hasMoved && !board.isSquareAttacked(BoardSquare(pieceRow, pieceCol), pieceInfo.pieceColor)) {
            switch (pieceInfo.pieceDirection) {
                case PieceDirection::NORTH:
                case PieceDirection::SOUTH:

                    // Left
                    // Check that don't end up in check during other check calculation
                    if ((pieceRow == 0 || pieceRow == board.getNumRows() - 1) &&                                                                    // Top or bottom row
                        pieceCol >= 4 &&                                                                                                            // Enough space on left
                        board.getPieceInfoAt(BoardSquare(pieceRow, pieceCol - 4)).pieceColor == pieceInfo.pieceColor &&                                                  // Must be same colour
                        board.getPieceInfoAt(BoardSquare(pieceRow, pieceCol - 4)).pieceType == PieceType::ROOK &&                                              // Must be rook
                        board.getPieceInfoAt(BoardSquare(pieceRow, pieceCol - 4)).pieceDirection == pieceInfo.pieceDirection &&                                          // With same direction
                        board.isEmptySquareOnBoard(BoardSquare(pieceRow, pieceCol - 1)) && !board.isSquareAttacked(BoardSquare(pieceRow, pieceCol - 1), pieceInfo.pieceColor) &&   // Move through square not attacked
                        board.isEmptySquareOnBoard(BoardSquare(pieceRow, pieceCol - 2)) &&                                                                       // Other empty move through
                        board.isEmptySquareOnBoard(BoardSquare(pieceRow, pieceCol - 3))) {                                                                       // Other empty move through
                        
                        moves.emplace_back(createBoardMove(board, BoardSquare(pieceRow, pieceCol), BoardSquare(pieceRow, pieceCol - 2), BoardSquare(pieceRow, pieceCol - 2), MoveType::CASTLE, false));
                    }

                    // Right
                    // Check that don't end up in check during other check calculation
                    if ((pieceRow == 0 || pieceRow == board.getNumRows() - 1) &&                                                                    // Top or bottom row
                        pieceCol <= board.getNumCols() - 4 &&                                                                                       // Enough space on right
                        board.getPieceInfoAt(BoardSquare(pieceRow, pieceCol + 3)).pieceColor == pieceInfo.pieceColor &&                                                  // Must be same colour
                        board.getPieceInfoAt(BoardSquare(pieceRow, pieceCol + 3)).pieceType == PieceType::ROOK &&                                              // Must be rook
                        board.getPieceInfoAt(BoardSquare(pieceRow, pieceCol + 3)).pieceDirection == pieceInfo.pieceDirection &&                                          // With same direction
                        board.isEmptySquareOnBoard(BoardSquare(pieceRow, pieceCol + 1)) && !board.isSquareAttacked(BoardSquare(pieceRow, pieceCol + 1), pieceInfo.pieceColor) &&   // Move through square not attacked
                        board.isEmptySquareOnBoard(BoardSquare(pieceRow, pieceCol + 2))) {                                                                       // Other empty move through

                        moves.emplace_back(createBoardMove(board, BoardSquare(pieceRow, pieceCol), BoardSquare(pieceRow, pieceCol + 2), BoardSquare(pieceRow, pieceCol + 2), MoveType::CASTLE, false));
                    }
                    

                    break;
                case PieceDirection::EAST:
                case PieceDirection::WEST:

                    // Up (left)
                    // Check that don't end up in check during other check calculation
                    if ((pieceCol == 0 || pieceCol == board.getNumCols() - 1) &&
                        pieceRow >= 4 &&
                        board.getPieceInfoAt(BoardSquare(pieceRow - 4, pieceCol)).pieceColor == pieceInfo.pieceColor &&
                        board.getPieceInfoAt(BoardSquare(pieceRow - 4, pieceCol)).pieceType == PieceType::ROOK &&
                        board.getPieceInfoAt(BoardSquare(pieceRow - 4, pieceCol)).pieceDirection == pieceInfo.pieceDirection &&
                        board.isEmptySquareOnBoard(BoardSquare(pieceRow - 1, pieceCol)) && !board.isSquareAttacked(BoardSquare(pieceRow - 1, pieceCol), pieceInfo.pieceColor) &&
                        board.isEmptySquareOnBoard(BoardSquare(pieceRow - 2, pieceCol)) && 
                        board.isEmptySquareOnBoard(BoardSquare(pieceRow - 3, pieceCol))) {

                        moves.emplace_back(createBoardMove(board, BoardSquare(pieceRow, pieceCol), BoardSquare(pieceRow - 2, pieceCol), BoardSquare(pieceRow - 2, pieceCol), MoveType::CASTLE, false));
                    }
                    
                    // Down (right)
                    // Check that don't end up in check during other check calculation
                    if ((pieceCol == 0 || pieceCol == board.getNumCols() - 1) &&
                        pieceCol <= board.getNumRows() - 4 &&
                        board.getPieceInfoAt(BoardSquare(pieceRow + 3, pieceCol)).pieceColor == pieceInfo.pieceColor &&
                        board.getPieceInfoAt(BoardSquare(pieceRow + 3, pieceCol)).pieceType == PieceType::ROOK &&
                        board.getPieceInfoAt(BoardSquare(pieceRow + 3, pieceCol)).pieceDirection == pieceInfo.pieceDirection &&
                        board.isEmptySquareOnBoard(BoardSquare(pieceRow + 1, pieceCol)) && !board.isSquareAttacked(BoardSquare(pieceRow + 1, pieceCol), pieceInfo.pieceColor) &&
                        board.isEmptySquareOnBoard(BoardSquare(pieceRow + 2, pieceCol))) {

                        moves.emplace_back(createBoardMove(board, BoardSquare(pieceRow, pieceCol), BoardSquare(pieceRow + 2, pieceCol), BoardSquare(pieceRow + 2, pieceCol), MoveType::CASTLE, false));
                    }

                    break;
                default:
                    break;
            }
        }
    }

    return moves;
}
