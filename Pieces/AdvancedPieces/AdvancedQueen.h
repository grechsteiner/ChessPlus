// AdvancedQueen.h

#ifndef AdvancedQueen_h
#define AdvancedQueen_h

#include <vector>
#include <utility>
#include <set>

#include "Constants.h"
#include "Piece.h"
#include "Cloneable.h"
#include "ComplicatedCloneable.h"
#include "PieceData.h"
#include "Queen.h"

class ChessBoard;
struct BoardSquare;
class BoardMove;


/**
 * AdvancedQueen Piece Class
 */
class AdvancedQueen final : public ComplicatedCloneable<Piece, Queen, AdvancedQueen> {
private:
    std::vector<std::unique_ptr<BoardMove>> getMovesImpl(ChessBoard const &chessBoard, BoardSquare const &fromSquare, bool onlyAttackingMoves) const override;
public:
    explicit AdvancedQueen(Team team, PieceDirection pieceDirection, bool hasMoved);
    AdvancedQueen(AdvancedQueen const &other);
    AdvancedQueen(AdvancedQueen &&other) noexcept;
    AdvancedQueen& operator=(AdvancedQueen const &other);
    AdvancedQueen& operator=(AdvancedQueen &&other) noexcept;
    virtual ~AdvancedQueen() = default;
};


#endif /* AdvancedQueen_h */
