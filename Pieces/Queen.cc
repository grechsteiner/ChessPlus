// Queen.cc

#include <vector>
#include <utility>
#include <set>

#include "Queen.h"
#include "Constants.h"
#include "Piece.h"
#include "Cloneable.h"
#include "ChessBoard.h"
#include "BoardSquare.h"
#include "BoardMove.h"
#include "BoardMoveFactory.h"


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
Queen::Queen(PieceLevel pieceLevel, Team team, PieceDirection pieceDirection, bool hasMoved) :
    Piece(PieceData(PieceType::QUEEN, PieceLevel::BASIC, team, pieceDirection, hasMoved), PieceInfo(9, "♛", "Q")) {}

// Copy ctor
Queen::Queen(Queen const &other) : 
    Piece(other) {}

// Move ctor
Queen::Queen(Queen &&other) noexcept : 
    Piece(std::move(other)) {}

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

std::vector<std::unique_ptr<BoardMove>> Queen::getStandardMoves(std::unique_ptr<ChessBoard> const &chessBoard, BoardSquare const &fromSquare, bool onlyAttackingMoves) const {
    std::vector<std::unique_ptr<BoardMove>> moves;
    if (chessBoard->isSquareOnBoard(fromSquare)) {
        for (std::pair<int, int> const &queenDirection : queenDirections) {
            BoardSquare toSquare(fromSquare.boardRow + queenDirection.first, fromSquare.boardCol + queenDirection.second);
            while (chessBoard->isSquareEmpty(toSquare) || chessBoard->isSquareOtherTeam(toSquare, pieceData.team)) {
                moves.emplace_back(BoardMoveFactory::createStandardMove(fromSquare, toSquare, toSquare, false, pieceData, chessBoard->getPieceDataAt(toSquare)));
                if (chessBoard->isSquareOtherTeam(toSquare, pieceData.team)) {
                    break;
                }
                toSquare = BoardSquare(toSquare.boardRow + queenDirection.first, toSquare.boardCol + queenDirection.second);
            }
        }
    }
    return moves;
}
