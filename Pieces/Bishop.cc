// Bishop.cc

#include <vector>
#include <utility>
#include <set>

#include "Bishop.h"
#include "Constants.h"
#include "Piece.h"
#include "Cloneable.h"
#include "ChessBoard.h"
#include "BoardSquare.h"
#include "OldBoardMove.h"

// Static
std::set<std::pair<int, int>> const Bishop::bishopDirections = { 
    {-1, -1},  
    {-1, 1}, 
    {1, -1}, 
    {1, 1} 
};

// Basic ctor
Bishop::Bishop(PieceLevel pieceLevel, Team team, PieceDirection pieceDirection, bool hasMoved) :
    Piece(PieceInfo(PieceData(PieceType::BISHOP, pieceLevel, team, pieceDirection, hasMoved), 3, "♝", "B")) {}

// Copy ctor
Bishop::Bishop(Bishop const &other) : 
    Piece(other) {}

// Move ctor
Bishop::Bishop(Bishop &&other) noexcept : 
    Piece(std::move(other)) {}

// Copy assignment
Bishop& Bishop::operator=(Bishop const &other) {
    if (this != &other) {
        Piece::operator=(other);
    }
    return *this;
}

// Move assignment
Bishop& Bishop::operator=(Bishop &&other) noexcept {
    if (this != &other) {
        Piece::operator=(std::move(other));
    }
    return *this;
}

std::vector<OldBoardMove> Bishop::getStandardMoves(ChessBoard const &chessBoard, BoardSquare const &fromSquare, bool onlyAttackingMoves) const {
    std::vector<OldBoardMove> moves;
    if (chessBoard.isSquareOnBoard(fromSquare)) {
        for (std::pair<int, int> const &bishopDirection : bishopDirections) {
            BoardSquare toSquare(fromSquare.getBoardRow() + bishopDirection.first, fromSquare.getBoardCol() + bishopDirection.second);
            while (chessBoard.isSquareEmpty(toSquare) || chessBoard.isSquareOtherTeam(toSquare, pieceInfo.pieceData.team)) {
                moves.emplace_back(OldBoardMove::createBasicMove(MoveType::STANDARD, pieceInfo.pieceData, fromSquare, toSquare, toSquare, chessBoard.getPieceInfoAt(toSquare)));
                if (chessBoard.isSquareOtherTeam(toSquare, pieceInfo.pieceData.team)) {
                    break;
                }
                toSquare = BoardSquare(toSquare.getBoardRow() + bishopDirection.first, toSquare.getBoardCol() + bishopDirection.second);
            }
        }
    }
    return moves;
}
