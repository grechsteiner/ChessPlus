// Queen.cc

#include <vector>
#include <utility>
#include <set>

#include "Queen.h"
#include "Constants.h"
#include "Piece.h"
#include "PieceCloneable.h"
#include "ChessBoard.h"
#include "BoardSquare.h"
#include "BoardMove.h"


// Static
std::set<std::pair<int, int>> const Queen::queenDirections = { 
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
Queen::Queen(Team team, PieceDirection pieceDirection, bool hasMoved, int pieceScore) :
    Cloneable<Piece, Queen>(PieceType::QUEEN, team, pieceDirection, hasMoved, pieceScore, "♛", "Q") {}

// Copy ctor
Queen::Queen(Queen const &other) : 
    Cloneable<Piece, Queen>(other) {}

// Move ctor
Queen::Queen(Queen &&other) noexcept : 
    Cloneable<Piece, Queen>(std::move(other)) {}

// Copy assignment
Queen& Queen::operator=(Queen const &other) {
    if (this != &other) {
        Piece::operator=(other);
    }
    return *this;
}

// Move assignment
Queen& Queen::operator=(Queen &&other) noexcept {
    if (this != &other) {
        Piece::operator=(std::move(other));
    }
    return *this;
}

std::vector<BoardMove> Queen::getMovesImpl(ChessBoard const &chessBoard, BoardSquare const &fromSquare, bool onlyAttackingMoves) const {
    std::vector<BoardMove> moves;
    if (chessBoard.isSquareOnBoard(fromSquare)) {
        for (std::pair<int, int> const &queenDirection : queenDirections) {
            BoardSquare toSquare(fromSquare.getBoardRow() + queenDirection.first, fromSquare.getBoardCol() + queenDirection.second);
            while (chessBoard.isSquareEmpty(toSquare) || chessBoard.isSquareOtherTeam(toSquare, pieceInfo.getTeam())) {
                moves.emplace_back(BoardMove::createBasicMove(MoveType::STANDARD, pieceInfo, fromSquare, toSquare, toSquare, chessBoard.getPieceInfoAt(toSquare)));
                if (chessBoard.isSquareOtherTeam(toSquare, pieceInfo.getTeam())) {
                    break;
                }
                toSquare = BoardSquare(toSquare.getBoardRow() + queenDirection.first, toSquare.getBoardCol() + queenDirection.second);
            }
        }
    }
    return moves;
}
