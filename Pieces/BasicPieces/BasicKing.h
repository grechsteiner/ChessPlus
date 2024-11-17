// BasicKing.h

#ifndef BasicKing_h
#define BasicKing_h

#include <memory>
#include <vector>

#include "BoardMove.h"
#include "BoardSquare.h"
#include "ChessBoard.h"
#include "ComplicatedCloneable.h"
#include "Constants.h"
#include "King.h"
#include "Piece.h"


/**
 * BasicKing King Piece Class
 */
class BasicKing final : public ComplicatedCloneable<Piece, King, BasicKing> {
private:
    std::vector<std::unique_ptr<BoardMove>> getMovesImpl(std::unique_ptr<ChessBoard> const &chessBoard, BoardSquare const &fromSquare, bool onlyAttackingMoves) const override;

public:
    explicit BasicKing(Team team, PieceDirection pieceDirection, bool hasMoved);
    BasicKing(BasicKing const &other);
    BasicKing(BasicKing &&other) noexcept;
    BasicKing& operator=(BasicKing const &other);
    BasicKing& operator=(BasicKing &&other) noexcept;
    virtual ~BasicKing() = default;
};


#endif /* BasicKing_h */
