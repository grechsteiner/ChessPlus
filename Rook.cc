// Rook.cc

#include <vector>
#include <utility>
#include <set>

#include "Rook.h"
#include "Constants.h"
#include "Piece.h"
#include "Cloneable.h"
#include "IChessBoard.h"
#include "BoardSquare.h"
#include "BoardMove.h"


// Static
std::set<std::pair<int, int>> const Rook::rookDirections = { 
    {-1, 0}, 
    {0, -1}, 
    {0, 1}, 
    {1, 0}, 
};

// Basic ctor
Rook::Rook(Team team, PieceDirection pieceDirection, bool hasMoved, int pieceScore) :
    Cloneable<Piece, Rook>(PieceType::ROOK, team, pieceDirection, hasMoved, pieceScore, "♜", "R") {}

// Copy ctor
Rook::Rook(Rook const &other) : 
    Cloneable<Piece, Rook>(other) {}

// Move ctor
Rook::Rook(Rook &&other) noexcept : 
    Cloneable<Piece, Rook>(std::move(other)) {}

// Copy assignment
Rook& Rook::operator=(Rook const &other) {
    if (this != &other) {
        Piece::operator=(other);
    }
    return *this;
}

// Move assignment
Rook& Rook::operator=(Rook &&other) noexcept {
    if (this != &other) {
        Piece::operator=(std::move(other));
    }
    return *this;
}

std::vector<BoardMove> Rook::getMovesImpl(IChessBoard const &chessBoard, BoardSquare const &fromSquare, bool onlyAttackingMoves) const {
    std::vector<BoardMove> moves;
    if (chessBoard.isSquareOnBoard(fromSquare)) {
        for (std::pair<int, int> const &rookDirection : rookDirections) {
            BoardSquare toSquare(fromSquare.getBoardRow() + rookDirection.first, fromSquare.getBoardCol() + rookDirection.second);
            while (chessBoard.isSquareEmpty(toSquare) || chessBoard.isSquareOtherTeam(toSquare, pieceData.getTeam())) {
                moves.emplace_back(BoardMove::createBasicMove(MoveType::STANDARD, pieceData, fromSquare, toSquare, toSquare, chessBoard.getPieceDataAt(toSquare)));
                if (chessBoard.isSquareOtherTeam(toSquare, pieceData.getTeam())) {
                    break;
                }
                toSquare = BoardSquare(toSquare.getBoardRow() + rookDirection.first, toSquare.getBoardCol() + rookDirection.second);
            }
        }
    }
    return moves;
}
