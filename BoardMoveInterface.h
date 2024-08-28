// BoardMoveInterface.h

#ifndef BoardMoveInterface_h
#define BoardMoveInterface_h

#include "Constants.h"
#include "FullMove.h"
#include "Piece.h"

class Context;

class BoardMoveInterface {

private:
    virtual Piece const& getPieceAtImpl(int row, int col) const = 0;
    virtual void setPositionImpl(int row, int col, Color pieceColor, PieceType pieceType, PieceDirection pieceDirection, bool hasMoved, int pieceScore = -1) = 0;
    virtual void clearPositionImpl(int row, int col) = 0;
    virtual void swapPositionsImpl(int rowOne, int colOne, int rowTwo, int colTwo) = 0;
    virtual void setHasMovedImpl(int row, int col, bool hasMoved) = 0;

    virtual Context& getContextImpl() = 0;

public:
    Piece const& getPieceAt(int row, int col) const;
    void setPosition(int row, int col, Color pieceColor, PieceType pieceType, PieceDirection pieceDirection, bool hasMoved, int pieceScore = -1);
    void clearPosition(int row, int col);
    void swapPositions(int rowOne, int colOne, int rowTwo, int colTwo);
    void setHasMoved(int row, int col, bool hasMoved);

    Context& getContext() { return getContextImpl(); }

};


#endif /* BoardMoveInterface_h */
