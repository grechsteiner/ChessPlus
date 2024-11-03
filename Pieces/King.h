// King.h

#ifndef King_h
#define King_h

#include <vector>
#include <utility>
#include <set>

#include "Constants.h"
#include "Piece.h"
#include "Cloneable.h"

class ChessBoard;
class BoardSquare;
class BoardMove;


/**
 * Abstract King Piece Class
 */
class King : public Piece {
private:
    static std::set<std::pair<int, int>> const kingDirections;
    bool checkCommonCastleInfo(ChessBoard const &chessBoard, BoardSquare const &fromSquare, BoardSquare const &toSquare, BoardSquare const &rookFromSquare, BoardSquare const &rookToSquare) const;

protected:
    explicit King(PieceLevel pieceLevel, Team team, PieceDirection pieceDirection, bool hasMoved);
    King(King const &other);
    King(King &&other) noexcept;
    King& operator=(King const &other);
    King& operator=(King &&other) noexcept;
    virtual ~King() = default;

    std::vector<std::unique_ptr<BoardMove>> getStandardMoves(ChessBoard const &chessBoard, BoardSquare const &fromSquare, bool onlyAttackingMoves) const override;
};


#endif /* King_h */
