// Piece.h

#ifndef Piece_h
#define Piece_h

#include <vector>
#include <memory>

#include "Constants.h"
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
    explicit Piece(PieceType pieceType, Team team, PieceDirection pieceDirection, bool hasMoved, int pieceScore, std::string const &image, std::string const &display);
    Piece(Piece const &other) = default;
    Piece(Piece &&other) noexcept;
    Piece& operator=(Piece const &other) = default;
    Piece& operator=(Piece &&other) noexcept;

    PieceInfo pieceInfo;

public:
    std::vector<BoardMove> getMoves(ChessBoard const &chessBoard, BoardSquare const &fromSquare, bool onlyAttackingMoves) const;
    std::unique_ptr<Piece> clone() const;
    
    PieceInfo const& getPieceInfo() const;

    virtual ~Piece() = default;
};


#endif /* Piece_h */
