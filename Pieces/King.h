// King.h

#ifndef King_h
#define King_h

#include <memory>
#include <vector>

#include "BoardMove.h"
#include "BoardSquare.h"
#include "ChessBoard.h"
#include "Constants.h"
#include "MoveDirection.h"
#include "Piece.h"


/**
 * Abstract King Piece Class
 */
class King : public Piece {
private:
    static std::vector<MoveDirection> const kingMoveDirections;
    bool checkCommonCastleInfo(std::unique_ptr<ChessBoard> const &chessBoard, BoardSquare const &fromSquare, BoardSquare const &toSquare, BoardSquare const &rookFromSquare, BoardSquare const &rookToSquare) const;

protected:
    explicit King(PieceLevel pieceLevel, Team team, PieceDirection pieceDirection, bool hasMoved, char32_t image);
    King(King const &other);
    King(King &&other) noexcept;
    King& operator=(King const &other);
    King& operator=(King &&other) noexcept;
    virtual ~King() = default;

    std::vector<std::unique_ptr<BoardMove>> getStandardMoves(std::unique_ptr<ChessBoard> const &chessBoard, BoardSquare const &fromSquare, bool onlyAttackingMoves) const override;
};


#endif /* King_h */
