// BasicQueen.h

#ifndef BasicQueen_h
#define BasicQueen_h

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
 * BasicQueen Piece Class
 */
class BasicQueen final : public ComplicatedCloneable<Piece, Queen, BasicQueen> {
private:
    std::vector<std::unique_ptr<BoardMove>> getMovesImpl(ChessBoard const &chessBoard, BoardSquare const &fromSquare, bool onlyAttackingMoves) const override;
public:
    explicit BasicQueen(Team team, PieceDirection pieceDirection, bool hasMoved);
    BasicQueen(BasicQueen const &other);
    BasicQueen(BasicQueen &&other) noexcept;
    BasicQueen& operator=(BasicQueen const &other);
    BasicQueen& operator=(BasicQueen &&other) noexcept;
    virtual ~BasicQueen() = default;
};


#endif /* BasicQueen_h */
