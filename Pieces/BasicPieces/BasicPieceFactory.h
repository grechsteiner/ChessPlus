// BasicPieceFactory.h

#ifndef BasicPieceFactory_h
#define BasicPieceFactory_h

#include <memory>
#include <optional>

class Piece;
struct PieceData;


class BasicPieceFactory final {
public:
    static std::unique_ptr<Piece> createPiece(PieceData const &pieceData);
};


#endif /* BasicPieceFactory_h */
