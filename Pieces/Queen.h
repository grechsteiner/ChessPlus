// Queen.h

#ifndef Queen_h
#define Queen_h

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
 * Abstract Queen Piece Class
 */
class Queen : public Piece {
private:
    static std::vector<MoveDirection> const queenMoveDirections;

protected:
    explicit Queen(PieceLevel pieceLevel, Team team, PieceDirection pieceDirection, bool hasMoved, char32_t image);
    Queen(Queen const &other);
    Queen(Queen &&other) noexcept;
    Queen& operator=(Queen const &other);
    Queen& operator=(Queen &&other) noexcept;
    virtual ~Queen() = default;

    std::vector<std::unique_ptr<BoardMove>> getStandardMoves(std::unique_ptr<ChessBoard> const &chessBoard, BoardSquare const &fromSquare, bool onlyAttackingMoves) const override;
};


#endif /* Queen_h */
