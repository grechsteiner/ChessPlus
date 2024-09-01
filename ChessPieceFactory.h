// ChessPieceFactory.h

#ifndef ChessPieceFactory_h
#define ChessPieceFactory_h

#include <memory>
#include <optional>

#include "Piece.h"


class ChessPieceFactory {
public:
    static std::unique_ptr<Piece> createPiece(Team team, PieceType pieceType, PieceDirection pieceDirection, bool hasMoved, std::optional<int> pieceScore = std::nullopt);
    static std::unique_ptr<Piece> createEmptyPiece();
};


#endif /* ChessPieceFactory_h */
