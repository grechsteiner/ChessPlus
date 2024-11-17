// AdvancedPieceFactory.h

#ifndef AdvancedPieceFactory_h
#define AdvancedPieceFactory_h

#include <memory>

#include "Piece.h"
#include "PieceData.h"


/**
 * Factory for creating Advanced Piece instances
 */
class AdvancedPieceFactory final {
public:
    static std::unique_ptr<Piece> createPiece(PieceData const &pieceData);
};


#endif /* AdvancedPieceFactory_h */
