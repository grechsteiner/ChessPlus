// Pawn.h

#ifndef Pawn_h
#define Pawn_h

#include <vector>
#include <utility>

#include "Constants.h"
#include "Piece.h"
#include "Cloneable.h"

#include "ChessBoard.h"
struct BoardSquare;
class BoardMove;


/**
 * Pawn Piece Class
 */
class Pawn : public Piece {    
protected:
    explicit Pawn(PieceLevel pieceLevel, Team team, PieceDirection pieceDirection, bool hasMoved);
    Pawn(Pawn const &other);
    Pawn(Pawn &&other) noexcept;
    Pawn& operator=(Pawn const &other);
    Pawn& operator=(Pawn &&other) noexcept;
    virtual ~Pawn() = default;

    std::vector<std::unique_ptr<BoardMove>> getStandardMoves(std::unique_ptr<ChessBoard> const &chessBoard, BoardSquare const &fromSquare, bool onlyAttackingMoves) const override;
    std::pair<int, int> getPawnDirection() const;

    // Appends new move to moves
    // Creates all variants if promotion needed
    void addMoves(std::vector<std::unique_ptr<BoardMove>> &moves, std::unique_ptr<ChessBoard> const &chessBoard, BoardSquare const &fromSquare, BoardSquare const &toSquare, BoardSquare const &captureSquare, bool doesEnableEnpassant) const;
};


#endif /* Pawn */
