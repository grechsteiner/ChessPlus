// BasicKnight.h

#ifndef BasicKnight_h
#define BasicKnight_h

#include <memory>
#include <vector>

#include "BoardMove.h"
#include "BoardSquare.h"
#include "ChessBoard.h"
#include "ComplicatedCloneable.h"
#include "Constants.h"
#include "Knight.h"
#include "Piece.h"


/**
 * BasicKnight Knight Piece Class
 */
class BasicKnight final : public ComplicatedCloneable<Piece, Knight, BasicKnight> {
private:
    std::vector<std::unique_ptr<BoardMove>> getMovesImpl(std::unique_ptr<ChessBoard> const &chessBoard, BoardSquare const &fromSquare, bool onlyAttackingMoves) const override;
    
public:
    explicit BasicKnight(Team team, PieceDirection pieceDirection, bool hasMoved);
    BasicKnight(BasicKnight const &other);
    BasicKnight(BasicKnight &&other) noexcept;
    BasicKnight& operator=(BasicKnight const &other);
    BasicKnight& operator=(BasicKnight &&other) noexcept;
    virtual ~BasicKnight() = default;
};


#endif /* BasicKnight_h */
