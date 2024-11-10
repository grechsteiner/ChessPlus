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
#include "BoardMove.h"
#include "BoardMoveFactory.h"

// Static
std::set<std::pair<int, int>> const Bishop::bishopDirections = { 
    {-1, -1},  
    {-1, 1}, 
    {1, -1}, 
    {1, 1} 
};

// Basic ctor
Bishop::Bishop(PieceLevel pieceLevel, Team team, PieceDirection pieceDirection, bool hasMoved) :
    Piece(PieceData(PieceType::BISHOP, pieceLevel, team, pieceDirection, hasMoved), PieceInfo(3, "♝", "B")) {}

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

std::vector<std::unique_ptr<BoardMove>> Bishop::getStandardMoves(std::unique_ptr<ChessBoard> const &chessBoard, BoardSquare const &fromSquare, bool onlyAttackingMoves) const {
    std::vector<std::unique_ptr<BoardMove>> moves;
    if (chessBoard->isSquareOnBoard(fromSquare)) {
        for (std::pair<int, int> const &bishopDirection : bishopDirections) {
            BoardSquare toSquare(fromSquare.boardRow + bishopDirection.first, fromSquare.boardCol + bishopDirection.second);
            while (chessBoard->isSquareEmpty(toSquare) || chessBoard->isSquareOtherTeam(toSquare, pieceData.team)) {
                moves.emplace_back(BoardMoveFactory::createStandardMove(fromSquare, toSquare, toSquare, false, pieceData, chessBoard->getPieceDataAt(toSquare)));
                if (chessBoard->isSquareOtherTeam(toSquare, pieceData.team)) {
                    break;
                }
                toSquare = BoardSquare(toSquare.boardRow + bishopDirection.first, toSquare.boardCol + bishopDirection.second);
            }
        }
    }
    return moves;
}
