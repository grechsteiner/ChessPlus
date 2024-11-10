// AdvancedBishop.cc

#include <vector>

#include "AdvancedBishop.h"
#include "BoardMove.h"
#include "BoardMoveFactory.h"
#include "ChessBoard.h"


// Basic ctor
AdvancedBishop::AdvancedBishop(Team team, PieceDirection pieceDirection, bool hasMoved) :
    ComplicatedCloneable<Piece, Bishop, AdvancedBishop>(PieceLevel::ADVANCED, team, pieceDirection, hasMoved) {}

// Copy ctor
AdvancedBishop::AdvancedBishop(AdvancedBishop const &other) : 
    ComplicatedCloneable<Piece, Bishop, AdvancedBishop>(other) {}

// Move ctor
AdvancedBishop::AdvancedBishop(AdvancedBishop &&other) noexcept : 
    ComplicatedCloneable<Piece, Bishop, AdvancedBishop>(std::move(other)) {}

// Copy assignment
AdvancedBishop& AdvancedBishop::operator=(AdvancedBishop const &other) {
    if (this != &other) {
        Bishop::operator=(other);
    }
    return *this;
}

// Move assignment
AdvancedBishop& AdvancedBishop::operator=(AdvancedBishop &&other) noexcept {
    if (this != &other) {
        Bishop::operator=(std::move(other));
    }
    return *this;
}

std::vector<std::unique_ptr<BoardMove>> AdvancedBishop::getMovesImpl(std::unique_ptr<ChessBoard> const &chessBoard, BoardSquare const &fromSquare, bool onlyAttackingMoves) const {
    std::vector<BoardSquare> const additionalToSquares = { 
        BoardSquare(fromSquare.boardRow + 0, fromSquare.boardCol + 1),
        BoardSquare(fromSquare.boardRow + 0, fromSquare.boardCol - 1),
        BoardSquare(fromSquare.boardRow + 1, fromSquare.boardCol + 0),
        BoardSquare(fromSquare.boardRow - 1, fromSquare.boardCol + 0)
    };

    std::vector<std::unique_ptr<BoardMove>> moves = getStandardMoves(chessBoard, fromSquare, onlyAttackingMoves);
    if (chessBoard->isSquareOnBoard(fromSquare)) {
        for (BoardSquare const &toSquare : additionalToSquares) {
            if (chessBoard->isSquareEmpty(toSquare) || chessBoard->isSquareOtherTeam(toSquare, pieceData.team)) {
                moves.emplace_back(BoardMoveFactory::createStandardMove(fromSquare, toSquare, toSquare, false, pieceData, chessBoard->getPieceDataAt(toSquare)));
            }
        }
    }
    return moves;
}
