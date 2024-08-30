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
std::unique_ptr<Piece> ChessPieceFactory::createPiece(Team team, PieceType pieceType, PieceDirection pieceDirection, bool hasMoved, int pieceScore) {
    switch(pieceType) {
        case PieceType::KING:
            return pieceScore == -1 
                ? std::make_unique<King>(team, pieceDirection, hasMoved)
                : std::make_unique<King>(team, pieceDirection, hasMoved, pieceScore);
        case PieceType::QUEEN:
            return pieceScore == -1 
                ? std::make_unique<Queen>(team, pieceDirection, hasMoved)
                : std::make_unique<Queen>(team, pieceDirection, hasMoved, pieceScore);
        case PieceType::ROOK:
            return pieceScore == -1 
                ? std::make_unique<Rook>(team, pieceDirection, hasMoved)
                : std::make_unique<Rook>(team, pieceDirection, hasMoved, pieceScore);
        case PieceType::BISHOP:
            return pieceScore == -1 
                ? std::make_unique<Bishop>(team, pieceDirection, hasMoved)
                : std::make_unique<Bishop>(team, pieceDirection, hasMoved, pieceScore);
        case PieceType::KNIGHT:
            return pieceScore == -1 
                ? std::make_unique<Knight>(team, pieceDirection, hasMoved)
                : std::make_unique<Knight>(team, pieceDirection, hasMoved, pieceScore);
        case PieceType::PAWN:
            return pieceScore == -1 
                ? std::make_unique<Pawn>(team, pieceDirection, hasMoved)
                : std::make_unique<Pawn>(team, pieceDirection, hasMoved, pieceScore);
        case PieceType::EMPTY:
        default:
            return pieceScore == -1 
                ? std::make_unique<Empty>(team, pieceDirection, hasMoved)
                : std::make_unique<Empty>(team, pieceDirection, hasMoved, pieceScore);
    }
}

// Static
std::unique_ptr<Piece> ChessPieceFactory::createEmptyPiece() {
    return std::make_unique<Empty>(Team::TEAM_NONE, PieceDirection::BLANK, 0, false);
}
