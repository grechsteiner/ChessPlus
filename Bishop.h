// Bishop.h

#ifndef Bishop_h
#define Bishop_h

#include <vector>
#include <utility>
#include <set>

#include "Constants.h"
#include "Piece.h"
#include "Cloneable.h"
#include "PieceData.h"

class IChessBoard;
class BoardSquare;
class BoardMove;


/**
 * Bishop Piece Class
 */
class Bishop : public Cloneable<Piece, Bishop> {
private:
    static std::set<std::pair<int, int>> const bishopDirections;
    std::vector<BoardMove> getMovesImpl(IChessBoard const &chessBoard, BoardSquare const &fromSquare, bool onlyAttackingMoves) const override;
public:
    explicit Bishop(PieceLevel pieceLevel, Team team, PieceDirection pieceDirection, bool hasMoved);
    Bishop(Bishop const &other);
    Bishop(Bishop &&other) noexcept;
    Bishop& operator=(Bishop const &other);
    Bishop& operator=(Bishop &&other) noexcept;
    virtual ~Bishop() = default;
};


#endif /* Bishop_h */
