// Piece.h

#ifndef Piece_h
#define Piece_h

#include <vector>
#include <memory>

#include "PieceData.h"
#include "PieceInfo.h"

#include "ChessBoard.h"
struct BoardSquare;
class BoardMove;


/**
 * Abstract Piece Class
 * Represents a piece on a chessboard
 */
class Piece {

private:
    virtual std::vector<std::unique_ptr<BoardMove>> getMovesImpl(std::unique_ptr<ChessBoard> const &chessBoard, BoardSquare const &fromSquare, bool onlyAttackingMoves) const = 0;
    virtual std::unique_ptr<Piece> cloneImpl() const = 0;
    
protected:
    explicit Piece(PieceData const &pieceData, PieceInfo const &pieceInfo);
    Piece(Piece const &other) = default;
    Piece(Piece &&other) noexcept;
    Piece& operator=(Piece const &other) = default;
    Piece& operator=(Piece &&other) noexcept;

    PieceData pieceData;
    PieceInfo pieceInfo;

    virtual std::vector<std::unique_ptr<BoardMove>> getStandardMoves(std::unique_ptr<ChessBoard> const &chessBoard, BoardSquare const &fromSquare, bool onlyAttackingMoves) const = 0;

public:
    std::vector<std::unique_ptr<BoardMove>> getMoves(std::unique_ptr<ChessBoard> const &chessBoard, BoardSquare const &fromSquare, bool onlyAttackingMoves) const;
    std::unique_ptr<Piece> clone() const;
    
    PieceData const& getPieceData() const;
    PieceInfo const& getPieceInfo() const;

    virtual ~Piece() = default;
};


#endif /* Piece_h */
