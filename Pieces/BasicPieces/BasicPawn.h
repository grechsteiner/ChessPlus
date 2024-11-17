// BasicPawn.h

#ifndef BasicPawn_h
#define BasicPawn_h

#include <memory>
#include <vector>

#include "BoardMove.h"
#include "BoardSquare.h"
#include "ChessBoard.h"
#include "ComplicatedCloneable.h"
#include "Constants.h"
#include "Pawn.h"
#include "Piece.h"


/**
 * BasicPawn Pawn Piece Class
 */
class BasicPawn final : public ComplicatedCloneable<Piece, Pawn, BasicPawn> {
private:
    std::vector<std::unique_ptr<BoardMove>> getMovesImpl(std::unique_ptr<ChessBoard> const &chessBoard, BoardSquare const &fromSquare, bool onlyAttackingMoves) const override;
    
public:
    explicit BasicPawn(Team team, PieceDirection pieceDirection, bool hasMoved);
    BasicPawn(BasicPawn const &other);
    BasicPawn(BasicPawn &&other) noexcept;
    BasicPawn& operator=(BasicPawn const &other);
    BasicPawn& operator=(BasicPawn &&other) noexcept;
    virtual ~BasicPawn() = default;
};


#endif /* BasicPawn_h */
