// King.cc

#include <vector>
#include <utility>
#include <set>

#include "King.h"
#include "Constants.h"
#include "Piece.h"
#include "ChessBoard.h"
#include "BoardSquare.h"
#include "BoardMove.h"


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

King::King(Team team, PieceDirection pieceDirection, bool hasMoved, int pieceScore) : 
    Piece(PieceType::KING, team, pieceDirection, hasMoved, pieceScore, "♚", "K") {}

std::vector<BoardMove> King::getMovesImpl(ChessBoard const &chessBoard, BoardSquare const &fromSquare, bool onlyAttackingMoves) const {
    std::vector<BoardMove> moves;
    if (chessBoard.isSquareOnBoard(fromSquare)) {
        int fromRow = fromSquare.getBoardRow();
        int fromCol = fromSquare.getBoardCol();

        // Standard Moves
        for (std::pair<int, int> const &kingDirection : kingDirections) {
            BoardSquare toSquare(fromRow + kingDirection.first, fromCol + kingDirection.second);
            if (chessBoard.isSquareEmpty(toSquare) || chessBoard.isSquareOtherTeam(toSquare, pieceInfo.getTeam())) {
                moves.emplace_back(BoardMove::createBasicMove(MoveType::STANDARD, pieceInfo, fromSquare, toSquare, toSquare, chessBoard.getPieceInfoAt(toSquare)));
            }
        }

        // Non Attacking Moves
        if (!onlyAttackingMoves) {

            // Castle
            if (!pieceInfo.getHasMoved() && !chessBoard.isSquareAttacked(fromSquare, pieceInfo.getTeam())) {
                switch (pieceInfo.getPieceDirection()) {
                    case PieceDirection::NORTH:
                    case PieceDirection::SOUTH: {
                        if (fromRow == 0 || fromRow == chessBoard.getNumRows() - 1) {

                            // Left Castle: Check if have enough room to the left and that the rook travel square is empty
                            if (fromCol >= 4 && chessBoard.isSquareEmpty(BoardSquare(fromRow, fromCol - 3))) {
                                BoardSquare rookFromSquare(fromRow, fromCol - 4);
                                BoardSquare toSquare(fromRow, fromCol - 2);
                                BoardSquare rookToSquare(fromRow, fromCol - 1);
                                if (checkCommonCastleInfo(chessBoard, fromSquare, toSquare, rookFromSquare, rookToSquare)) {
                                    moves.emplace_back(BoardMove::createCastleMove(rookFromSquare, rookToSquare, MoveType::CASTLE, pieceInfo, fromSquare, toSquare, toSquare));
                                }
                            }

                            // Right Castle: Check if have enough room to the right
                            if (fromCol <= chessBoard.getNumCols() - 4) {
                                BoardSquare rookFromSquare(fromRow, fromCol + 3);
                                BoardSquare toSquare(fromRow, fromCol + 2);
                                BoardSquare rookToSquare(fromRow, fromCol + 1);
                                if (checkCommonCastleInfo(chessBoard, fromSquare, toSquare, rookFromSquare, rookToSquare)) {
                                    moves.emplace_back(BoardMove::createCastleMove(rookFromSquare, rookToSquare, MoveType::CASTLE, pieceInfo, fromSquare, toSquare, toSquare));
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
                                    moves.emplace_back(BoardMove::createCastleMove(rookFromSquare, rookToSquare, MoveType::CASTLE, pieceInfo, fromSquare, toSquare, toSquare));
                                }
                            }

                            // Down Castle: Check if have enough room down
                            if (fromCol <= chessBoard.getNumRows() - 4) {
                                BoardSquare rookFromSquare(fromRow + 3, fromCol);
                                BoardSquare toSquare(fromRow + 2, fromCol);
                                BoardSquare rookToSquare(fromRow + 1, fromCol);
                                if (checkCommonCastleInfo(chessBoard, fromSquare, toSquare, rookFromSquare, rookToSquare)) {
                                    moves.emplace_back(BoardMove::createCastleMove(rookFromSquare, rookToSquare, MoveType::CASTLE, pieceInfo, fromSquare, toSquare, toSquare));
                                }
                            }
                        }
                        break;
                    }
                    default:
                        break;
                }
            }
        }
    }
    return moves;
}

bool King::checkCommonCastleInfo(ChessBoard const &chessBoard, BoardSquare const &fromSquare, BoardSquare const &toSquare, BoardSquare const &rookFromSquare, BoardSquare const &rookToSquare) const {
    if (chessBoard.getPieceInfoAt(rookFromSquare).has_value()) {
        PieceInfo rookPieceInfo = chessBoard.getPieceInfoAt(rookFromSquare).value();
        return
            rookPieceInfo.getPieceType() == PieceType::ROOK &&
            rookPieceInfo.getTeam() == pieceInfo.getTeam() &&
            rookPieceInfo.getPieceDirection() == pieceInfo.getPieceDirection() &&
            rookPieceInfo.getHasMoved() == false &&
            chessBoard.isSquareEmpty(toSquare) &&
            chessBoard.isSquareEmpty(rookToSquare) && !chessBoard.isSquareAttacked(rookToSquare, pieceInfo.getTeam());
    } else {
        return false;
    }
}
