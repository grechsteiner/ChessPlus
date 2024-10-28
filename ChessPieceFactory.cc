// ChessPieceFactory.cc

#include <memory>
#include <cassert>

#include "ChessPieceFactory.h"
#include "Constants.h"
#include "Piece.h"
#include "King.h"
#include "Queen.h"
#include "Rook.h"
#include "Bishop.h"
#include "Knight.h"
#include "Pawn.h"

// Static
std::unique_ptr<Piece> ChessPieceFactory::createPiece(PieceData const &pieceData) {
    switch (pieceData.pieceType) {
        case PieceType::KING:
            return std::make_unique<King>(pieceData.pieceLevel, pieceData.team, pieceData.pieceDirection, pieceData.hasMoved);
        case PieceType::QUEEN:
            return std::make_unique<Queen>(pieceData.pieceLevel, pieceData.team, pieceData.pieceDirection, pieceData.hasMoved);
        case PieceType::ROOK:
            return std::make_unique<Rook>(pieceData.pieceLevel, pieceData.team, pieceData.pieceDirection, pieceData.hasMoved);
        case PieceType::BISHOP:
            return std::make_unique<Bishop>(pieceData.pieceLevel, pieceData.team, pieceData.pieceDirection, pieceData.hasMoved);
        case PieceType::KNIGHT:
            return std::make_unique<Knight>(pieceData.pieceLevel, pieceData.team, pieceData.pieceDirection, pieceData.hasMoved);
        case PieceType::PAWN:
            return std::make_unique<Pawn>(pieceData.pieceLevel, pieceData.team, pieceData.pieceDirection, pieceData.hasMoved);
        default:
            assert(false);
    }
}

