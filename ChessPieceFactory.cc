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
std::unique_ptr<Piece> ChessPieceFactory::createPiece(Color pieceColor, PieceType pieceType, PieceDirection pieceDirection, bool hasMoved, int pieceScore) {
    switch(pieceType) {
        case PieceType::KING:
            return pieceScore == -1 
                ? std::make_unique<King>(pieceColor, pieceDirection, hasMoved)
                : std::make_unique<King>(pieceColor, pieceDirection, hasMoved, pieceScore);
        case PieceType::QUEEN:
            return pieceScore == -1 
                ? std::make_unique<Queen>(pieceColor, pieceDirection, hasMoved)
                : std::make_unique<Queen>(pieceColor, pieceDirection, hasMoved, pieceScore);
        case PieceType::ROOK:
            return pieceScore == -1 
                ? std::make_unique<Rook>(pieceColor, pieceDirection, hasMoved)
                : std::make_unique<Rook>(pieceColor, pieceDirection, hasMoved, pieceScore);
        case PieceType::BISHOP:
            return pieceScore == -1 
                ? std::make_unique<Bishop>(pieceColor, pieceDirection, hasMoved)
                : std::make_unique<Bishop>(pieceColor, pieceDirection, hasMoved, pieceScore);
        case PieceType::KNIGHT:
            return pieceScore == -1 
                ? std::make_unique<Knight>(pieceColor, pieceDirection, hasMoved)
                : std::make_unique<Knight>(pieceColor, pieceDirection, hasMoved, pieceScore);
        case PieceType::PAWN:
            return pieceScore == -1 
                ? std::make_unique<Pawn>(pieceColor, pieceDirection, hasMoved)
                : std::make_unique<Pawn>(pieceColor, pieceDirection, hasMoved, pieceScore);
        case PieceType::EMPTY:
        default:
            return pieceScore == -1 
                ? std::make_unique<Empty>(pieceColor, pieceDirection, hasMoved)
                : std::make_unique<Empty>(pieceColor, pieceDirection, hasMoved, pieceScore);
    }
}

// Static
std::unique_ptr<Piece> ChessPieceFactory::createEmptyPiece() {
    return std::make_unique<Empty>(Color::NONE, PieceDirection::BLANK, 0, false);
}
