// Pawn.cc

#include "Pawn.h"

#include <cassert>
#include <memory>
#include <utility>
#include <vector>

#include "BoardMove.h"
#include "BoardMoveFactory.h"
#include "BoardSquare.h"
#include "ChessBoard.h"
#include "Constants.h"
#include "MoveDirection.h"
#include "Piece.h"


// Basic ctor
Pawn::Pawn(PieceLevel pieceLevel, Team team, PieceDirection pieceDirection, bool hasMoved, char32_t image) :
    Piece(PieceData(PieceType::PAWN, pieceLevel, team, pieceDirection, hasMoved), PieceInfo(1, image)) { }

// Copy ctor
Pawn::Pawn(Pawn const &other) : 
    Piece(other) { }

// Move ctor
Pawn::Pawn(Pawn &&other) noexcept : 
    Piece(std::move(other)) { }

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

/*
 * Converts PieceDirection to MoveDirection
 */
MoveDirection Pawn::getPawnMoveDirection() const {
    switch (pieceData.pieceDirection) {
        case PieceDirection::NORTH: return MoveDirection(-1, 0);
        case PieceDirection::SOUTH: return MoveDirection(1, 0);
        case PieceDirection::EAST: return MoveDirection(0, 1);
        case PieceDirection::WEST: return MoveDirection(0, -1);
        default:
            assert(false);
    }
}

/*
 * Returns all pseudo legal standard moves for a Bishop Piece
 */
std::vector<std::unique_ptr<BoardMove>> Pawn::getStandardMoves(std::unique_ptr<ChessBoard> const &chessBoard, BoardSquare const &fromSquare, bool onlyAttackingMoves) const {
    std::vector<std::unique_ptr<BoardMove>> moves;
    if (chessBoard->isSquareOnBoard(fromSquare)){
        int fromRow = fromSquare.boardRow;
        int fromCol = fromSquare.boardCol;
        MoveDirection pawnMoveDirection = getPawnMoveDirection();

        // Non Attacking Moves 
        if (!onlyAttackingMoves) {

            // Normal Move + Double Pawn
            BoardSquare normalMoveToSquare(fromRow + pawnMoveDirection.rowDirection, fromCol + pawnMoveDirection.colDirection);
            BoardSquare doubleMoveToSquare(fromRow + 2 * pawnMoveDirection.rowDirection, fromCol + 2 * pawnMoveDirection.colDirection);
            if (chessBoard->isSquareEmpty(normalMoveToSquare)) {
                addMoves(moves, chessBoard, fromSquare, normalMoveToSquare, normalMoveToSquare, false);
                if (!pieceData.hasMoved && chessBoard->isSquareEmpty(doubleMoveToSquare)) {
                    addMoves(moves, chessBoard, fromSquare, doubleMoveToSquare, doubleMoveToSquare, true);
                }
            }
        }
        
        // En Passant
        std::vector<std::unique_ptr<BoardMove>> const &completedMoves = chessBoard->getCompletedMoves();
        if (!completedMoves.empty()) {
            std::unique_ptr<BoardMove> const &lastCompletedMove = completedMoves.back();

            if (lastCompletedMove->getDoesEnableEnpassant() == true && lastCompletedMove->getMovedPieceData().team != pieceData.team) {
                int lastMoveToRow = lastCompletedMove->getToSquare().boardRow;
                int lastMoveToCol = lastCompletedMove->getToSquare().boardCol;

                switch (pieceData.pieceDirection) {
                    case PieceDirection::NORTH:
                    case PieceDirection::SOUTH: {
                        if (lastMoveToRow == fromRow && std::abs(lastMoveToCol - fromCol) == 1) {
                            BoardSquare toSquare(fromRow + pawnMoveDirection.rowDirection, lastMoveToCol);
                            BoardSquare captureSquare = lastCompletedMove->getToSquare();
                            addMoves(moves, chessBoard, fromSquare, toSquare, captureSquare, false);
                        }
                        break;
                    }
                    case PieceDirection::EAST:
                    case PieceDirection::WEST: {
                        if (lastMoveToCol == fromCol && std::abs(lastMoveToRow - fromRow) == 1) {
                            BoardSquare toSquare(lastMoveToRow, fromCol + pawnMoveDirection.colDirection);
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
                BoardSquare leftToSquare(fromRow + pawnMoveDirection.rowDirection, fromCol - 1);
                BoardSquare rightToSquare(fromRow + pawnMoveDirection.rowDirection, fromCol + 1);
                if (chessBoard->isSquareOtherTeam(leftToSquare, pieceData.team)) {
                    addMoves(moves, chessBoard, fromSquare, leftToSquare, leftToSquare, false);
                }
                if (chessBoard->isSquareOtherTeam(rightToSquare, pieceData.team)) {
                    addMoves(moves, chessBoard, fromSquare, rightToSquare, rightToSquare, false);
                }
                break;
            }
            case PieceDirection::EAST:
            case PieceDirection::WEST: {
                BoardSquare upToSquare(fromRow - 1, fromCol + pawnMoveDirection.colDirection);
                BoardSquare downToSquare(fromRow + 1, fromCol + pawnMoveDirection.colDirection);
                if (chessBoard->isSquareOtherTeam(upToSquare, pieceData.team)) {
                    addMoves(moves, chessBoard, fromSquare, upToSquare, upToSquare, false);
                }
                if (chessBoard->isSquareOtherTeam(downToSquare, pieceData.team)) {
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


/*
 * If BoardMove represented by arguments should have a promotion PieceType, append variants with all possible promotion PieceTypes
 */
void Pawn::addMoves(std::vector<std::unique_ptr<BoardMove>> &moves, std::unique_ptr<ChessBoard> const &chessBoard, BoardSquare const &fromSquare, BoardSquare const &toSquare, BoardSquare const &captureSquare, bool doesEnableEnpassant) const {
    PieceDirection pieceDirection = pieceData.pieceDirection;
    int toRow = toSquare.boardRow;
    int toCol = toSquare.boardCol;

    if ((pieceDirection == PieceDirection::NORTH && toRow == 0) ||
        (pieceDirection == PieceDirection::SOUTH && toRow == chessBoard->getNumRowsOnBoard() - 1) ||
        (pieceDirection == PieceDirection::EAST && toCol == chessBoard->getNumColsOnBoard() - 1) ||
        (pieceDirection == PieceDirection::WEST && toCol == 0)) {

        static std::vector<PieceType> promotionPieceTypes = { PieceType::QUEEN, PieceType::ROOK, PieceType::KNIGHT, PieceType::BISHOP };
        for (PieceType const &promotionPieceType : promotionPieceTypes) {
            PieceData promotedPieceData(promotionPieceType, pieceData.pieceLevel, pieceData.team, pieceData.pieceDirection, pieceData.hasMoved);
            moves.emplace_back(BoardMoveFactory::createStandardMove(fromSquare, toSquare, captureSquare, doesEnableEnpassant, promotedPieceData, chessBoard->getPieceDataAt(captureSquare)));
        }
    } else {
        moves.emplace_back(BoardMoveFactory::createStandardMove(fromSquare, toSquare, captureSquare, doesEnableEnpassant, pieceData, chessBoard->getPieceDataAt(captureSquare)));
    }
}
