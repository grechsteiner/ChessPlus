// King.cc

#include <vector>
#include <utility>
#include <set>
#include <cassert>

#include "King.h"
#include "Constants.h"
#include "Piece.h"
#include "Cloneable.h"
#include "ChessBoard.h"
#include "BoardSquare.h"
#include "BoardMove.h"
#include "BoardMoveFactory.h"


// Static
std::set<std::pair<int, int>> const King::kingDirections = { 
    {-1, -1}, 
    {-1, 0}, 
    {-1, 1}, 
    {0, -1}, 
    {0, 1}, 
    {1, -1}, 
    {1, 0}, 
    {1, 1} 
};

// Basic ctor
King::King(PieceLevel pieceLevel, Team team, PieceDirection pieceDirection, bool hasMoved) : 
    Piece(PieceData(PieceType::KING, pieceLevel, team, pieceDirection, hasMoved), PieceInfo(1000, "♚", "K")) {}

// Copy ctor
King::King(King const &other) : 
    Piece(other) {}

// Move ctor
King::King(King &&other) noexcept : 
    Piece(std::move(other)) {}

// Copy assignment
King& King::operator=(King const &other) {
    if (this != &other) {
        Piece::operator=(other);
    }
    return *this;
}

// Move assignment
King& King::operator=(King &&other) noexcept {
    if (this != &other) {
        Piece::operator=(std::move(other));
    }
    return *this;
}

std::vector<std::unique_ptr<BoardMove>> King::getStandardMoves(ChessBoard const &chessBoard, BoardSquare const &fromSquare, bool onlyAttackingMoves) const {
    std::vector<std::unique_ptr<BoardMove>> moves;
    if (chessBoard.isSquareOnBoard(fromSquare)) {
        int fromRow = fromSquare.boardRow;
        int fromCol = fromSquare.boardCol;

        // Standard Moves
        for (std::pair<int, int> const &kingDirection : kingDirections) {
            BoardSquare toSquare(fromRow + kingDirection.first, fromCol + kingDirection.second);
            if (chessBoard.isSquareEmpty(toSquare) || chessBoard.isSquareOtherTeam(toSquare, pieceData.team)) {
                moves.emplace_back(BoardMoveFactory::createStandardMove(fromSquare, toSquare, toSquare, false, pieceData, chessBoard.getPieceDataAt(toSquare)));
            }
        }

        // Non Attacking Moves
        if (!onlyAttackingMoves) {

            // Castle
            if (!pieceData.hasMoved && !chessBoard.isSquareAttacked(fromSquare, pieceData.team)) {
                switch (pieceData.pieceDirection) {
                    case PieceDirection::NORTH:
                    case PieceDirection::SOUTH: {
                        if (fromRow == 0 || fromRow == chessBoard.getNumRows() - 1) {

                            // Left Castle: Check if have enough room to the left and that the rook travel square is empty
                            if (fromCol >= 4 && chessBoard.isSquareEmpty(BoardSquare(fromRow, fromCol - 3))) {
                                BoardSquare rookFromSquare(fromRow, fromCol - 4);
                                BoardSquare toSquare(fromRow, fromCol - 2);
                                BoardSquare rookToSquare(fromRow, fromCol - 1);
                                if (checkCommonCastleInfo(chessBoard, fromSquare, toSquare, rookFromSquare, rookToSquare)) {
                                    moves.emplace_back(BoardMoveFactory::createCastleMove(fromSquare, toSquare, toSquare, rookFromSquare, rookToSquare, false, pieceData, chessBoard.getPieceDataAt(toSquare)));
                                }
                            }

                            // Right Castle: Check if have enough room to the right
                            if (fromCol <= chessBoard.getNumCols() - 4) {
                                BoardSquare rookFromSquare(fromRow, fromCol + 3);
                                BoardSquare toSquare(fromRow, fromCol + 2);
                                BoardSquare rookToSquare(fromRow, fromCol + 1);
                                if (checkCommonCastleInfo(chessBoard, fromSquare, toSquare, rookFromSquare, rookToSquare)) {
                                    moves.emplace_back(BoardMoveFactory::createCastleMove(fromSquare, toSquare, toSquare, rookFromSquare, rookToSquare, false, pieceData, chessBoard.getPieceDataAt(toSquare)));
                                }
                            }
                        }
                        break;
                    }
                    case PieceDirection::EAST:
                    case PieceDirection::WEST: {
                        if (fromCol == 0 || fromCol == chessBoard.getNumCols() - 1) {

                            // Up Castle: Check if we have enough room up and that the rook travel square is empty
                            if (fromRow >= 4 && chessBoard.isSquareEmpty(BoardSquare(fromRow - 3, fromCol))) {
                                BoardSquare rookFromSquare(fromRow - 4, fromCol);
                                BoardSquare toSquare(fromRow - 2, fromCol);
                                BoardSquare rookToSquare(fromRow - 1, fromCol);
                                if (checkCommonCastleInfo(chessBoard, fromSquare, toSquare, rookFromSquare, rookToSquare)) {
                                    moves.emplace_back(BoardMoveFactory::createCastleMove(fromSquare, toSquare, toSquare, rookFromSquare, rookToSquare, false, pieceData, chessBoard.getPieceDataAt(toSquare)));
                                }
                            }

                            // Down Castle: Check if have enough room down
                            if (fromCol <= chessBoard.getNumRows() - 4) {
                                BoardSquare rookFromSquare(fromRow + 3, fromCol);
                                BoardSquare toSquare(fromRow + 2, fromCol);
                                BoardSquare rookToSquare(fromRow + 1, fromCol);
                                if (checkCommonCastleInfo(chessBoard, fromSquare, toSquare, rookFromSquare, rookToSquare)) {
                                    moves.emplace_back(BoardMoveFactory::createCastleMove(fromSquare, toSquare, toSquare, rookFromSquare, rookToSquare, false, pieceData, chessBoard.getPieceDataAt(toSquare)));
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

bool King::checkCommonCastleInfo(ChessBoard const &chessBoard, BoardSquare const &fromSquare, BoardSquare const &toSquare, BoardSquare const &rookFromSquare, BoardSquare const &rookToSquare) const {
    if (chessBoard.getPieceDataAt(rookFromSquare).has_value()) {
        PieceData potentialRookPieceData = chessBoard.getPieceDataAt(rookFromSquare).value();
        return
            potentialRookPieceData.pieceType == PieceType::ROOK &&
            potentialRookPieceData.team == pieceData.team &&
            potentialRookPieceData.pieceDirection == pieceData.pieceDirection &&
            potentialRookPieceData.hasMoved == false &&
            chessBoard.isSquareEmpty(toSquare) &&
            chessBoard.isSquareEmpty(rookToSquare) && !chessBoard.isSquareAttacked(rookToSquare, pieceData.team);
    } else {
        return false;
    }
}
