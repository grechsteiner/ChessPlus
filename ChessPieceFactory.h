// ChessPieceFactory.h

#ifndef ChessPieceFactory_h
#define ChessPieceFactory_h

#include <memory>
#include <optional>

#include "Piece.h"
#include "PieceData.h"


class ChessPieceFactory {
public:
    static std::unique_ptr<Piece> createPiece(PieceData const &pieceData);
};


#endif /* ChessPieceFactory_h */
