// AdvancedPieceFactory.h

#ifndef AdvancedPieceFactory_h
#define AdvancedPieceFactory_h

#include <memory>
#include <optional>

class Piece;
struct PieceData;


class AdvancedPieceFactory {
public:
    static std::unique_ptr<Piece> createPiece(PieceData const &pieceData);
};


#endif /* AdvancedPieceFactory_h */
