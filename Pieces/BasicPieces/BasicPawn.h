// BasicPawn.h

#ifndef BasicPawn_h
#define BasicPawn_h

#include <vector>
#include <utility>
#include <set>

#include "Constants.h"
#include "Piece.h"
#include "Cloneable.h"
#include "ComplicatedCloneable.h"
#include "PieceData.h"
#include "Pawn.h"

class ChessBoard;
class BoardSquare;
class BoardMove;


/**
 * BasicPawn Piece Class
 */
class BasicPawn final : public ComplicatedCloneable<Piece, Pawn, BasicPawn> {
private:
    std::vector<BoardMove> getMovesImpl(ChessBoard const &chessBoard, BoardSquare const &fromSquare, bool onlyAttackingMoves) const override;
public:
    explicit BasicPawn(Team team, PieceDirection pieceDirection, bool hasMoved);
    BasicPawn(BasicPawn const &other);
    BasicPawn(BasicPawn &&other) noexcept;
    BasicPawn& operator=(BasicPawn const &other);
    BasicPawn& operator=(BasicPawn &&other) noexcept;
    virtual ~BasicPawn() = default;
};


#endif /* BasicPawn_h */
