// Piece.h

#ifndef Piece_h
#define Piece_h

#include <vector>

#include "Constants.h"
#include "BoardMove.h"
#include "PieceInfo.h"

class ChessBoard;

class Piece {

private:
    virtual std::vector<BoardMove> getMovesImplementation(ChessBoard const &board, BoardSquare const &boardSquare, bool onlyAttackingMoves) const = 0;
    
protected:
    Piece(Color pieceColor, PieceType pieceType, PieceDirection pieceDirection, bool hasMoved, std::string const &image, std::string const &display, int pieceScore);

    PieceInfo pieceInfo;

    // TODO:
    // Factory up for different move types
    // Maybe alter isAttackingMove
    BoardMove createBoardMove(ChessBoard const &board, BoardSquare const &fromSquare, BoardSquare const &toSquare, BoardSquare const &captureSquare, MoveType moveType, bool isAttackingMove, PieceType promotionPieceType = PieceType::EMPTY) const;

public:
    virtual ~Piece() = default;
    
    std::vector<BoardMove> getMoves(ChessBoard const &board, BoardSquare const &boardSquare, bool onlyAttackingMoves) const;
    
    // Getters
    PieceInfo getPieceInfo() const;
    void setHasMoved(bool newHasMoved);
};


#endif /* Piece_h */
