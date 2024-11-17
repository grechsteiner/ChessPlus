// Piece.h

#ifndef Piece_h
#define Piece_h

#include <memory>
#include <vector>

#include "PieceData.h"
#include "PieceInfo.h"
#include "ChessBoard.h"
#include "BoardSquare.h"
#include "BoardMove.h"


/**
 * Abstract Piece Class
 * Represents a Piece on a ChessBoard
 */
class Piece {
private:
    virtual std::vector<std::unique_ptr<BoardMove>> getStandardMoves(std::unique_ptr<ChessBoard> const &chessBoard, BoardSquare const &fromSquare, bool onlyAttackingMoves) const = 0;

    virtual std::vector<std::unique_ptr<BoardMove>> getMovesImpl(std::unique_ptr<ChessBoard> const &chessBoard, BoardSquare const &fromSquare, bool onlyAttackingMoves) const = 0;
    virtual std::unique_ptr<Piece> cloneImpl() const = 0;
    
protected:
    PieceData pieceData;
    PieceInfo pieceInfo;

    explicit Piece(PieceData const &pieceData, PieceInfo const &pieceInfo);
    Piece(Piece const &other);
    Piece(Piece &&other) noexcept;
    Piece& operator=(Piece const &other);
    Piece& operator=(Piece &&other) noexcept;

public:
    virtual ~Piece() = default;

    bool operator==(Piece const &other) const;
    bool operator!=(Piece const &other) const;

    std::vector<std::unique_ptr<BoardMove>> getMoves(std::unique_ptr<ChessBoard> const &chessBoard, BoardSquare const &fromSquare, bool onlyAttackingMoves) const;
    std::unique_ptr<Piece> clone() const;
    
    PieceData const& getPieceData() const;
    PieceInfo const& getPieceInfo() const;
};


#endif /* Piece_h */
