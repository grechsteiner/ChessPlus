// AdvancedQueen.h

#ifndef AdvancedQueen_h
#define AdvancedQueen_h

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
 * AdvancedQueen Queen Piece Class
 */
class AdvancedQueen final : public ComplicatedCloneable<Piece, Queen, AdvancedQueen> {
private:
    std::vector<std::unique_ptr<BoardMove>> getMovesImpl(std::unique_ptr<ChessBoard> const &chessBoard, BoardSquare const &fromSquare, bool onlyAttackingMoves) const override;
    
public:
    explicit AdvancedQueen(Team team, PieceDirection pieceDirection, bool hasMoved);
    AdvancedQueen(AdvancedQueen const &other);
    AdvancedQueen(AdvancedQueen &&other) noexcept;
    AdvancedQueen& operator=(AdvancedQueen const &other);
    AdvancedQueen& operator=(AdvancedQueen &&other) noexcept;
    virtual ~AdvancedQueen() = default;
};


#endif /* AdvancedQueen_h */
