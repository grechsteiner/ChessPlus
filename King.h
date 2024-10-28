// King.h

#ifndef King_h
#define King_h

#include <vector>
#include <utility>
#include <set>

#include "Constants.h"
#include "Piece.h"
#include "Cloneable.h"

class IChessBoard;
class BoardSquare;
class BoardMove;


/**
 * King Piece Class
 */
class King : public Cloneable<Piece, King> {
private:
    static std::set<std::pair<int, int>> const kingDirections;
    std::vector<BoardMove> getMovesImpl(IChessBoard const &chessBoard, BoardSquare const &fromSquare, bool onlyAttackingMoves) const override;
    bool checkCommonCastleInfo(IChessBoard const &chessBoard, BoardSquare const &fromSquare, BoardSquare const &toSquare, BoardSquare const &rookFromSquare, BoardSquare const &rookToSquare) const;
public:
    explicit King(PieceLevel pieceLevel, Team team, PieceDirection pieceDirection, bool hasMoved);
    King(King const &other);
    King(King &&other) noexcept;
    King& operator=(King const &other);
    King& operator=(King &&other) noexcept;
    virtual ~King() = default;
};


#endif /* King_h */
