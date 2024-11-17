// Piece.cc

#include "Piece.h"

#include <memory>
#include <utility>
#include <vector>

#include "PieceData.h"
#include "PieceInfo.h"
#include "ChessBoard.h"
#include "BoardSquare.h"
#include "BoardMove.h"


// Basic ctor
Piece::Piece(PieceData const &pieceData, PieceInfo const &pieceInfo) :
    pieceData(pieceData), pieceInfo(pieceInfo) { }

// Copy ctor
Piece::Piece(Piece const &other) :
    pieceData(other.pieceData), pieceInfo(other.pieceInfo) { }

// Move ctor
Piece::Piece(Piece &&other) noexcept :
    pieceData(std::move(other.pieceData)), pieceInfo(std::move(other.pieceInfo)) { }

// Copy assignment
Piece& Piece::operator=(Piece const &other) {
    if (this != &other) {
        pieceData = other.pieceData;
        pieceInfo = other.pieceInfo;
    }
    return *this;
}

// Move assignment
Piece& Piece::operator=(Piece &&other) noexcept {
    if (this != &other) {
        pieceData = std::move(other.pieceData);
        pieceInfo = std::move(other.pieceInfo);
    }
    return *this;
}

// Equality
bool Piece::operator==(Piece const &other) const {
    return
        pieceData == other.pieceData &&
        pieceInfo == other.pieceInfo;
}

// Inequality
bool Piece::operator!=(Piece const &other) const {
    return !(*this == other);
}

/* Public Virtual Methods */
std::vector<std::unique_ptr<BoardMove>> Piece::getMoves(std::unique_ptr<ChessBoard> const &chessBoard, BoardSquare const &fromSquare, bool onlyAttackingMoves) const { return getMovesImpl(chessBoard, fromSquare, onlyAttackingMoves); }
std::unique_ptr<Piece> Piece::clone() const { return cloneImpl(); }

/* Getters */
PieceData const& Piece::getPieceData() const { return pieceData; }
PieceInfo const& Piece::getPieceInfo() const { return pieceInfo; }
