// Queen.h

#ifndef Queen_h
#define Queen_h

#include <vector>
#include <utility>
#include <set>

#include "Constants.h"
#include "Piece.h"
#include "Cloneable.h"

class ChessBoard;
struct BoardSquare;
class BoardMove;


/**
 * Queen Piece Class
 */
class Queen : public Piece {
private:
    static std::set<std::pair<int, int>> const queenDirections;

protected:
    explicit Queen(PieceLevel pieceLevel, Team team, PieceDirection pieceDirection, bool hasMoved);
    Queen(Queen const &other);
    Queen(Queen &&other) noexcept;
    Queen& operator=(Queen const &other);
    Queen& operator=(Queen &&other) noexcept;
    virtual ~Queen() = default;

    std::vector<std::unique_ptr<BoardMove>> getStandardMoves(std::unique_ptr<ChessBoard> const &chessBoard, BoardSquare const &fromSquare, bool onlyAttackingMoves) const override;
};


#endif /* Queen_h */
