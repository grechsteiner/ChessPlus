// PieceFactory.cc

#include <memory>
#include <cassert>

#include "PieceFactory.h"
#include "Piece.h"
#include "Constants.h"

#include "BasicPieceFactory.h"
#include "AdvancedPieceFactory.h"


// Static
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
