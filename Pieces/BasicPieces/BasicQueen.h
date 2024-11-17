// BasicQueen.h

#ifndef BasicQueen_h
#define BasicQueen_h

#include <memory>
#include <vector>

#include "BoardMove.h"
#include "BoardSquare.h"
#include "ChessBoard.h"
#include "ComplicatedCloneable.h"
#include "Constants.h"
#include "Piece.h"
#include "Queen.h"


/**
 * BasicQueen Queen Piece Class
 */
class BasicQueen final : public ComplicatedCloneable<Piece, Queen, BasicQueen> {
private:
    std::vector<std::unique_ptr<BoardMove>> getMovesImpl(std::unique_ptr<ChessBoard> const &chessBoard, BoardSquare const &fromSquare, bool onlyAttackingMoves) const override;

public:
    explicit BasicQueen(Team team, PieceDirection pieceDirection, bool hasMoved);
    BasicQueen(BasicQueen const &other);
    BasicQueen(BasicQueen &&other) noexcept;
    BasicQueen& operator=(BasicQueen const &other);
    BasicQueen& operator=(BasicQueen &&other) noexcept;
    virtual ~BasicQueen() = default;
};


#endif /* BasicQueen_h */
