// Pawn.cc

#include <vector>
#include <cassert>
#include <utility>

#include "Constants.h"
#include "Pawn.h"
#include "BoardPieceInterface.h"
#include "Piece.h"
#include "Move.h"


Pawn::Pawn(Color pieceColor, PieceDirection pieceDirection, bool hasMoved, int pieceScore) :
    Piece(pieceColor, PieceType::PAWN, pieceDirection, hasMoved, "♟", "P", pieceScore) {}

std::vector<Move> Pawn::getMovesImplementation(BoardPieceInterface const &board, int pieceRow, int pieceCol, bool attackingMoves) const {
    std::vector<Move> moves;

    std::pair<int, int> direction;
    switch (pieceDirection) {
        case PieceDirection::NORTH:
            direction = std::make_pair(-1, 0);
            break;
        case PieceDirection::SOUTH:
            direction = std::make_pair(1, 0);
            break;
        case PieceDirection::EAST:
            direction = std::make_pair(0, 1);
            break;
        case PieceDirection::WEST:
            direction = std::make_pair(0, -1);
            break;
        default:
            break;
    }

    // Normal Move + Double Pawn
    if (board.isEmptySquareOnBoard(pieceRow + direction.first, pieceCol + direction.second)) {

        // Normal Move
        moves.emplace_back(Move(board.getNumRows(), pieceRow, pieceCol, pieceRow + direction.first, pieceCol + direction.second));

        // Double Pawn
        if (!hasMoved && board.isEmptySquareOnBoard(pieceRow + 2 * direction.first, pieceCol + 2 * direction.second)) {
            moves.emplace_back(Move(board.getNumRows(), pieceRow, pieceCol, pieceRow + 2 * direction.first, pieceCol + 2 * direction.second));
        }
    }
    
    if (board.lastMove()) {
        CompletedMove const &lastCompletedMove = board.getLastMove();
        int lastCompletedToRow = lastCompletedMove.getVectorRow(board.getNumRows(), lastCompletedMove.getToRow());
        int lastCompletedToCol = lastCompletedMove.getVectorCol(lastCompletedMove.getToCol());  

        // En passant
        // Last move was double pawn move, and different color team
        if (lastCompletedMove.getMoveType() == MoveType::DOUBLE_PAWN && board.getPieceAt(lastCompletedToRow, lastCompletedToCol)->getPieceColor() != pieceColor) {
            switch (pieceDirection) {
                case PieceDirection::NORTH:
                case PieceDirection::SOUTH:
                    if (lastCompletedToRow == pieceRow) {
                        if (lastCompletedToCol == pieceCol + 1) {
                            moves.emplace_back(Move(board.getNumRows(), pieceRow, pieceCol, pieceRow + direction.first, pieceCol + 1));
                        } else if (lastCompletedToCol == pieceCol - 1) {
                            moves.emplace_back(Move(board.getNumRows(), pieceRow, pieceCol, pieceRow + direction.first, pieceCol - 1));
                        }
                    }
                    break;
                case PieceDirection::EAST:
                case PieceDirection::WEST:
                    if (lastCompletedToCol == pieceCol) {
                        if (lastCompletedToRow == pieceRow + 1) {
                            moves.emplace_back(Move(board.getNumRows(), pieceRow, pieceCol, pieceRow + 1, pieceCol + direction.second));
                        } else if (lastCompletedToRow == pieceRow - 1) {
                            moves.emplace_back(Move(board.getNumRows(), pieceRow, pieceCol, pieceRow - 1, pieceCol + direction.second));
                        }
                    }
                    break;
                default:
                    break;
            }
        }
    }

    // Attack
    switch (pieceDirection) {
        case PieceDirection::NORTH:
        case PieceDirection::SOUTH:
            // Left
            if (board.isOpposingColorOnBoard(pieceRow + direction.first, pieceCol - 1, pieceColor)) {
                moves.emplace_back(Move(board.getNumRows(), pieceRow, pieceCol, pieceRow + direction.first, pieceCol - 1));
            }
            // Right
            if (board.isOpposingColorOnBoard(pieceRow + direction.first, pieceCol + 1, pieceColor)) {
                moves.emplace_back(Move(board.getNumRows(), pieceRow, pieceCol, pieceRow + direction.first, pieceCol + 1));
            }
            break;
        case PieceDirection::EAST:
        case PieceDirection::WEST:
            // Up (left) 
            if (board.isOpposingColorOnBoard(pieceRow - 1, pieceCol + direction.second, pieceColor)) {
                moves.emplace_back(Move(board.getNumRows(), pieceRow, pieceCol, pieceRow - 1, pieceCol + direction.second));
            }
            // Down (right)
            if (board.isOpposingColorOnBoard(pieceRow + 1, pieceCol + direction.second, pieceColor)) {
                moves.emplace_back(Move(board.getNumRows(), pieceRow, pieceCol, pieceRow + 1, pieceCol + direction.second));
            }
            break;
        default:
            break;
    }

    // Promotion
    // Fix any moves that got to the end of the board
    std::vector<Move> promotionMoves;
    for (std::vector<Move>::iterator it = moves.begin(); it != moves.end(); ) {
        int toRow = it->getVectorRow(board.getNumRows(), it->getToRow());
        int toCol = it->getVectorCol(it->getToCol());
        if ((pieceDirection == PieceDirection::NORTH && toRow == 0) ||
            (pieceDirection == PieceDirection::SOUTH && toRow == board.getNumRows() - 1) ||
            (pieceDirection == PieceDirection::EAST && toCol == board.getNumCols() - 1) ||
            (pieceDirection == PieceDirection::WEST && toCol == 0)) {
            
            std::vector<Move> newPromotionMoves = getPromotionMoves(board, *it);
            promotionMoves.insert(promotionMoves.end(), newPromotionMoves.begin(), newPromotionMoves.end());
            it = moves.erase(it);
        } else {
            ++it;
        }
    }
    moves.insert(moves.end(), promotionMoves.begin(), promotionMoves.end());
    
    return moves;
}


std::vector<Move> Pawn::getPromotionMoves(BoardPieceInterface const &board, Move const &move) const {
    std::vector<Move> promotionMoves;

    int fromRow = move.getVectorRow(board.getNumRows(), move.getFromRow());
    int fromCol = move.getVectorCol(move.getFromCol());
    int toRow = move.getVectorRow(board.getNumRows(), move.getToRow());
    int toCol = move.getVectorCol(move.getToCol());
    promotionMoves.emplace_back(Move(board.getNumRows(), fromRow, fromCol, toRow, toCol, PieceType::QUEEN));
    promotionMoves.emplace_back(Move(board.getNumRows(), fromRow, fromCol, toRow, toCol, PieceType::ROOK));
    promotionMoves.emplace_back(Move(board.getNumRows(), fromRow, fromCol, toRow, toCol, PieceType::KNIGHT));
    promotionMoves.emplace_back(Move(board.getNumRows(), fromRow, fromCol, toRow, toCol, PieceType::BISHOP));
    
    return promotionMoves;
}
