// BasicQueen.cc

#include "BasicQueen.h"

#include <memory>
#include <utility>
#include <vector>

#include "Bishop.h"
#include "BoardMove.h"
#include "BoardSquare.h"
#include "ChessBoard.h"
#include "Constants.h"
#include "Piece.h"
#include "Queen.h"


/*
 * Basic ctor
 */
BasicQueen::BasicQueen(Team team, PieceDirection pieceDirection, bool hasMoved) :
    ComplicatedCloneable<Piece, Queen, BasicQueen>(PieceLevel::BASIC, team, pieceDirection, hasMoved, char32_t(U'♛')) { }

/*
 * Copy ctor
 */
BasicQueen::BasicQueen(BasicQueen const &other) : 
    ComplicatedCloneable<Piece, Queen, BasicQueen>(other) { }

/*
 * Move ctor
 */
BasicQueen::BasicQueen(BasicQueen &&other) noexcept : 
    ComplicatedCloneable<Piece, Queen, BasicQueen>(std::move(other)) { }

/*
 * Copy assignment
 */
BasicQueen& BasicQueen::operator=(BasicQueen const &other) {
    if (this != &other) {
        Queen::operator=(other);
    }
    return *this;
}

/*
 * Move assignment
 */
BasicQueen& BasicQueen::operator=(BasicQueen &&other) noexcept {
    if (this != &other) {
        Queen::operator=(std::move(other));
    }
    return *this;
}

/*
 * Returns all pseudo legal moves for a BasicQueen Queen Piece
 */
std::vector<std::unique_ptr<BoardMove>> BasicQueen::getMovesImpl(std::unique_ptr<ChessBoard> const &chessBoard, BoardSquare const &fromSquare, bool onlyAttackingMoves) const {
    return getStandardMoves(chessBoard, fromSquare, onlyAttackingMoves);
}
