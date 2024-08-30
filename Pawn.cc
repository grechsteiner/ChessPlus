// Pawn.cc

#include <vector>
#include <cassert>
#include <utility>

#include "Constants.h"
#include "Pawn.h"
#include "ChessBoard.h"
#include "Piece.h"
#include "BoardMove.h"


Pawn::Pawn(Team team, PieceDirection pieceDirection, bool hasMoved, int pieceScore) :
    Piece(team, PieceType::PAWN, pieceDirection, hasMoved, "♟", "P", pieceScore) {}

std::vector<BoardMove> Pawn::getMovesImplementation(ChessBoard const &board, BoardSquare const &boardSquare, bool onlyAttackingMoves) const {
    std::vector<BoardMove> moves;

    int pieceRow = boardSquare.getBoardRow();
    int pieceCol = boardSquare.getBoardCol();

    std::pair<int, int> direction;
    switch (pieceInfo.pieceDirection) {
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
    // Only if not get only attacking moves
    if (!onlyAttackingMoves) {
        if (board.isEmptySquareOnBoard(BoardSquare(pieceRow + direction.first, pieceCol + direction.second))) {
            // Normal Move
            moves.emplace_back(createBoardMove(board, BoardSquare(pieceRow, pieceCol), BoardSquare(pieceRow + direction.first, pieceCol + direction.second), BoardSquare(pieceRow + direction.first, pieceCol + direction.second), MoveType::STANDARD, false));

            // Double Pawn
            if (!pieceInfo.hasMoved && board.isEmptySquareOnBoard(BoardSquare(pieceRow + 2 * direction.first, pieceCol + 2 * direction.second))) {
                moves.emplace_back(createBoardMove(board, BoardSquare(pieceRow, pieceCol), BoardSquare(pieceRow + 2 * direction.first, pieceCol + 2 * direction.second), BoardSquare(pieceRow + 2 * direction.first, pieceCol + 2 * direction.second), MoveType::DOUBLE_PAWN, false));
            }
        }
    }
    
    
    // En passant
    if (board.hasMoveBeenMade()) {
        BoardMove const &lastCompletedMove = board.getLastMadeMove();

        int lastToRow = lastCompletedMove.getToSquare().getBoardRow();
        int lastToCol = lastCompletedMove.getToSquare().getBoardCol();

        // En passant
        // Last move was double pawn move, and different color team
        if (lastCompletedMove.getMoveType() == MoveType::DOUBLE_PAWN && board.getPieceInfoAt(lastCompletedMove.getToSquare()).team != pieceInfo.team) {
            switch (pieceInfo.pieceDirection) {
                case PieceDirection::NORTH:
                case PieceDirection::SOUTH:
                    if (lastToRow == pieceRow) {
                        if (lastToCol == pieceCol + 1) {
                            moves.emplace_back(createBoardMove(board, BoardSquare(pieceRow, pieceCol), BoardSquare(pieceRow + direction.first, pieceCol + 1), BoardSquare(pieceRow, pieceCol + 1), MoveType::ENPASSANT, true));
                        } else if (lastToCol == pieceCol - 1) {
                            moves.emplace_back(createBoardMove(board, BoardSquare(pieceRow, pieceCol), BoardSquare(pieceRow + direction.first, pieceCol - 1), BoardSquare(pieceRow, pieceCol - 1), MoveType::ENPASSANT, true));
                        }
                    }
                    break;
                case PieceDirection::EAST:
                case PieceDirection::WEST:
                    if (lastToCol == pieceCol) {
                        if (lastToRow == pieceRow + 1) {
                            moves.emplace_back(createBoardMove(board, BoardSquare(pieceRow, pieceCol), BoardSquare(pieceRow + 1, pieceCol + direction.second), BoardSquare(pieceRow + 1, pieceCol), MoveType::ENPASSANT, true));
                        } else if (lastToRow == pieceRow - 1) {
                            moves.emplace_back(createBoardMove(board, BoardSquare(pieceRow, pieceCol), BoardSquare(pieceRow - 1, pieceCol + direction.second), BoardSquare(pieceRow - 1, pieceCol), MoveType::ENPASSANT, true));                        }
                    }
                    break;
                default:
                    break;
            }
        }
    }

    // Attack
    switch (pieceInfo.pieceDirection) {
        case PieceDirection::NORTH:
        case PieceDirection::SOUTH:
            // Left
            if (board.isOpposingTeamOnBoard(BoardSquare(pieceRow + direction.first, pieceCol - 1), pieceInfo.team)) {
                moves.emplace_back(createBoardMove(board, BoardSquare(pieceRow, pieceCol), BoardSquare(pieceRow + direction.first, pieceCol - 1), BoardSquare(pieceRow + direction.first, pieceCol - 1), MoveType::STANDARD, true));
            }
            // Right
            if (board.isOpposingTeamOnBoard(BoardSquare(pieceRow + direction.first, pieceCol + 1), pieceInfo.team)) {
                moves.emplace_back(createBoardMove(board, BoardSquare(pieceRow, pieceCol), BoardSquare(pieceRow + direction.first, pieceCol + 1), BoardSquare(pieceRow + direction.first, pieceCol + 1), MoveType::STANDARD, true));
            }
            break;
        case PieceDirection::EAST:
        case PieceDirection::WEST:
            // Up (left) 
            if (board.isOpposingTeamOnBoard(BoardSquare(pieceRow - 1, pieceCol + direction.second), pieceInfo.team)) {
                moves.emplace_back(createBoardMove(board, BoardSquare(pieceRow, pieceCol), BoardSquare(pieceRow - 1, pieceCol + direction.second), BoardSquare(pieceRow - 1, pieceCol + direction.second), MoveType::STANDARD, true));
            }
            // Down (right)
            if (board.isOpposingTeamOnBoard(BoardSquare(pieceRow + 1, pieceCol + direction.second), pieceInfo.team)) {
                moves.emplace_back(createBoardMove(board, BoardSquare(pieceRow, pieceCol), BoardSquare(pieceRow + 1, pieceCol + direction.second), BoardSquare(pieceRow + 1, pieceCol + direction.second), MoveType::STANDARD, true));
            }
            break;
        default:
            break;
    }

    // Promotion
    // Fix any moves that got to the end of the board
    std::vector<BoardMove> promotionMoves;
    for (std::vector<BoardMove>::iterator it = moves.begin(); it != moves.end(); ) {
        int toRow = it->getToSquare().getBoardRow();
        int toCol = it->getToSquare().getBoardCol();
        if ((pieceInfo.pieceDirection == PieceDirection::NORTH && toRow == 0) ||
            (pieceInfo.pieceDirection == PieceDirection::SOUTH && toRow == board.getNumRows() - 1) ||
            (pieceInfo.pieceDirection == PieceDirection::EAST && toCol == board.getNumCols() - 1) ||
            (pieceInfo.pieceDirection == PieceDirection::WEST && toCol == 0)) {
            
            std::vector<BoardMove> newPromotionMoves = getPromotionMoves(board, *it);
            promotionMoves.insert(promotionMoves.end(), newPromotionMoves.begin(), newPromotionMoves.end());
            it = moves.erase(it);
        } else {
            ++it;
        }
    }
    moves.insert(moves.end(), promotionMoves.begin(), promotionMoves.end());
    
    return moves;
}


std::vector<BoardMove> Pawn::getPromotionMoves(ChessBoard const &board, BoardMove const &move) const {
    std::vector<BoardMove> promotionMoves;
    promotionMoves.emplace_back(createBoardMove(board, move.getFromSquare(), move.getToSquare(), move.getCaptureSquare(), move.getMoveType(), move.getIsAttackingMove(), PieceType::QUEEN));
    promotionMoves.emplace_back(createBoardMove(board, move.getFromSquare(), move.getToSquare(), move.getCaptureSquare(), move.getMoveType(), move.getIsAttackingMove(), PieceType::ROOK));
    promotionMoves.emplace_back(createBoardMove(board, move.getFromSquare(), move.getToSquare(), move.getCaptureSquare(), move.getMoveType(), move.getIsAttackingMove(), PieceType::KNIGHT));
    promotionMoves.emplace_back(createBoardMove(board, move.getFromSquare(), move.getToSquare(), move.getCaptureSquare(), move.getMoveType(), move.getIsAttackingMove(), PieceType::BISHOP));
    
    return promotionMoves;
}
