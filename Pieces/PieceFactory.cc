// ChessPieceFactory.cc

#include <memory>
#include <cassert>

#include "ChessPieceFactory.h"
#include "Constants.h"

#include "Piece.h"
#include "King.h"
#include "Queen.h"
#include "Rook.h"
#include "Bishop.h"
#include "Knight.h"
#include "Pawn.h"

#include "BasicKing.h"
#include "AdvancedKing.h"
#include "BasicQueen.h"
#include "AdvancedQueen.h"
#include "BasicRook.h"
#include "AdvancedRook.h"
#include "BasicBishop.h"
#include "AdvancedBishop.h"
#include "BasicKnight.h"
#include "AdvancedKnight.h"
#include "BasicPawn.h"
#include "AdvancedPawn.h"

// Static
std::unique_ptr<Piece> ChessPieceFactory::createPiece(PieceData const &pieceData) {
    switch (pieceData.pieceType) {
        case PieceType::KING:
            if (pieceData.pieceLevel == PieceLevel::BASIC) {
                return std::make_unique<BasicKing>(pieceData.team, pieceData.pieceDirection, pieceData.hasMoved);
            } else {
                return std::make_unique<AdvancedKing>(pieceData.team, pieceData.pieceDirection, pieceData.hasMoved);
            }
        case PieceType::QUEEN:
            if (pieceData.pieceLevel == PieceLevel::BASIC) {
                return std::make_unique<BasicQueen>(pieceData.team, pieceData.pieceDirection, pieceData.hasMoved);
            } else {
                return std::make_unique<AdvancedQueen>(pieceData.team, pieceData.pieceDirection, pieceData.hasMoved);
            }
        case PieceType::ROOK:
            if (pieceData.pieceLevel == PieceLevel::BASIC) {
                return std::make_unique<BasicRook>(pieceData.team, pieceData.pieceDirection, pieceData.hasMoved);
            } else {
                return std::make_unique<AdvancedRook>(pieceData.team, pieceData.pieceDirection, pieceData.hasMoved);
            }
        case PieceType::BISHOP:
            if (pieceData.pieceLevel == PieceLevel::BASIC) {
                return std::make_unique<BasicBishop>(pieceData.team, pieceData.pieceDirection, pieceData.hasMoved);
            } else {
                return std::make_unique<AdvancedBishop>(pieceData.team, pieceData.pieceDirection, pieceData.hasMoved);
            }
        case PieceType::KNIGHT:
            if (pieceData.pieceLevel == PieceLevel::BASIC) {
                return std::make_unique<BasicKnight>(pieceData.team, pieceData.pieceDirection, pieceData.hasMoved);
            } else {
                return std::make_unique<AdvancedKnight>(pieceData.team, pieceData.pieceDirection, pieceData.hasMoved);
            }
        case PieceType::PAWN:
            if (pieceData.pieceLevel == PieceLevel::BASIC) {
                return std::make_unique<BasicPawn>(pieceData.team, pieceData.pieceDirection, pieceData.hasMoved);
            } else {
                return std::make_unique<AdvancedPawn>(pieceData.team, pieceData.pieceDirection, pieceData.hasMoved);
            }
        default:
            assert(false);
    }
}

