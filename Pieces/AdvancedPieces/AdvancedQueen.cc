// AdvancedQueen.cc

#include "AdvancedQueen.h"

#include <memory>
#include <utility>
#include <vector>

#include "BoardMove.h"
#include "BoardMoveFactory.h"
#include "BoardSquare.h"
#include "ChessBoard.h"
#include "Constants.h"
#include "Piece.h"
#include "Queen.h"


/*
 * Basic ctor
 */
AdvancedQueen::AdvancedQueen(Team team, PieceDirection pieceDirection, bool hasMoved) :
    ComplicatedCloneable<Piece, Queen, AdvancedQueen>(PieceLevel::ADVANCED, team, pieceDirection, hasMoved, char32_t(U'♕')) { }

/*
 * Copy ctor
 */
AdvancedQueen::AdvancedQueen(AdvancedQueen const &other) : 
    ComplicatedCloneable<Piece, Queen, AdvancedQueen>(other) { }

/*
 * Move ctor
 */
AdvancedQueen::AdvancedQueen(AdvancedQueen &&other) noexcept : 
    ComplicatedCloneable<Piece, Queen, AdvancedQueen>(std::move(other)) { }

/*
 * Copy assignment
 */
AdvancedQueen& AdvancedQueen::operator=(AdvancedQueen const &other) {
    if (this != &other) {
        Queen::operator=(other);
    }
    return *this;
}

/*
 * Move assignment
 */
AdvancedQueen& AdvancedQueen::operator=(AdvancedQueen &&other) noexcept {
    if (this != &other) {
        Queen::operator=(std::move(other));
    }
    return *this;
}

/*
 * Returns all pseudo legal moves for an AdvancedQueen Queen Piece
 */
std::vector<std::unique_ptr<BoardMove>> AdvancedQueen::getMovesImpl(std::unique_ptr<ChessBoard> const &chessBoard, BoardSquare const &fromSquare, bool onlyAttackingMoves) const {
    std::vector<BoardSquare> const additionalToSquares = { 
        BoardSquare(fromSquare.boardRow + 1, fromSquare.boardCol + 2),
        BoardSquare(fromSquare.boardRow + 1, fromSquare.boardCol - 2),
        BoardSquare(fromSquare.boardRow - 1, fromSquare.boardCol + 2),
        BoardSquare(fromSquare.boardRow - 1, fromSquare.boardCol - 2),
        BoardSquare(fromSquare.boardRow + 2, fromSquare.boardCol + 1),
        BoardSquare(fromSquare.boardRow + 2, fromSquare.boardCol - 1),
        BoardSquare(fromSquare.boardRow - 2, fromSquare.boardCol + 1),
        BoardSquare(fromSquare.boardRow - 2, fromSquare.boardCol - 1)
    };

    std::vector<std::unique_ptr<BoardMove>> moves = getStandardMoves(chessBoard, fromSquare, onlyAttackingMoves);
    if (chessBoard->isSquareOnBoard(fromSquare)) {
        for (BoardSquare const &toSquare : additionalToSquares) {
            if (chessBoard->isSquareEmpty(toSquare) || chessBoard->isSquareOtherTeam(toSquare, pieceData.team)) {
                moves.emplace_back(BoardMoveFactory::createStandardMove(fromSquare, toSquare, toSquare, false, pieceData, chessBoard->getPieceDataAt(toSquare)));
            }
        }
    }
    return moves;
}
