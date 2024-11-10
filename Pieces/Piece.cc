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
Piece::Piece(PieceData const &pieceData, PieceInfo const &pieceInfo) :
    pieceData(pieceData), pieceInfo(pieceInfo) {}

// Move ctor
Piece::Piece(Piece &&other) noexcept :
    pieceData(std::move(other.pieceData)), pieceInfo(std::move(other.pieceInfo)) {}

// Move assignment
Piece& Piece::operator=(Piece &&other) noexcept {
    if (this != &other) {
        pieceData = std::move(other.pieceData);
        pieceInfo = std::move(other.pieceInfo);
    }
    return *this;
}

std::vector<std::unique_ptr<BoardMove>> Piece::getMoves(std::unique_ptr<ChessBoard> const &chessBoard, BoardSquare const &fromSquare, bool onlyAttackingMoves) const { return getMovesImpl(chessBoard, fromSquare, onlyAttackingMoves); }
std::unique_ptr<Piece> Piece::clone() const { return cloneImpl(); }

PieceData const& Piece::getPieceData() const { return pieceData; }
PieceInfo const& Piece::getPieceInfo() const { return pieceInfo; }
