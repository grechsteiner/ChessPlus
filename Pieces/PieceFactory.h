// PieceFactory.h

#ifndef PieceFactory_h
#define PieceFactory_h

#include <memory>

#include "Piece.h"
#include "PieceData.h"


/**
 * Factory for creating Piece instances
 */
class PieceFactory final {
public:
    static std::unique_ptr<Piece> createPiece(PieceData const &pieceData);
};


#endif /* PieceFactory_u */
