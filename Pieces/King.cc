// King.cc

#include "King.h"

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


/*
 * Static
 *
 * The directions a King Piece can move
 */
std::vector<MoveDirection> const King::kingMoveDirections = { 
    { MoveDirection(-1, -1) }, 
    { MoveDirection(-1, 0) }, 
    { MoveDirection(-1, 1) }, 
    { MoveDirection(0, -1) }, 
    { MoveDirection(0, 1) }, 
    { MoveDirection(1, -1) }, 
    { MoveDirection(1, 0) }, 
    { MoveDirection(1, 1) } 
};

/*
 * Basic ctor
 */
King::King(PieceLevel pieceLevel, Team team, PieceDirection pieceDirection, bool hasMoved, char32_t image) : 
    Piece(PieceData(PieceType::KING, pieceLevel, team, pieceDirection, hasMoved), PieceInfo(KING_SCORE, image)) { }

/*
 * Copy ctor
 */
King::King(King const &other) : 
    Piece(other) { }

/*
 * Move ctor
 */
King::King(King &&other) noexcept : 
    Piece(std::move(other)) { }

/*
 * Copy assignment
 */
King& King::operator=(King const &other) {
    if (this != &other) {
        Piece::operator=(other);
    }
    return *this;
}

/*
 * Move assignment
 */
King& King::operator=(King &&other) noexcept {
    if (this != &other) {
        Piece::operator=(std::move(other));
    }
    return *this;
}

/*
 * Returns all pseudo legal standard moves for a King Piece
 */
std::vector<std::unique_ptr<BoardMove>> King::getStandardMoves(std::unique_ptr<ChessBoard> const &chessBoard, BoardSquare const &fromSquare, bool onlyAttackingMoves) const {
    std::vector<std::unique_ptr<BoardMove>> moves;
    if (chessBoard->isSquareOnBoard(fromSquare)) {
        int fromRow = fromSquare.boardRow;
        int fromCol = fromSquare.boardCol;

        // Standard Moves
        for (MoveDirection const &kingMoveDirection : kingMoveDirections) {
            BoardSquare toSquare(fromRow + kingMoveDirection.rowDirection, fromCol + kingMoveDirection.colDirection);
            if (chessBoard->isSquareEmpty(toSquare) || chessBoard->isSquareOtherTeam(toSquare, pieceData.team)) {
                moves.emplace_back(BoardMoveFactory::createStandardMove(fromSquare, toSquare, toSquare, false, pieceData, chessBoard->getPieceDataAt(toSquare)));
            }
        }

        // Non Attacking Moves
        if (!onlyAttackingMoves) {

            // Castle
            if (!pieceData.hasMoved && !chessBoard->isSquareAttacked(fromSquare, pieceData.team)) {
                switch (pieceData.pieceDirection) {
                    case PieceDirection::NORTH:
                    case PieceDirection::SOUTH: {
                        if (fromRow == 0 || fromRow == chessBoard->getNumRowsOnBoard() - 1) {

                            // Left Castle: Check if have enough room to the left and that the rook travel square is empty
                            if (fromCol >= 4 && chessBoard->isSquareEmpty(BoardSquare(fromRow, fromCol - 3))) {
                                BoardSquare rookFromSquare(fromRow, fromCol - 4);
                                BoardSquare toSquare(fromRow, fromCol - 2);
                                BoardSquare rookToSquare(fromRow, fromCol - 1);
                                if (checkCommonCastleInfo(chessBoard, fromSquare, toSquare, rookFromSquare, rookToSquare)) {
                                    moves.emplace_back(BoardMoveFactory::createCastleMove(fromSquare, toSquare, toSquare, rookFromSquare, rookToSquare, false, pieceData, chessBoard->getPieceDataAt(toSquare)));
                                }
                            }

                            // Right Castle: Check if have enough room to the right
                            if (fromCol <= chessBoard->getNumColsOnBoard() - 4) {
                                BoardSquare rookFromSquare(fromRow, fromCol + 3);
                                BoardSquare toSquare(fromRow, fromCol + 2);
                                BoardSquare rookToSquare(fromRow, fromCol + 1);
                                if (checkCommonCastleInfo(chessBoard, fromSquare, toSquare, rookFromSquare, rookToSquare)) {
                                    moves.emplace_back(BoardMoveFactory::createCastleMove(fromSquare, toSquare, toSquare, rookFromSquare, rookToSquare, false, pieceData, chessBoard->getPieceDataAt(toSquare)));
                                }
                            }
                        }
                        break;
                    }
                    case PieceDirection::EAST:
                    case PieceDirection::WEST: {
                        if (fromCol == 0 || fromCol == chessBoard->getNumColsOnBoard() - 1) {

                            // Up Castle: Check if we have enough room up and that the rook travel square is empty
                            if (fromRow >= 4 && chessBoard->isSquareEmpty(BoardSquare(fromRow - 3, fromCol))) {
                                BoardSquare rookFromSquare(fromRow - 4, fromCol);
                                BoardSquare toSquare(fromRow - 2, fromCol);
                                BoardSquare rookToSquare(fromRow - 1, fromCol);
                                if (checkCommonCastleInfo(chessBoard, fromSquare, toSquare, rookFromSquare, rookToSquare)) {
                                    moves.emplace_back(BoardMoveFactory::createCastleMove(fromSquare, toSquare, toSquare, rookFromSquare, rookToSquare, false, pieceData, chessBoard->getPieceDataAt(toSquare)));
                                }
                            }

                            // Down Castle: Check if have enough room down
                            if (fromCol <= chessBoard->getNumRowsOnBoard() - 4) {
                                BoardSquare rookFromSquare(fromRow + 3, fromCol);
                                BoardSquare toSquare(fromRow + 2, fromCol);
                                BoardSquare rookToSquare(fromRow + 1, fromCol);
                                if (checkCommonCastleInfo(chessBoard, fromSquare, toSquare, rookFromSquare, rookToSquare)) {
                                    moves.emplace_back(BoardMoveFactory::createCastleMove(fromSquare, toSquare, toSquare, rookFromSquare, rookToSquare, false, pieceData, chessBoard->getPieceDataAt(toSquare)));
                                }
                            }
                        }
                        break;
                    }
                    default:
                        assert(false);
                }
            }
        }
    }
    return moves;
}

/*
 * True if a Castle move is legal, false otherwise
 */
bool King::checkCommonCastleInfo(std::unique_ptr<ChessBoard> const &chessBoard, BoardSquare const &fromSquare, BoardSquare const &toSquare, BoardSquare const &rookFromSquare, BoardSquare const &rookToSquare) const {
    if (chessBoard->getPieceDataAt(rookFromSquare).has_value()) {
        PieceData potentialRookPieceData = chessBoard->getPieceDataAt(rookFromSquare).value();
        return
            potentialRookPieceData.pieceType == PieceType::ROOK &&
            potentialRookPieceData.team == pieceData.team &&
            potentialRookPieceData.pieceDirection == pieceData.pieceDirection &&
            potentialRookPieceData.hasMoved == false &&
            chessBoard->isSquareEmpty(toSquare) &&
            chessBoard->isSquareEmpty(rookToSquare) && !chessBoard->isSquareAttacked(rookToSquare, pieceData.team);
    }

    return false;
}
