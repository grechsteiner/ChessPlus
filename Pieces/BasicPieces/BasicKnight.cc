// BasicKnight.cc

#include "BasicKnight.h"

#include <memory>
#include <utility>
#include <vector>

#include "BoardMove.h"
#include "BoardSquare.h"
#include "ChessBoard.h"
#include "Constants.h"
#include "Knight.h"
#include "Piece.h"


/*
 * Basic ctor
 */
BasicKnight::BasicKnight(Team team, PieceDirection pieceDirection, bool hasMoved) :
    ComplicatedCloneable<Piece, Knight, BasicKnight>(PieceLevel::BASIC, team, pieceDirection, hasMoved, char32_t(U'♞')) { }

/*
 * Copy ctor
 */
BasicKnight::BasicKnight(BasicKnight const &other) : 
    ComplicatedCloneable<Piece, Knight, BasicKnight>(other) { }

/*
 * Move ctor
 */
BasicKnight::BasicKnight(BasicKnight &&other) noexcept : 
    ComplicatedCloneable<Piece, Knight, BasicKnight>(std::move(other)) { }

/*
 * Copy assignment
 */
BasicKnight& BasicKnight::operator=(BasicKnight const &other) {
    if (this != &other) {
        Knight::operator=(other);
    }
    return *this;
}

/*
 * Move assignment
 */
BasicKnight& BasicKnight::operator=(BasicKnight &&other) noexcept {
    if (this != &other) {
        Knight::operator=(std::move(other));
    }
    return *this;
}

/*
 * Returns all pseudo legal moves for a BasicKnight Knight Piece
 */
std::vector<std::unique_ptr<BoardMove>> BasicKnight::getMovesImpl(std::unique_ptr<ChessBoard> const &chessBoard, BoardSquare const &fromSquare, bool onlyAttackingMoves) const {
    return getStandardMoves(chessBoard, fromSquare, onlyAttackingMoves);
}
