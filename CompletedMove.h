// CompletedMove.h

#ifndef CompletedMove_h
#define CompletedMove_h

#include <vector>
#include <memory>

#include "Constants.h"
#include "Move.h"
#include "Piece.h"

class CompletedMove : public Move {

private:

    // The captured piece information
    int capturedRow;
    char capturedCol;

    Color capturedColor;
    PieceType capturedPieceType;
    PieceDirection capturedPieceDirection;
    bool capturedHasMoved;
    int capturedPieceScore;

    // The piece that was actually moved
    bool movedHasMoved;

    // Standard, enpassant, castle
    // TODO: Might not need this
    MoveType moveType;

    // Castle move
    std::unique_ptr<CompletedMove> castleMove;

public:
    CompletedMove(Move const &move, std::vector<std::vector<std::unique_ptr<Piece>>> const &grid);

    // Getters
    int getCapturedRow() const;
    char getCapturedCol() const;
    Color getCapturedColor() const;
    PieceType getCapturedPieceType() const;
    PieceDirection getCapturedPieceDirection() const;
    bool getCapturedHasMoved() const;
    int getCapturedScore() const;

    bool getMovedHasMoved() const;

    MoveType getMoveType() const;
    const std::unique_ptr<CompletedMove>& getCastleMove() const;
};


#endif /* CompletedMove*/
