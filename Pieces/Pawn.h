// Pawn.h

#ifndef Pawn_h
#define Pawn_h

#include <memory>
#include <utility>
#include <vector>

#include "BoardMove.h"
#include "BoardSquare.h"
#include "ChessBoard.h"
#include "Constants.h"
#include "MoveDirection.h"
#include "Piece.h"


/**
 * Abstract Pawn Piece Class
 */
class Pawn : public Piece {    
protected:
    explicit Pawn(PieceLevel pieceLevel, Team team, PieceDirection pieceDirection, bool hasMoved, char32_t image);
    Pawn(Pawn const &other);
    Pawn(Pawn &&other) noexcept;
    Pawn& operator=(Pawn const &other);
    Pawn& operator=(Pawn &&other) noexcept;
    virtual ~Pawn() = default;

    std::vector<std::unique_ptr<BoardMove>> getStandardMoves(std::unique_ptr<ChessBoard> const &chessBoard, BoardSquare const &fromSquare, bool onlyAttackingMoves) const override;

    MoveDirection getPawnMoveDirection() const;
    void addMoves(std::vector<std::unique_ptr<BoardMove>> &moves, std::unique_ptr<ChessBoard> const &chessBoard, BoardSquare const &fromSquare, BoardSquare const &toSquare, BoardSquare const &captureSquare, bool doesEnableEnpassant) const;
};


#endif /* Pawn */
