// Piece.h

#ifndef Piece_h
#define Piece_h

#include <vector>
#include <memory>

#include "PieceInfo.h"

class ChessBoard;
class BoardSquare;
class BoardMove;


/**
 * Abstract Piece Class
 * Represents a piece on a chessboard
 */
class Piece {

private:
    virtual std::vector<BoardMove> getMovesImpl(ChessBoard const &chessBoard, BoardSquare const &fromSquare, bool onlyAttackingMoves) const = 0;
    virtual std::unique_ptr<Piece> cloneImpl() const = 0;
    
protected:
    explicit Piece(PieceInfo const &pieceInfo);
    Piece(Piece const &other) = default;
    Piece(Piece &&other) noexcept;
    Piece& operator=(Piece const &other) = default;
    Piece& operator=(Piece &&other) noexcept;

    PieceInfo pieceInfo;

    virtual std::vector<BoardMove> getStandardMoves(ChessBoard const &chessBoard, BoardSquare const &fromSquare, bool onlyAttackingMoves) const = 0;

public:
    std::vector<BoardMove> getMoves(ChessBoard const &chessBoard, BoardSquare const &fromSquare, bool onlyAttackingMoves) const;
    std::unique_ptr<Piece> clone() const;
    
    PieceInfo const& getPieceInfo() const;

    virtual ~Piece() = default;
};


#endif /* Piece_h */
