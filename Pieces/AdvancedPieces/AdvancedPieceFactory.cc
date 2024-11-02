// AdvancedPieceFactory.cc

#include <memory>
#include <cassert>

#include "AdvancedPieceFactory.h"
#include "Piece.h"
#include "Constants.h"

#include "AdvancedKing.h"
#include "AdvancedQueen.h"
#include "AdvancedRook.h"
#include "AdvancedBishop.h"
#include "AdvancedKnight.h"
#include "AdvancedPawn.h"

// Static
std::unique_ptr<Piece> AdvancedPieceFactory::createPiece(PieceData const &pieceData) {
    switch (pieceData.pieceType) {
        case PieceType::KING:
            return std::make_unique<AdvancedKing>(pieceData.team, pieceData.pieceDirection, pieceData.hasMoved);
        case PieceType::QUEEN:
            return std::make_unique<AdvancedQueen>(pieceData.team, pieceData.pieceDirection, pieceData.hasMoved);
        case PieceType::ROOK:
            return std::make_unique<AdvancedRook>(pieceData.team, pieceData.pieceDirection, pieceData.hasMoved);
        case PieceType::BISHOP:
            return std::make_unique<AdvancedBishop>(pieceData.team, pieceData.pieceDirection, pieceData.hasMoved);
        case PieceType::KNIGHT:
            return std::make_unique<AdvancedKnight>(pieceData.team, pieceData.pieceDirection, pieceData.hasMoved);
        case PieceType::PAWN:
            return std::make_unique<AdvancedPawn>(pieceData.team, pieceData.pieceDirection, pieceData.hasMoved);
        default:
            assert(false);
    }
}

