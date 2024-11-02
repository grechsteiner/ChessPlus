// AdvancedKing.cc

#include <vector>

#include "AdvancedKing.h"
#include "BoardMove.h"
#include "ChessBoard.h"

// Basic ctor
AdvancedKing::AdvancedKing(Team team, PieceDirection pieceDirection, bool hasMoved) :
    ComplicatedCloneable<Piece, King, AdvancedKing>(PieceLevel::ADVANCED, team, pieceDirection, hasMoved) {}

// Copy ctor
AdvancedKing::AdvancedKing(AdvancedKing const &other) : 
    ComplicatedCloneable<Piece, King, AdvancedKing>(other) {}

// Move ctor
AdvancedKing::AdvancedKing(AdvancedKing &&other) noexcept : 
    ComplicatedCloneable<Piece, King, AdvancedKing>(std::move(other)) {}

// Copy assignment
AdvancedKing& AdvancedKing::operator=(AdvancedKing const &other) {
    if (this != &other) {
        King::operator=(other);
    }
    return *this;
}

// Move assignment
AdvancedKing& AdvancedKing::operator=(AdvancedKing &&other) noexcept {
    if (this != &other) {
        King::operator=(std::move(other));
    }
    return *this;
}

std::vector<BoardMove> AdvancedKing::getMovesImpl(ChessBoard const &chessBoard, BoardSquare const &fromSquare, bool onlyAttackingMoves) const {
    std::vector<BoardSquare> const additionalToSquares = { 
        BoardSquare(fromSquare.getBoardRow() + 2, fromSquare.getBoardCol() + 2),
        BoardSquare(fromSquare.getBoardRow() + 2, fromSquare.getBoardCol() - 2),
        BoardSquare(fromSquare.getBoardRow() - 2, fromSquare.getBoardCol() + 2),
        BoardSquare(fromSquare.getBoardRow() - 2, fromSquare.getBoardCol() - 2)
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
