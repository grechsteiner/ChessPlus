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
#include "ChessBoard.h"
#include "BoardSquare.h"
#include "BoardMove.h"
#include "BoardMoveFactory.h"


// Basic ctor
Pawn::Pawn(PieceLevel pieceLevel, Team team, PieceDirection pieceDirection, bool hasMoved) :
    Piece(PieceData(PieceType::PAWN, PieceLevel::BASIC, team, pieceDirection, hasMoved), PieceInfo(1, "♟", "P")) {}

// Copy ctor
Pawn::Pawn(Pawn const &other) : 
    Piece(other) {}

// Move ctor
Pawn::Pawn(Pawn &&other) noexcept : 
    Piece(std::move(other)) {}

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
    switch (pieceData.pieceDirection) {
        case PieceDirection::NORTH: return std::make_pair(-1, 0);
        case PieceDirection::SOUTH: return std::make_pair(1, 0);
        case PieceDirection::EAST: return std::make_pair(0, 1);
        case PieceDirection::WEST: return std::make_pair(0, -1);
        default:
            assert(false);
    }
}

std::vector<std::unique_ptr<BoardMove>> Pawn::getStandardMoves(ChessBoard const &chessBoard, BoardSquare const &fromSquare, bool onlyAttackingMoves) const {
    std::vector<std::unique_ptr<BoardMove>> moves;
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
                addMoves(moves, chessBoard, fromSquare, normalMoveToSquare, normalMoveToSquare, false);
                if (!pieceData.hasMoved && chessBoard.isSquareEmpty(doubleMoveToSquare)) {
                    addMoves(moves, chessBoard, fromSquare, doubleMoveToSquare, doubleMoveToSquare, true);
                }
            }
        }
        
        // En Passant
        std::stack<std::unique_ptr<BoardMove>> const &completedMoves = chessBoard.getCompletedMoves();
        if (!completedMoves.empty()) {
            std::unique_ptr<BoardMove> const &lastCompletedMove = completedMoves.top();

            if (lastCompletedMove->getDoesEnableEnpassant() == true && lastCompletedMove->getMovedPieceData().team != pieceData.team) {
                int lastMoveToRow = lastCompletedMove->getToSquare().getBoardRow();
                int lastMoveToCol = lastCompletedMove->getToSquare().getBoardCol();

                switch (pieceData.pieceDirection) {
                    case PieceDirection::NORTH:
                    case PieceDirection::SOUTH: {
                        if (lastMoveToRow == fromRow && std::abs(lastMoveToCol - fromCol) == 1) {
                            BoardSquare toSquare(fromRow + pawnDirection.first, lastMoveToCol);
                            BoardSquare captureSquare = lastCompletedMove->getToSquare();
                            addMoves(moves, chessBoard, fromSquare, toSquare, captureSquare, false);
                        }
                        break;
                    }
                    case PieceDirection::EAST:
                    case PieceDirection::WEST: {
                        if (lastMoveToCol == fromCol && std::abs(lastMoveToRow - fromRow) == 1) {
                            BoardSquare toSquare(lastMoveToRow, fromCol + pawnDirection.second);
                            BoardSquare captureSquare = lastCompletedMove->getToSquare();
                            addMoves(moves, chessBoard, fromSquare, toSquare, captureSquare, false);
                        }
                        break;
                    }
                    default:
                        assert(false);
                }
            }
        }

        // Attack
        switch (pieceData.pieceDirection) {
            case PieceDirection::NORTH:
            case PieceDirection::SOUTH: {
                BoardSquare leftToSquare(fromRow + pawnDirection.first, fromCol - 1);
                BoardSquare rightToSquare(fromRow + pawnDirection.first, fromCol + 1);
                if (chessBoard.isSquareOtherTeam(leftToSquare, pieceData.team)) {
                    addMoves(moves, chessBoard, fromSquare, leftToSquare, leftToSquare, false);
                }
                if (chessBoard.isSquareOtherTeam(rightToSquare, pieceData.team)) {
                    addMoves(moves, chessBoard, fromSquare, rightToSquare, rightToSquare, false);
                }
                break;
            }
            case PieceDirection::EAST:
            case PieceDirection::WEST: {
                BoardSquare upToSquare(fromRow - 1, fromCol + pawnDirection.second);
                BoardSquare downToSquare(fromRow + 1, fromCol + pawnDirection.second);
                if (chessBoard.isSquareOtherTeam(upToSquare, pieceData.team)) {
                    addMoves(moves, chessBoard, fromSquare, upToSquare, upToSquare, false);
                }
                if (chessBoard.isSquareOtherTeam(downToSquare, pieceData.team)) {
                    addMoves(moves, chessBoard, fromSquare, downToSquare, downToSquare, false);
                }
                break;
            }
            default:
                assert(false);
        }
    }
    return moves;
}

void Pawn::addMoves(std::vector<std::unique_ptr<BoardMove>> &moves, ChessBoard const &chessBoard, BoardSquare const &fromSquare, BoardSquare const &toSquare, BoardSquare const &captureSquare, bool doesEnableEnpassant) const {
    int toRow = toSquare.getBoardRow();
    int toCol = toSquare.getBoardCol();
    PieceDirection pieceDirection = pieceData.pieceDirection;
    bool isPromotionMove = 
        (pieceDirection == PieceDirection::NORTH && toRow == 0) ||
        (pieceDirection == PieceDirection::SOUTH && toRow == chessBoard.getNumRows() - 1) ||
        (pieceDirection == PieceDirection::EAST && toCol == chessBoard.getNumCols() - 1) ||
        (pieceDirection == PieceDirection::WEST && toCol == 0);
    if (isPromotionMove) {
        static std::set<PieceType> promotionPieceTypes = { PieceType::QUEEN, PieceType::ROOK, PieceType::KNIGHT, PieceType::BISHOP };
        for (PieceType const &promotionPieceType : promotionPieceTypes) {
            PieceData promotedPieceData(promotionPieceType, pieceData.pieceLevel, pieceData.team, pieceData.pieceDirection, pieceData.hasMoved);
            moves.emplace_back(BoardMoveFactory::createStandardMove(fromSquare, toSquare, captureSquare, doesEnableEnpassant, promotedPieceData, chessBoard.getPieceDataAt(captureSquare)));
        }
    } else {
        moves.emplace_back(BoardMoveFactory::createStandardMove(fromSquare, toSquare, captureSquare, doesEnableEnpassant, pieceData, chessBoard.getPieceDataAt(captureSquare)));
    }
}
