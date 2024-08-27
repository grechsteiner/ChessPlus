// BoardMoveInterface.h

#ifndef BoardMoveInterface_h
#define BoardMoveInterface_h

#include "Constants.h"
#include "FullMove.h"
#include "Piece.h"


class BoardMoveInterface {

private:
    virtual Piece const& getPieceAtImpl(int row, int col) const = 0;
    virtual void setPositionImpl(int row, int col, Color pieceColor, PieceType pieceType, PieceDirection pieceDirection, bool hasMoved, int pieceScore = -1) = 0;
    virtual void swapPositionsImpl(int rowOne, int colOne, int rowTwo, int colTwo) = 0;
    virtual void setHasMovedImpl(int row, int col, bool hasMoved) = 0;

public:
    Piece const& getPieceAt(int row, int col) const;
    void setPosition(int row, int col, Color pieceColor, PieceType pieceType, PieceDirection pieceDirection, bool hasMoved, int pieceScore = -1);
    void swapPositions(int rowOne, int colOne, int rowTwo, int colTwo);
    void setHasMoved(int row, int col, bool hasMoved);

};


#endif /* BoardMoveInterface_h */
