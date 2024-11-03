// BasicRook.h

#ifndef BasicRook_h
#define BasicRook_h

#include <vector>
#include <utility>
#include <set>

#include "Constants.h"
#include "Piece.h"
#include "Cloneable.h"
#include "ComplicatedCloneable.h"
#include "PieceData.h"
#include "Rook.h"

class ChessBoard;
struct BoardSquare;
class BoardMove;


/**
 * BasicRook Piece Class
 */
class BasicRook final : public ComplicatedCloneable<Piece, Rook, BasicRook> {
private:
    std::vector<std::unique_ptr<BoardMove>> getMovesImpl(ChessBoard const &chessBoard, BoardSquare const &fromSquare, bool onlyAttackingMoves) const override;
public:
    explicit BasicRook(Team team, PieceDirection pieceDirection, bool hasMoved);
    BasicRook(BasicRook const &other);
    BasicRook(BasicRook &&other) noexcept;
    BasicRook& operator=(BasicRook const &other);
    BasicRook& operator=(BasicRook &&other) noexcept;
    virtual ~BasicRook() = default;
};


#endif /* BasicRook_h */
