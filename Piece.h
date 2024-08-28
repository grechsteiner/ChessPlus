// Piece.h

#ifndef Piece_h
#define Piece_h

#include <vector>

#include "Constants.h"
#include "FullMove.h"

class BoardPieceInterface;

class Piece {

private:
    virtual std::vector<FullMove> getMovesImplementation(BoardPieceInterface const &board, int pieceRow, int pieceCol, bool attackingMoves) const = 0;
    
protected:
    Piece(Color pieceColor, PieceType pieceType, PieceDirection pieceDirection, bool hasMoved, std::string const &image, std::string const &display, int pieceScore);

    Color pieceColor;
    PieceType pieceType;
    PieceDirection pieceDirection;
    bool hasMoved;
    int pieceScore;
    std::string image;
    std::string display;

    // TODO:
    // Factory up for different move types
    // Maybe alter isAttackingMove
    FullMove createFullMove(BoardPieceInterface const &board, int fromRow, int fromCol, int toRow, int toCol, int captureRow, int captureCol, MoveType moveType, bool isAttackingMove, PieceType promotionPieceType = PieceType::EMPTY) const;

public:
    virtual ~Piece() = default;
    
    std::vector<FullMove> getMoves(BoardPieceInterface const &board, int pieceRow, int pieceCol, bool attackingMoves) const;
    
    // Getters
    Color getPieceColor() const;
    PieceType getPieceType() const;
    PieceDirection getPieceDirection() const;
    bool getHasMoved() const;
    void setHasMoved(bool newHasMoved);
    int getPieceScore() const;
    const std::string& getImage() const;
    const std::string& getDisplay() const;
};


#endif /* Piece_h */
