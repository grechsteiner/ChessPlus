// AdvancedKnight.cc

#include <vector>

#include "AdvancedKnight.h"
#include "BoardMove.h"
#include "ChessBoard.h"

// Basic ctor
AdvancedKnight::AdvancedKnight(Team team, PieceDirection pieceDirection, bool hasMoved) :
    ComplicatedCloneable<Piece, Knight, AdvancedKnight>(PieceLevel::BASIC, team, pieceDirection, hasMoved) {}

// Copy ctor
AdvancedKnight::AdvancedKnight(AdvancedKnight const &other) : 
    ComplicatedCloneable<Piece, Knight, AdvancedKnight>(other) {}

// Move ctor
AdvancedKnight::AdvancedKnight(AdvancedKnight &&other) noexcept : 
    ComplicatedCloneable<Piece, Knight, AdvancedKnight>(std::move(other)) {}

// Copy assignment
AdvancedKnight& AdvancedKnight::operator=(AdvancedKnight const &other) {
    if (this != &other) {
        Knight::operator=(other);
    }
    return *this;
}

// Move assignment
AdvancedKnight& AdvancedKnight::operator=(AdvancedKnight &&other) noexcept {
    if (this != &other) {
        Knight::operator=(std::move(other));
    }
    return *this;
}

std::vector<BoardMove> AdvancedKnight::getMovesImpl(ChessBoard const &chessBoard, BoardSquare const &fromSquare, bool onlyAttackingMoves) const {
    std::vector<BoardSquare> const additionalToSquares = { 
        BoardSquare(fromSquare.getBoardRow() + 1, fromSquare.getBoardCol() + 3),
        BoardSquare(fromSquare.getBoardRow() + 1, fromSquare.getBoardCol() - 3),
        BoardSquare(fromSquare.getBoardRow() - 1, fromSquare.getBoardCol() + 3),
        BoardSquare(fromSquare.getBoardRow() - 1, fromSquare.getBoardCol() - 3),
        BoardSquare(fromSquare.getBoardRow() + 3, fromSquare.getBoardCol() + 1),
        BoardSquare(fromSquare.getBoardRow() + 3, fromSquare.getBoardCol() - 1),
        BoardSquare(fromSquare.getBoardRow() - 3, fromSquare.getBoardCol() + 1),
        BoardSquare(fromSquare.getBoardRow() - 3, fromSquare.getBoardCol() - 1)
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
