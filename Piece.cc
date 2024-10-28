// Piece.cc

#include <vector>
#include <memory>
#include <utility>

#include "Piece.h"
#include "Constants.h"
#include "PieceData.h"
#include "IChessBoard.h"
#include "BoardSquare.h"
#include "BoardMove.h"


// Basic ctor
Piece::Piece(PieceType pieceType, Team team, PieceDirection pieceDirection, bool hasMoved, int pieceScore, std::string const &image, std::string const &display) :
    pieceData(PieceData(pieceType, team, pieceDirection, hasMoved, pieceScore, image, display)) {}

// Move ctor
Piece::Piece(Piece &&other) noexcept :
    pieceData(std::move(other.pieceData)) {}

// Move assignment
Piece& Piece::operator=(Piece &&other) noexcept {
    if (this != &other) {
        pieceData = std::move(other.pieceData);
    }
    return *this;
}

std::vector<BoardMove> Piece::getMoves(IChessBoard const &chessBoard, BoardSquare const &fromSquare, bool onlyAttackingMoves) const { return getMovesImpl(chessBoard, fromSquare, onlyAttackingMoves); }
std::unique_ptr<Piece> Piece::clone() const { return cloneImpl(); }

PieceData const& Piece::getPieceData() const { return pieceData; }
