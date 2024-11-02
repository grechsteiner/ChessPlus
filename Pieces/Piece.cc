// Piece.cc

#include <vector>
#include <memory>
#include <utility>

#include "Piece.h"
#include "PieceInfo.h"
#include "ChessBoard.h"
#include "BoardSquare.h"
#include "BoardMove.h"


// Basic ctor
Piece::Piece(PieceInfo const &pieceInfo) :
    pieceInfo(pieceInfo) {}

// Move ctor
Piece::Piece(Piece &&other) noexcept :
    pieceInfo(std::move(other.pieceInfo)) {}

// Move assignment
Piece& Piece::operator=(Piece &&other) noexcept {
    if (this != &other) {
        pieceInfo = std::move(other.pieceInfo);
    }
    return *this;
}

std::vector<BoardMove> Piece::getMoves(ChessBoard const &chessBoard, BoardSquare const &fromSquare, bool onlyAttackingMoves) const { return getMovesImpl(chessBoard, fromSquare, onlyAttackingMoves); }
std::unique_ptr<Piece> Piece::clone() const { return cloneImpl(); }

PieceInfo const& Piece::getPieceInfo() const { return pieceInfo; }
