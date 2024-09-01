// ChessPieceFactory.cc

#include <memory>

#include "ChessPieceFactory.h"
#include "Constants.h"
#include "Piece.h"
#include "King.h"
#include "Queen.h"
#include "Rook.h"
#include "Bishop.h"
#include "Knight.h"
#include "Pawn.h"
#include "Empty.h"

// Static
std::unique_ptr<Piece> ChessPieceFactory::createPiece(Team team, PieceType pieceType, PieceDirection pieceDirection, bool hasMoved, std::optional<int> pieceScore) {
    switch(pieceType) {
        case PieceType::KING:
            return pieceScore.has_value()
                ? std::make_unique<King>(team, pieceDirection, hasMoved, pieceScore.value())
                : std::make_unique<King>(team, pieceDirection, hasMoved);
        case PieceType::QUEEN:
            return pieceScore.has_value()
                ? std::make_unique<Queen>(team, pieceDirection, hasMoved, pieceScore.value())
                : std::make_unique<Queen>(team, pieceDirection, hasMoved);
        case PieceType::ROOK:
            return pieceScore.has_value()
                ? std::make_unique<Rook>(team, pieceDirection, hasMoved, pieceScore.value())
                : std::make_unique<Rook>(team, pieceDirection, hasMoved);
        case PieceType::BISHOP:
            return pieceScore.has_value()
                ? std::make_unique<Bishop>(team, pieceDirection, hasMoved, pieceScore.value())
                : std::make_unique<Bishop>(team, pieceDirection, hasMoved);
        case PieceType::KNIGHT:
            return pieceScore.has_value()
                ? std::make_unique<Knight>(team, pieceDirection, hasMoved, pieceScore.value())
                : std::make_unique<Knight>(team, pieceDirection, hasMoved);
        case PieceType::PAWN:
            return pieceScore.has_value()
                ? std::make_unique<Pawn>(team, pieceDirection, hasMoved, pieceScore.value())
                : std::make_unique<Pawn>(team, pieceDirection, hasMoved);
        case PieceType::EMPTY:
        default:
            return pieceScore.has_value()
                ? std::make_unique<Empty>(team, pieceDirection, hasMoved, pieceScore.value())
                : std::make_unique<Empty>(team, pieceDirection, hasMoved);
    }
}

// Static
std::unique_ptr<Piece> ChessPieceFactory::createEmptyPiece() {
    return std::make_unique<Empty>(Team::TEAM_NONE, PieceDirection::BLANK, 0, false);
}
