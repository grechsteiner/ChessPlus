// Piece.h

#ifndef Piece_h
#define Piece_h

#include <vector>

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
    
protected:
    explicit Piece(PieceType pieceType, Team team, PieceDirection pieceDirection, bool hasMoved, int pieceScore, std::string const &image, std::string const &display);
    PieceInfo pieceInfo;

public:
    std::vector<BoardMove> getMoves(ChessBoard const &chessBoard, BoardSquare const &fromSquare, bool onlyAttackingMoves) const;
    virtual ~Piece() = default;
    PieceInfo const& getPieceInfo() const;
};


#endif /* Piece_h */
