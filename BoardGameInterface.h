// BoardGameInterface.h

#ifndef BoardGameInterface_h
#define BoardGameInterface_h

#include <memory>

#include "FullMove.h"
#include "UserEnteredMove.h"
#include "Constants.h"

class Context;

class BoardGameInterface {

private:
    virtual bool isInStaleMateImpl() const = 0;
    virtual bool hasGameFinishedImpl() const = 0;
    virtual bool isBoardInValidStateImpl() const = 0;

    virtual void setPositionImpl(int row, char col, Color pieceColor, PieceType pieceType, PieceDirection pieceDirection, bool hasMoved, int pieceScore = -1) = 0;
    virtual bool clearPositionImpl(int row, char col) = 0;
    virtual void clearBoardImpl() = 0;
    
    virtual bool isSquareOnBoardImpl(int row, char col) const = 0;
    virtual bool setBoardSizeImpl(int newNumRows, int newNumCols) = 0;
    virtual void applyStandardSetupImpl() = 0;

    virtual std::unique_ptr<FullMove> generateFullMoveImpl(UserEnteredMove const &userEnteredMove) const = 0;
    virtual void makeMoveImpl(FullMove const &move) = 0;                    
    virtual bool undoMoveImpl() = 0;            
    virtual bool redoMoveImpl() = 0;

    virtual Context& getContextImpl() = 0;

public:
    bool isInStaleMate() const;
    bool hasGameFinished() const;
    bool isBoardInValidState() const;

    void setPosition(int row, char col, Color pieceColor, PieceType pieceType, PieceDirection pieceDirection, bool hasMoved, int pieceScore = -1);
    bool clearPosition(int row, char col);
    void clearBoard();
    
    bool isSquareOnBoard(int row, char col) const;
    bool setBoardSize(int newNumRows, int newNumCols);
    void applyStandardSetup();

    std::unique_ptr<FullMove> generateFullMove(UserEnteredMove const &userEnteredMove) const;
    void makeMove(FullMove const &move);                    
    bool undoMove();            
    bool redoMove();  

    Context& getContext() { return getContextImpl(); }

};


#endif /* BoardGameInterface_h */
