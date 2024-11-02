// BasicBishop.h

#ifndef BasicBishop_h
#define BasicBishop_h

#include <vector>
#include <utility>
#include <set>

#include "Constants.h"
#include "Piece.h"
#include "Cloneable.h"
#include "ComplicatedCloneable.h"
#include "PieceData.h"
#include "Bishop.h"

class ChessBoard;
class BoardSquare;
class OldBoardMove;


/**
 * BasicBishop Piece Class
 */
class BasicBishop final : public ComplicatedCloneable<Piece, Bishop, BasicBishop> {
private:
    std::vector<OldBoardMove> getMovesImpl(ChessBoard const &chessBoard, BoardSquare const &fromSquare, bool onlyAttackingMoves) const override;
public:
    explicit BasicBishop(Team team, PieceDirection pieceDirection, bool hasMoved);
    BasicBishop(BasicBishop const &other);
    BasicBishop(BasicBishop &&other) noexcept;
    BasicBishop& operator=(BasicBishop const &other);
    BasicBishop& operator=(BasicBishop &&other) noexcept;
    virtual ~BasicBishop() = default;
};


#endif /* BasicBishop_h */
