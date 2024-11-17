// Rook.h

#ifndef Rook_h
#define Rook_h

#include <memory>
#include <vector>

#include "BoardMove.h"
#include "BoardSquare.h"
#include "ChessBoard.h"
#include "Constants.h"
#include "MoveDirection.h"
#include "Piece.h"


/**
 * AbstractRook Piece Class
 */
class Rook : public Piece {
private:
    static std::vector<MoveDirection> const rookMoveDirections;
protected:
    explicit Rook(PieceLevel pieceLevel, Team team, PieceDirection pieceDirection, bool hasMoved, char32_t image);
    Rook(Rook const &other);
    Rook(Rook &&other) noexcept;
    Rook& operator=(Rook const &other);
    Rook& operator=(Rook &&other) noexcept;
    virtual ~Rook() = default;

    std::vector<std::unique_ptr<BoardMove>> getStandardMoves(std::unique_ptr<ChessBoard> const &chessBoard, BoardSquare const &fromSquare, bool onlyAttackingMoves) const override;
};


#endif /* Rook_h */
