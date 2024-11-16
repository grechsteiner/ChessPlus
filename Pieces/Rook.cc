// Rook.cc

#include <vector>
#include <utility>
#include <set>

#include "Rook.h"
#include "Constants.h"
#include "Piece.h"
#include "Cloneable.h"
#include "ChessBoard.h"
#include "BoardSquare.h"
#include "BoardMove.h"
#include "BoardMoveFactory.h"


// Static
std::set<std::pair<int, int>> const Rook::rookDirections = { 
    {-1, 0}, 
    {0, -1}, 
    {0, 1}, 
    {1, 0}, 
};

// Basic ctor
Rook::Rook(PieceLevel pieceLevel, Team team, PieceDirection pieceDirection, bool hasMoved, char32_t image) :
    Piece(PieceData(PieceType::ROOK, PieceLevel::BASIC, team, pieceDirection, hasMoved), PieceInfo(5, image)) {}

// Copy ctor
Rook::Rook(Rook const &other) : 
    Piece(other) {}

// Move ctor
Rook::Rook(Rook &&other) noexcept : 
    Piece(std::move(other)) {}

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

std::vector<std::unique_ptr<BoardMove>> Rook::getStandardMoves(std::unique_ptr<ChessBoard> const &chessBoard, BoardSquare const &fromSquare, bool onlyAttackingMoves) const {
    std::vector<std::unique_ptr<BoardMove>> moves;
    if (chessBoard->isSquareOnBoard(fromSquare)) {
        for (std::pair<int, int> const &rookDirection : rookDirections) {
            BoardSquare toSquare(fromSquare.boardRow + rookDirection.first, fromSquare.boardCol + rookDirection.second);
            while (chessBoard->isSquareEmpty(toSquare) || chessBoard->isSquareOtherTeam(toSquare, pieceData.team)) {
                moves.emplace_back(BoardMoveFactory::createStandardMove(fromSquare, toSquare, toSquare, false, pieceData, chessBoard->getPieceDataAt(toSquare)));
                if (chessBoard->isSquareOtherTeam(toSquare, pieceData.team)) {
                    break;
                }
                toSquare = BoardSquare(toSquare.boardRow + rookDirection.first, toSquare.boardCol + rookDirection.second);
            }
        }
    }
    return moves;
}
