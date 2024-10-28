// King.cc

#include <vector>
#include <utility>
#include <set>
#include <cassert>

#include "King.h"
#include "Constants.h"
#include "Piece.h"
#include "Cloneable.h"
#include "IChessBoard.h"
#include "BoardSquare.h"
#include "BoardMove.h"


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
King::King(Team team, PieceDirection pieceDirection, bool hasMoved, int pieceScore) : 
    Cloneable<Piece, King>(PieceType::KING, team, pieceDirection, hasMoved, pieceScore, "♚", "K") {}

// Copy ctor
King::King(King const &other) : 
    Cloneable<Piece, King>(other) {}

// Move ctor
King::King(King &&other) noexcept : 
    Cloneable<Piece, King>(std::move(other)) {}

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

std::vector<BoardMove> King::getMovesImpl(IChessBoard const &chessBoard, BoardSquare const &fromSquare, bool onlyAttackingMoves) const {
    std::vector<BoardMove> moves;
    if (chessBoard.isSquareOnBoard(fromSquare)) {
        int fromRow = fromSquare.getBoardRow();
        int fromCol = fromSquare.getBoardCol();

        // Standard Moves
        for (std::pair<int, int> const &kingDirection : kingDirections) {
            BoardSquare toSquare(fromRow + kingDirection.first, fromCol + kingDirection.second);
            if (chessBoard.isSquareEmpty(toSquare) || chessBoard.isSquareOtherTeam(toSquare, pieceData.getTeam())) {
                moves.emplace_back(BoardMove::createBasicMove(MoveType::STANDARD, pieceData, fromSquare, toSquare, toSquare, chessBoard.getPieceDataAt(toSquare)));
            }
        }

        // Non Attacking Moves
        if (!onlyAttackingMoves) {

            // Castle
            if (!pieceData.getHasMoved() && !chessBoard.isSquareAttacked(fromSquare, pieceData.getTeam())) {
                switch (pieceData.getPieceDirection()) {
                    case PieceDirection::NORTH:
                    case PieceDirection::SOUTH: {
                        if (fromRow == 0 || fromRow == chessBoard.getNumRows() - 1) {

                            // Left Castle: Check if have enough room to the left and that the rook travel square is empty
                            if (fromCol >= 4 && chessBoard.isSquareEmpty(BoardSquare(fromRow, fromCol - 3))) {
                                BoardSquare rookFromSquare(fromRow, fromCol - 4);
                                BoardSquare toSquare(fromRow, fromCol - 2);
                                BoardSquare rookToSquare(fromRow, fromCol - 1);
                                if (checkCommonCastleInfo(chessBoard, fromSquare, toSquare, rookFromSquare, rookToSquare)) {
                                    moves.emplace_back(BoardMove::createCastleMove(rookFromSquare, rookToSquare, MoveType::CASTLE, pieceData, fromSquare, toSquare, toSquare));
                                }
                            }

                            // Right Castle: Check if have enough room to the right
                            if (fromCol <= chessBoard.getNumCols() - 4) {
                                BoardSquare rookFromSquare(fromRow, fromCol + 3);
                                BoardSquare toSquare(fromRow, fromCol + 2);
                                BoardSquare rookToSquare(fromRow, fromCol + 1);
                                if (checkCommonCastleInfo(chessBoard, fromSquare, toSquare, rookFromSquare, rookToSquare)) {
                                    moves.emplace_back(BoardMove::createCastleMove(rookFromSquare, rookToSquare, MoveType::CASTLE, pieceData, fromSquare, toSquare, toSquare));
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
                                    moves.emplace_back(BoardMove::createCastleMove(rookFromSquare, rookToSquare, MoveType::CASTLE, pieceData, fromSquare, toSquare, toSquare));
                                }
                            }

                            // Down Castle: Check if have enough room down
                            if (fromCol <= chessBoard.getNumRows() - 4) {
                                BoardSquare rookFromSquare(fromRow + 3, fromCol);
                                BoardSquare toSquare(fromRow + 2, fromCol);
                                BoardSquare rookToSquare(fromRow + 1, fromCol);
                                if (checkCommonCastleInfo(chessBoard, fromSquare, toSquare, rookFromSquare, rookToSquare)) {
                                    moves.emplace_back(BoardMove::createCastleMove(rookFromSquare, rookToSquare, MoveType::CASTLE, pieceData, fromSquare, toSquare, toSquare));
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

bool King::checkCommonCastleInfo(IChessBoard const &chessBoard, BoardSquare const &fromSquare, BoardSquare const &toSquare, BoardSquare const &rookFromSquare, BoardSquare const &rookToSquare) const {
    if (chessBoard.getPieceDataAt(rookFromSquare).has_value()) {
        PieceData rookPieceData = chessBoard.getPieceDataAt(rookFromSquare).value();
        return
            rookPieceData.getPieceType() == PieceType::ROOK &&
            rookPieceData.getTeam() == pieceData.getTeam() &&
            rookPieceData.getPieceDirection() == pieceData.getPieceDirection() &&
            rookPieceData.getHasMoved() == false &&
            chessBoard.isSquareEmpty(toSquare) &&
            chessBoard.isSquareEmpty(rookToSquare) && !chessBoard.isSquareAttacked(rookToSquare, pieceData.getTeam());
    } else {
        return false;
    }
}
