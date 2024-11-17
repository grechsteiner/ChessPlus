// BasicPieceFactory.h

#ifndef BasicPieceFactory_h
#define BasicPieceFactory_h

#include <memory>

#include "Piece.h"
#include "PieceData.h"


/**
 * Factory for creating Basic Piece instances
 */
class BasicPieceFactory final {
public:
    static std::unique_ptr<Piece> createPiece(PieceData const &pieceData);
};


#endif /* BasicPieceFactory_h */
