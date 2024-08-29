// Pawn.cc

#include <vector>
#include <cassert>
#include <utility>

#include "Constants.h"
#include "Pawn.h"
#include "ChessBoard.h"
#include "Piece.h"
#include "FullMove.h"


Pawn::Pawn(Color pieceColor, PieceDirection pieceDirection, bool hasMoved, int pieceScore) :
    Piece(pieceColor, PieceType::PAWN, pieceDirection, hasMoved, "♟", "P", pieceScore) {}

std::vector<FullMove> Pawn::getMovesImplementation(ChessBoard const &board, int pieceRow, int pieceCol, bool attackingMoves) const {
    std::vector<FullMove> moves;

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
        moves.emplace_back(createFullMove(board, pieceRow, pieceCol, pieceRow + direction.first, pieceCol + direction.second, pieceRow + direction.first, pieceCol + direction.second, MoveType::STANDARD, false));

        // Double Pawn
        if (!hasMoved && board.isEmptySquareOnBoard(pieceRow + 2 * direction.first, pieceCol + 2 * direction.second)) {
            moves.emplace_back(createFullMove(board, pieceRow, pieceCol, pieceRow + 2 * direction.first, pieceCol + 2 * direction.second, pieceRow + 2 * direction.first, pieceCol + 2 * direction.second, MoveType::DOUBLE_PAWN, false));
        }
    }
    
    if (board.hasMoveBeenMade()) {
        FullMove const &lastCompletedMove = board.getLastMove();

        // En passant
        // Last move was double pawn move, and different color team
        if (lastCompletedMove.getMoveType() == MoveType::DOUBLE_PAWN && board.getPieceAt(lastCompletedMove.getToRow(), lastCompletedMove.getToCol()).getPieceColor() != pieceColor) {
            switch (pieceDirection) {
                case PieceDirection::NORTH:
                case PieceDirection::SOUTH:
                    if (lastCompletedMove.getToRow() == pieceRow) {
                        if (lastCompletedMove.getToCol() == pieceCol + 1) {
                            moves.emplace_back(createFullMove(board, pieceRow, pieceCol, pieceRow + direction.first, pieceCol + 1, pieceRow + direction.first, pieceCol + 1, MoveType::ENPASSANT, true));
                        } else if (lastCompletedMove.getToCol() == pieceCol - 1) {
                            moves.emplace_back(createFullMove(board, pieceRow, pieceCol, pieceRow + direction.first, pieceCol - 1, pieceRow + direction.first, pieceCol - 1, MoveType::ENPASSANT, true));
                        }
                    }
                    break;
                case PieceDirection::EAST:
                case PieceDirection::WEST:
                    if (lastCompletedMove.getToCol() == pieceCol) {
                        if (lastCompletedMove.getToRow() == pieceRow + 1) {
                            moves.emplace_back(createFullMove(board, pieceRow, pieceCol, pieceRow + 1, pieceCol + direction.second, pieceRow + 1, pieceCol + direction.second, MoveType::ENPASSANT, true));
                        } else if (lastCompletedMove.getToRow() == pieceRow - 1) {
                            moves.emplace_back(createFullMove(board, pieceRow, pieceCol, pieceRow - 1, pieceCol + direction.second, pieceRow - 1, pieceCol + direction.second, MoveType::ENPASSANT, true));                        }
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
                moves.emplace_back(createFullMove(board, pieceRow, pieceCol, pieceRow + direction.first, pieceCol - 1, pieceRow + direction.first, pieceCol - 1, MoveType::STANDARD, true));
            }
            // Right
            if (board.isOpposingColorOnBoard(pieceRow + direction.first, pieceCol + 1, pieceColor)) {
                moves.emplace_back(createFullMove(board, pieceRow, pieceCol, pieceRow + direction.first, pieceCol + 1, pieceRow + direction.first, pieceCol + 1, MoveType::STANDARD, true));
            }
            break;
        case PieceDirection::EAST:
        case PieceDirection::WEST:
            // Up (left) 
            if (board.isOpposingColorOnBoard(pieceRow - 1, pieceCol + direction.second, pieceColor)) {
                moves.emplace_back(createFullMove(board, pieceRow, pieceCol, pieceRow - 1, pieceCol + direction.second, pieceRow - 1, pieceCol + direction.second, MoveType::STANDARD, true));
            }
            // Down (right)
            if (board.isOpposingColorOnBoard(pieceRow + 1, pieceCol + direction.second, pieceColor)) {
                moves.emplace_back(createFullMove(board, pieceRow, pieceCol, pieceRow + 1, pieceCol + direction.second, pieceRow + 1, pieceCol + direction.second, MoveType::STANDARD, true));
            }
            break;
        default:
            break;
    }

    // Promotion
    // Fix any moves that got to the end of the board
    std::vector<FullMove> promotionMoves;
    for (std::vector<FullMove>::iterator it = moves.begin(); it != moves.end(); ) {
        int toRow = it->getToRow();
        int toCol = it->getToCol();
        if ((pieceDirection == PieceDirection::NORTH && toRow == 0) ||
            (pieceDirection == PieceDirection::SOUTH && toRow == board.getNumRows() - 1) ||
            (pieceDirection == PieceDirection::EAST && toCol == board.getNumCols() - 1) ||
            (pieceDirection == PieceDirection::WEST && toCol == 0)) {
            
            std::vector<FullMove> newPromotionMoves = getPromotionMoves(board, *it);
            promotionMoves.insert(promotionMoves.end(), newPromotionMoves.begin(), newPromotionMoves.end());
            it = moves.erase(it);
        } else {
            ++it;
        }
    }
    moves.insert(moves.end(), promotionMoves.begin(), promotionMoves.end());
    
    return moves;
}


std::vector<FullMove> Pawn::getPromotionMoves(ChessBoard const &board, FullMove const &move) const {
    std::vector<FullMove> promotionMoves;

    int fromRow = move.getFromRow();
    int fromCol = move.getFromCol();
    int toRow = move.getToRow();
    int toCol = move.getToCol();
    promotionMoves.emplace_back(createFullMove(board, fromRow, fromCol, toRow, toCol, toRow, toCol, move.getMoveType(), move.getIsAttackingMove(), PieceType::QUEEN));
    promotionMoves.emplace_back(createFullMove(board, fromRow, fromCol, toRow, toCol, toRow, toCol, move.getMoveType(), move.getIsAttackingMove(), PieceType::ROOK));
    promotionMoves.emplace_back(createFullMove(board, fromRow, fromCol, toRow, toCol, toRow, toCol, move.getMoveType(), move.getIsAttackingMove(), PieceType::KNIGHT));
    promotionMoves.emplace_back(createFullMove(board, fromRow, fromCol, toRow, toCol, toRow, toCol, move.getMoveType(), move.getIsAttackingMove(), PieceType::BISHOP));
    
    return promotionMoves;
}
