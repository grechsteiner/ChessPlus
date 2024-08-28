// BoardPieceInterface.h

#ifndef BoardPieceInterface_h
#define BoardPieceInterface_h

#include <memory>

#include "Piece.h"
#include "Constants.h"
#include "FullMove.h"


class BoardPieceInterface {

private:
    virtual Piece const& getPieceAtImpl(int row, int col) const = 0;
    virtual bool isEmptySquareOnBoardImplementation(int row, int col) const = 0;
    virtual bool isOpposingColorOnBoardImplementation(int row, int col, Color color) const = 0;
    virtual bool isEmptySquareOrOpposingColorOnBoardImplementation(int row, int col, Color color) const = 0;
    virtual bool isSquareCheckAttackedImplementation(int attackedRow, int attackedCol, Color color) const = 0;

    virtual bool hasMoveBeenMadeImplementation() const = 0;
    virtual FullMove const& getLastMoveImplementation() const = 0;

    virtual int getNumRowsImplementation() const = 0;
    virtual int getNumColsImplementation() const = 0;

public:
    Piece const& getPieceAt(int row, int col) const;
    bool isEmptySquareOnBoard(int row, int col) const;
    bool isOpposingColorOnBoard(int row, int col, Color color) const;
    bool isEmptySquareOrOpposingColorOnBoard(int row, int col, Color color) const;
    bool isSquareCheckAttacked(int attackedRow, int attackedCol, Color color) const;

    bool hasMoveBeenMade() const;
    FullMove const& getLastMove() const;

    int getNumRows() const;
    int getNumCols() const;

    virtual ~BoardPieceInterface() = default;
};


#endif /* BoardPieceInterface */
