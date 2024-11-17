// BasicRook.h

#ifndef BasicRook_h
#define BasicRook_h

#include <memory>
#include <vector>

#include "BoardMove.h"
#include "BoardSquare.h"
#include "ChessBoard.h"
#include "ComplicatedCloneable.h"
#include "Constants.h"
#include "Piece.h"
#include "Rook.h"


/**
 * BasicRook Rook Piece Class
 */
class BasicRook final : public ComplicatedCloneable<Piece, Rook, BasicRook> {
private:
    std::vector<std::unique_ptr<BoardMove>> getMovesImpl(std::unique_ptr<ChessBoard> const &chessBoard, BoardSquare const &fromSquare, bool onlyAttackingMoves) const override;

public:
    explicit BasicRook(Team team, PieceDirection pieceDirection, bool hasMoved);
    BasicRook(BasicRook const &other);
    BasicRook(BasicRook &&other) noexcept;
    BasicRook& operator=(BasicRook const &other);
    BasicRook& operator=(BasicRook &&other) noexcept;
    virtual ~BasicRook() = default;
};


#endif /* BasicRook_h */
