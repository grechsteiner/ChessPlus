// PieceFactory.cc

#include "PieceFactory.h"

#include <cassert>
#include <memory>

#include "AdvancedPieceFactory.h"
#include "BasicPieceFactory.h"
#include "Piece.h"
#include "PieceData.h"


/*
 * Static
 *
 * Returns a Piece instance
 */
std::unique_ptr<Piece> PieceFactory::createPiece(PieceData const &pieceData) {
    switch (pieceData.pieceLevel) {
        case PieceLevel::BASIC:
            return BasicPieceFactory::createPiece(pieceData);
        case PieceLevel::ADVANCED:
            return AdvancedPieceFactory::createPiece(pieceData);
        default:
            assert(false);
    }
}
