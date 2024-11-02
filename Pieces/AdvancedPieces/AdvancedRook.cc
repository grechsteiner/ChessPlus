// AdvancedRook.cc

#include <vector>

#include "AdvancedRook.h"
#include "BoardMove.h"
#include "ChessBoard.h"


// Basic ctor
AdvancedRook::AdvancedRook(Team team, PieceDirection pieceDirection, bool hasMoved) :
    ComplicatedCloneable<Piece, Rook, AdvancedRook>(PieceLevel::ADVANCED, team, pieceDirection, hasMoved) {}

// Copy ctor
AdvancedRook::AdvancedRook(AdvancedRook const &other) : 
    ComplicatedCloneable<Piece, Rook, AdvancedRook>(other) {}

// Move ctor
AdvancedRook::AdvancedRook(AdvancedRook &&other) noexcept : 
    ComplicatedCloneable<Piece, Rook, AdvancedRook>(std::move(other)) {}

// Copy assignment
AdvancedRook& AdvancedRook::operator=(AdvancedRook const &other) {
    if (this != &other) {
        Rook::operator=(other);
    }
    return *this;
}

// Move assignment
AdvancedRook& AdvancedRook::operator=(AdvancedRook &&other) noexcept {
    if (this != &other) {
        Rook::operator=(std::move(other));
    }
    return *this;
}

std::vector<BoardMove> AdvancedRook::getMovesImpl(ChessBoard const &chessBoard, BoardSquare const &fromSquare, bool onlyAttackingMoves) const {
    std::vector<BoardSquare> const additionalToSquares = { 
        BoardSquare(fromSquare.getBoardRow() + 1, fromSquare.getBoardCol() + 1),
        BoardSquare(fromSquare.getBoardRow() + 1, fromSquare.getBoardCol() - 1),
        BoardSquare(fromSquare.getBoardRow() - 1, fromSquare.getBoardCol() + 1),
        BoardSquare(fromSquare.getBoardRow() - 1, fromSquare.getBoardCol() - 1)
    };

    std::vector<BoardMove> additionalMoves;
    if (chessBoard.isSquareOnBoard(fromSquare)) {
        for (BoardSquare const &toSquare : additionalToSquares) {
            if (chessBoard.isSquareEmpty(toSquare) || chessBoard.isSquareOtherTeam(toSquare, pieceInfo.pieceData.team)) {
                additionalMoves.emplace_back(BoardMove::createBasicMove(MoveType::STANDARD, pieceInfo.pieceData, fromSquare, toSquare, toSquare, chessBoard.getPieceInfoAt(toSquare)));
            }
        }
    }

    std::vector<BoardMove> moves = getStandardMoves(chessBoard, fromSquare, onlyAttackingMoves);
    moves.insert(moves.end(), additionalMoves.begin(), additionalMoves.end());
    return moves;
}
