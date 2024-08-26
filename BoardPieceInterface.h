// BoardPieceInterface.h

#ifndef BoardPieceInterface_h
#define BoardPieceInterface_h

#include <memory>

#include "Piece.h"
#include "Constants.h"
#include "CompletedMove.h"


class BoardPieceInterface {

private:
    virtual const std::unique_ptr<Piece>& getPieceAtImplementation(int row, int col) const = 0;
    virtual bool isEmptySquareOnBoardImplementation(int row, int col) const = 0;
    virtual bool isOpposingColorOnBoardImplementation(int row, int col, Color color) const = 0;
    virtual bool isEmptySquareOrOpposingColorOnBoardImplementation(int row, int col, Color color) const = 0;
    virtual bool isSquareCheckAttackedImplementation(int attackedRow, int attackedCol, Color color) const = 0;

    virtual bool lastMoveImplementation() const = 0;
    virtual const CompletedMove& getLastMoveImplementation() const = 0;

    virtual int getNumRowsImplementation() const = 0;
    virtual int getNumColsImplementation() const = 0;

public:
    const std::unique_ptr<Piece>& getPieceAt(int row, int col) const;
    bool isEmptySquareOnBoard(int row, int col) const;
    bool isOpposingColorOnBoard(int row, int col, Color color) const;
    bool isEmptySquareOrOpposingColorOnBoard(int row, int col, Color color) const;
    bool isSquareCheckAttacked(int attackedRow, int attackedCol, Color color) const;

    bool lastMove() const;
    const CompletedMove& getLastMove() const;

    int getNumRows() const;
    int getNumCols() const;

    virtual ~BoardPieceInterface() = default;
};


#endif /* BoardPieceInterface */
