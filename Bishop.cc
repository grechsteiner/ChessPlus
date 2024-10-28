// Bishop.cc

#include <vector>
#include <utility>
#include <set>

#include "Bishop.h"
#include "Constants.h"
#include "Piece.h"
#include "Cloneable.h"
#include "IChessBoard.h"
#include "BoardSquare.h"
#include "BoardMove.h"

// Static
std::set<std::pair<int, int>> const Bishop::bishopDirections = { 
    {-1, -1},  
    {-1, 1}, 
    {1, -1}, 
    {1, 1} 
};

// Basic ctor
Bishop::Bishop(Team team, PieceLevel pieceLevel, PieceDirection pieceDirection, bool hasMoved) :
    Cloneable<Piece, Bishop>(PieceInfo(PieceData(PieceType::BISHOP, PieceLevel::BASIC, team, pieceDirection, hasMoved), 3, "♝", "B")) {}

// Copy ctor
Bishop::Bishop(Bishop const &other) : 
    Cloneable<Piece, Bishop>(other) {}

// Move ctor
Bishop::Bishop(Bishop &&other) noexcept : 
    Cloneable<Piece, Bishop>(std::move(other)) {}

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

std::vector<BoardMove> Bishop::getMovesImpl(IChessBoard const &chessBoard, BoardSquare const &fromSquare, bool onlyAttackingMoves) const {
    std::vector<BoardMove> moves;
    if (chessBoard.isSquareOnBoard(fromSquare)) {
        for (std::pair<int, int> const &bishopDirection : bishopDirections) {
            BoardSquare toSquare(fromSquare.getBoardRow() + bishopDirection.first, fromSquare.getBoardCol() + bishopDirection.second);
            while (chessBoard.isSquareEmpty(toSquare) || chessBoard.isSquareOtherTeam(toSquare, pieceInfo.pieceData.team)) {
                moves.emplace_back(BoardMove::createBasicMove(MoveType::STANDARD, pieceInfo.pieceData, fromSquare, toSquare, toSquare, chessBoard.getPieceDataAt(toSquare)));
                if (chessBoard.isSquareOtherTeam(toSquare, pieceInfo.pieceData.team)) {
                    break;
                }
                toSquare = BoardSquare(toSquare.getBoardRow() + bishopDirection.first, toSquare.getBoardCol() + bishopDirection.second);
            }
        }
    }
    return moves;
}
