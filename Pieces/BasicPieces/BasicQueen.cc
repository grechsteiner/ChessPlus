// BasicQueen.cc

#include <vector>

#include "BasicQueen.h"
#include "BoardMove.h"

// Basic ctor
BasicQueen::BasicQueen(Team team, PieceDirection pieceDirection, bool hasMoved) :
    ComplicatedCloneable<Piece, Queen, BasicQueen>(PieceLevel::BASIC, team, pieceDirection, hasMoved) {}

// Copy ctor
BasicQueen::BasicQueen(BasicQueen const &other) : 
    ComplicatedCloneable<Piece, Queen, BasicQueen>(other) {}

// Move ctor
BasicQueen::BasicQueen(BasicQueen &&other) noexcept : 
    ComplicatedCloneable<Piece, Queen, BasicQueen>(std::move(other)) {}

// Copy assignment
BasicQueen& BasicQueen::operator=(BasicQueen const &other) {
    if (this != &other) {
        Queen::operator=(other);
    }
    return *this;
}

// Move assignment
BasicQueen& BasicQueen::operator=(BasicQueen &&other) noexcept {
    if (this != &other) {
        Queen::operator=(std::move(other));
    }
    return *this;
}

std::vector<BoardMove> BasicQueen::getMovesImpl(ChessBoard const &chessBoard, BoardSquare const &fromSquare, bool onlyAttackingMoves) const {
    return getStandardMoves(chessBoard, fromSquare, onlyAttackingMoves);
}
