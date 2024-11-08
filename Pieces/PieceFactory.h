// PieceFactory.h

#ifndef PieceFactory_h
#define PieceFactory_h

#include <memory>
#include <optional>

class Piece;
struct PieceData;


class PieceFactory final {
public:
    static std::unique_ptr<Piece> createPiece(PieceData const &pieceData);
};


#endif /* PieceFactory_u */
