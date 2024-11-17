// Knight.h

#ifndef Knight_h
#define Knight_h

#include <memory>
#include <utility>
#include <vector>

#include "BoardMove.h"
#include "BoardSquare.h"
#include "ChessBoard.h"
#include "Constants.h"
#include "MoveDirection.h"
#include "Piece.h"


/**
 * Abstract Knight Piece Class
 */
class Knight : public Piece {
private:
    static std::vector<MoveDirection> const knightMoveDirections;

protected:
    explicit Knight(PieceLevel pieceLevel, Team team, PieceDirection pieceDirection, bool hasMoved, char32_t image);
    Knight(Knight const &other);
    Knight(Knight &&other) noexcept;
    Knight& operator=(Knight const &other);
    Knight& operator=(Knight &&other) noexcept;
    virtual ~Knight() = default;

    std::vector<std::unique_ptr<BoardMove>> getStandardMoves(std::unique_ptr<ChessBoard> const &chessBoard, BoardSquare const &fromSquare, bool onlyAttackingMoves) const override;
};


#endif /* Knight_h */
