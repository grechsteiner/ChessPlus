// AdvancedQueen.cc

#include <vector>

#include "AdvancedQueen.h"
#include "OldBoardMove.h"
#include "ChessBoard.h"


// Basic ctor
AdvancedQueen::AdvancedQueen(Team team, PieceDirection pieceDirection, bool hasMoved) :
    ComplicatedCloneable<Piece, Queen, AdvancedQueen>(PieceLevel::ADVANCED, team, pieceDirection, hasMoved) {}

// Copy ctor
AdvancedQueen::AdvancedQueen(AdvancedQueen const &other) : 
    ComplicatedCloneable<Piece, Queen, AdvancedQueen>(other) {}

// Move ctor
AdvancedQueen::AdvancedQueen(AdvancedQueen &&other) noexcept : 
    ComplicatedCloneable<Piece, Queen, AdvancedQueen>(std::move(other)) {}

// Copy assignment
AdvancedQueen& AdvancedQueen::operator=(AdvancedQueen const &other) {
    if (this != &other) {
        Queen::operator=(other);
    }
    return *this;
}

// Move assignment
AdvancedQueen& AdvancedQueen::operator=(AdvancedQueen &&other) noexcept {
    if (this != &other) {
        Queen::operator=(std::move(other));
    }
    return *this;
}

std::vector<OldBoardMove> AdvancedQueen::getMovesImpl(ChessBoard const &chessBoard, BoardSquare const &fromSquare, bool onlyAttackingMoves) const {
    std::vector<BoardSquare> const additionalToSquares = { 
        BoardSquare(fromSquare.getBoardRow() + 1, fromSquare.getBoardCol() + 2),
        BoardSquare(fromSquare.getBoardRow() + 1, fromSquare.getBoardCol() - 2),
        BoardSquare(fromSquare.getBoardRow() - 1, fromSquare.getBoardCol() + 2),
        BoardSquare(fromSquare.getBoardRow() - 1, fromSquare.getBoardCol() - 2),
        BoardSquare(fromSquare.getBoardRow() + 2, fromSquare.getBoardCol() + 1),
        BoardSquare(fromSquare.getBoardRow() + 2, fromSquare.getBoardCol() - 1),
        BoardSquare(fromSquare.getBoardRow() - 2, fromSquare.getBoardCol() + 1),
        BoardSquare(fromSquare.getBoardRow() - 2, fromSquare.getBoardCol() - 1)
    };

    std::vector<OldBoardMove> additionalMoves;
    if (chessBoard.isSquareOnBoard(fromSquare)) {
        for (BoardSquare const &toSquare : additionalToSquares) {
            if (chessBoard.isSquareEmpty(toSquare) || chessBoard.isSquareOtherTeam(toSquare, pieceInfo.pieceData.team)) {
                additionalMoves.emplace_back(OldBoardMove::createBasicMove(MoveType::STANDARD, pieceInfo.pieceData, fromSquare, toSquare, toSquare, chessBoard.getPieceInfoAt(toSquare)));
            }
        }
    }

    std::vector<OldBoardMove> moves = getStandardMoves(chessBoard, fromSquare, onlyAttackingMoves);
    moves.insert(moves.end(), additionalMoves.begin(), additionalMoves.end());
    return moves;
}
