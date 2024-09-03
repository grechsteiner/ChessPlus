// Bishop.cc

#include <vector>
#include <utility>
#include <set>

#include "Bishop.h"
#include "Constants.h"
#include "Piece.h"
#include "PieceCloneable.h"
#include "ChessBoard.h"
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
Bishop::Bishop(Team team, PieceDirection pieceDirection, bool hasMoved, int pieceScore) :
    Cloneable<Piece, Bishop>(PieceType::BISHOP, team, pieceDirection, hasMoved, pieceScore, "♝", "B") {}

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

std::vector<BoardMove> Bishop::getMovesImpl(ChessBoard const &chessBoard, BoardSquare const &fromSquare, bool onlyAttackingMoves) const {
    std::vector<BoardMove> moves;
    if (chessBoard.isSquareOnBoard(fromSquare)) {
        for (std::pair<int, int> const &bishopDirection : bishopDirections) {
            BoardSquare toSquare(fromSquare.getBoardRow() + bishopDirection.first, fromSquare.getBoardCol() + bishopDirection.second);
            while (chessBoard.isSquareEmpty(toSquare) || chessBoard.isSquareOtherTeam(toSquare, pieceInfo.getTeam())) {
                moves.emplace_back(BoardMove::createBasicMove(MoveType::STANDARD, pieceInfo, fromSquare, toSquare, toSquare, chessBoard.getPieceInfoAt(toSquare)));
                if (chessBoard.isSquareOtherTeam(toSquare, pieceInfo.getTeam())) {
                    break;
                }
                toSquare = BoardSquare(toSquare.getBoardRow() + bishopDirection.first, toSquare.getBoardCol() + bishopDirection.second);
            }
        }
    }
    return moves;
}
