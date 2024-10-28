// Pawn.cc

#include <vector>
#include <utility>
#include <set>
#include <cmath>
#include <cassert>

#include "Pawn.h"
#include "Constants.h"
#include "Piece.h"
#include "Cloneable.h"
#include "IChessBoard.h"
#include "BoardSquare.h"
#include "BoardMove.h"


// Basic ctor
Pawn::Pawn(Team team, PieceDirection pieceDirection, bool hasMoved, int pieceScore) :
    Cloneable<Piece, Pawn>(PieceType::PAWN, team, pieceDirection, hasMoved, pieceScore, "♟", "P") {}

// Copy ctor
Pawn::Pawn(Pawn const &other) : 
    Cloneable<Piece, Pawn>(other) {}

// Move ctor
Pawn::Pawn(Pawn &&other) noexcept : 
    Cloneable<Piece, Pawn>(std::move(other)) {}

// Copy assignment
Pawn& Pawn::operator=(Pawn const &other) {
    if (this != &other) {
        Piece::operator=(other);
    }
    return *this;
}

// Move assignment
Pawn& Pawn::operator=(Pawn &&other) noexcept {
    if (this != &other) {
        Piece::operator=(std::move(other));
    }
    return *this;
}

std::pair<int, int> Pawn::getPawnDirection() const {
    switch (pieceData.getPieceDirection()) {
        case PieceDirection::NORTH: return std::make_pair(-1, 0);
        case PieceDirection::SOUTH: return std::make_pair(1, 0);
        case PieceDirection::EAST: return std::make_pair(0, 1);
        case PieceDirection::WEST: return std::make_pair(0, -1);
        default:
            assert(false);
    }
}

