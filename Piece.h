// Piece.h

#ifndef Piece_h
#define Piece_h

#include <vector>
#include <memory>

#include "PieceInfo.h"

class IChessBoard;
class BoardSquare;
class BoardMove;


/**
 * Abstract Piece Class
 * Represents a piece on a chessboard
 */
class Piece {

private:
    virtual std::vector<BoardMove> getMovesImpl(IChessBoard const &chessBoard, BoardSquare const &fromSquare, bool onlyAttackingMoves) const = 0;
    virtual std::unique_ptr<Piece> cloneImpl() const = 0;
    
protected:
    explicit Piece(PieceInfo const &pieceInfo);
    Piece(Piece const &other) = default;
    Piece(Piece &&other) noexcept;
    Piece& operator=(Piece const &other) = default;
    Piece& operator=(Piece &&other) noexcept;

    PieceInfo pieceInfo;

public:
    std::vector<BoardMove> getMoves(IChessBoard const &chessBoard, BoardSquare const &fromSquare, bool onlyAttackingMoves) const;
    std::unique_ptr<Piece> clone() const;
    
    PieceInfo const& getPieceInfo() const;

    virtual ~Piece() = default;
};


#endif /* Piece_h */
