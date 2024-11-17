// BasicBishop.h

#ifndef BasicBishop_h
#define BasicBishop_h

#include <memory>
#include <vector>

#include "Bishop.h"
#include "BoardMove.h"
#include "BoardSquare.h"
#include "ChessBoard.h"
#include "ComplicatedCloneable.h"
#include "Constants.h"
#include "Piece.h"


/**
 * BasicBishop Bishop Piece Class
 */
class BasicBishop final : public ComplicatedCloneable<Piece, Bishop, BasicBishop> {
private:
    std::vector<std::unique_ptr<BoardMove>> getMovesImpl(std::unique_ptr<ChessBoard> const &chessBoard, BoardSquare const &fromSquare, bool onlyAttackingMoves) const override;

public:
    explicit BasicBishop(Team team, PieceDirection pieceDirection, bool hasMoved);
    BasicBishop(BasicBishop const &other);
    BasicBishop(BasicBishop &&other) noexcept;
    BasicBishop& operator=(BasicBishop const &other);
    BasicBishop& operator=(BasicBishop &&other) noexcept;
    virtual ~BasicBishop() = default;
};


#endif /* BasicBishop_h */