std::vector<BoardMove> Pawn::getMovesImpl(IChessBoard const &chessBoard, BoardSquare const &fromSquare, bool onlyAttackingMoves) const {
    std::vector<BoardMove> moves;
    if (chessBoard.isSquareOnBoard(fromSquare)){
        int fromRow = fromSquare.getBoardRow();
        int fromCol = fromSquare.getBoardCol();
        std::pair<int, int> pawnDirection = getPawnDirection();

        // Non Attacking Moves 
        if (!onlyAttackingMoves) {

            // Normal Move + Double Pawn
            BoardSquare normalMoveToSquare(fromRow + pawnDirection.first, fromCol + pawnDirection.second);
            BoardSquare doubleMoveToSquare(fromRow + 2 * pawnDirection.first, fromCol + 2 * pawnDirection.second);
            if (chessBoard.isSquareEmpty(normalMoveToSquare)) {
                moves.emplace_back(BoardMove::createBasicMove(MoveType::STANDARD, pieceData, fromSquare, normalMoveToSquare, normalMoveToSquare));
                if (!pieceData.getHasMoved() && chessBoard.isSquareEmpty(doubleMoveToSquare)) {
                    moves.emplace_back(BoardMove::createBasicMove(MoveType::STANDARD, pieceData, fromSquare, doubleMoveToSquare, doubleMoveToSquare));
                }
            }
        }
        
        // En Passant
        std::optional<BoardMove> const &lastMove = chessBoard.getLastCompletedMove();
        if (lastMove.has_value() && lastMove.value().getMoveType() == MoveType::DOUBLE_PAWN && lastMove.value().getMovedPieceData().getTeam() != pieceData.getTeam()) {
            int lastMoveToRow = lastMove.value().getToSquare().getBoardRow();
            int lastMoveToCol = lastMove.value().getToSquare().getBoardCol();

            switch (pieceData.getPieceDirection()) {
                case PieceDirection::NORTH:
                case PieceDirection::SOUTH: {
                    if (lastMoveToRow == fromRow && std::abs(lastMoveToCol - fromCol) == 1) {
                        BoardSquare toSquare(fromRow + pawnDirection.first, lastMoveToCol);
                        BoardSquare captureSquare = lastMove.value().getToSquare();
                        moves.emplace_back(BoardMove::createBasicMove(MoveType::ENPASSANT, pieceData, fromSquare, toSquare, captureSquare, chessBoard.getPieceDataAt(captureSquare)));
                    }
                    break;
                }
                case PieceDirection::EAST:
                case PieceDirection::WEST: {
                    if (lastMoveToCol == fromCol && std::abs(lastMoveToRow - fromRow) == 1) {
                        BoardSquare toSquare(lastMoveToRow, fromCol + pawnDirection.second);
                        BoardSquare captureSquare = lastMove.value().getToSquare();
                        moves.emplace_back(BoardMove::createBasicMove(MoveType::ENPASSANT, pieceData, fromSquare, toSquare, captureSquare, chessBoard.getPieceDataAt(captureSquare)));
                    }
                    break;
                }
                default:
                    assert(false);
            }
        }

        // Attack
        switch (pieceData.getPieceDirection()) {
            case PieceDirection::NORTH:
            case PieceDirection::SOUTH: {
                BoardSquare leftToSquare(fromRow + pawnDirection.first, fromCol - 1);
                BoardSquare rightToSquare(fromRow + pawnDirection.first, fromCol + 1);
                if (chessBoard.isSquareOtherTeam(leftToSquare, pieceData.getTeam())) {
                    moves.emplace_back(BoardMove::createBasicMove(MoveType::STANDARD, pieceData, fromSquare, leftToSquare, leftToSquare, chessBoard.getPieceDataAt(leftToSquare)));
                }
                if (chessBoard.isSquareOtherTeam(rightToSquare, pieceData.getTeam())) {
                    moves.emplace_back(BoardMove::createBasicMove(MoveType::STANDARD, pieceData, fromSquare, rightToSquare, rightToSquare, chessBoard.getPieceDataAt(rightToSquare)));
                }
                break;
            }
            case PieceDirection::EAST:
            case PieceDirection::WEST: {
                BoardSquare upToSquare(fromRow - 1, fromCol + pawnDirection.second);
                BoardSquare downToSquare(fromRow + 1, fromCol + pawnDirection.second);
                if (chessBoard.isSquareOtherTeam(upToSquare, pieceData.getTeam())) {
                    moves.emplace_back(BoardMove::createBasicMove(MoveType::STANDARD, pieceData, fromSquare, upToSquare, upToSquare, chessBoard.getPieceDataAt(upToSquare)));
                }
                if (chessBoard.isSquareOtherTeam(downToSquare, pieceData.getTeam())) {
                    moves.emplace_back(BoardMove::createBasicMove(MoveType::STANDARD, pieceData, fromSquare, downToSquare, downToSquare, chessBoard.getPieceDataAt(downToSquare)));
                }
                break;
            }
            default:
                assert(false);
        }

        // Promotion (fix any moves that got to the end of the board)
        for (std::vector<BoardMove>::iterator it = moves.begin(); it != moves.end(); ) {
            int toRow = it->getToSquare().getBoardRow();
            int toCol = it->getToSquare().getBoardCol();
            PieceDirection pieceDirection = pieceData.getPieceDirection();
            if ((pieceDirection == PieceDirection::NORTH && toRow == 0) ||
                (pieceDirection == PieceDirection::SOUTH && toRow == chessBoard.getNumRows() - 1) ||
                (pieceDirection == PieceDirection::EAST && toCol == chessBoard.getNumCols() - 1) ||
                (pieceDirection == PieceDirection::WEST && toCol == 0)) {
                
                std::vector<BoardMove> promotionMoves = createPromotionMoves(*it);
                it = moves.erase(it);
                moves.insert(moves.end(), promotionMoves.begin(), promotionMoves.end());
            } else {
                ++it;
            }
        }
    }
    return moves;
}


std::vector<BoardMove> Pawn::createPromotionMoves(BoardMove const &move) const {
    static std::set<PieceType> promotionPieceTypes = { PieceType::QUEEN, PieceType::ROOK, PieceType::KNIGHT, PieceType::BISHOP };
    std::vector<BoardMove> promotionMoves;
    for (PieceType const &promotionPieceType : promotionPieceTypes) {
        promotionMoves.emplace_back(BoardMove::createPromotionMove(promotionPieceType, move.getMoveType(), move.getMovedPieceData(), move.getFromSquare(), move.getToSquare(), move.getCaptureSquare(), move.getCapturedPieceData()));
    }
    return promotionMoves;
}
