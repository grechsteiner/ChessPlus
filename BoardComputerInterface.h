// BoardComputerInterface.h

#ifndef BoardComputerInterface_h
#define BoardComputerInterface_h

#include <vector>

#include "FullMove.h"
#include "Constants.h"
#include "Piece.h"

class Context;


class BoardComputerInterface {

private:
    virtual std::vector<FullMove> getLegalMovesImpl(Color color) const = 0; 
    virtual std::vector<FullMove> getCapturingMovesImpl(Color color) const = 0;
    virtual std::vector<FullMove> getCheckApplyingMovesImpl(Color color) const = 0;
    virtual std::vector<FullMove> getCaptureAvoidingMovesImpl(Color color) const = 0;

    virtual Color getColorOneImpl() const = 0;
    virtual Color getColorTwoImpl() const = 0;
    virtual Color oppositeColorImpl(Color color) const = 0;

    virtual void makeMoveImpl(FullMove const &move) = 0;                    
    virtual bool undoMoveImpl() = 0;   

    virtual Piece const& getPieceAtImpl(int row, int col) const = 0;
    virtual bool isInStaleMateImpl(Color color) const = 0;
    virtual int getAlphaBetaBoardScoreImpl(Color color) const = 0;

    virtual Context& getContextImpl() = 0;

public:
    std::vector<FullMove> getLegalMoves(Color color) const; 
    std::vector<FullMove> getCapturingMoves(Color color) const;
    std::vector<FullMove> getCheckApplyingMoves(Color color) const;
    std::vector<FullMove> getCaptureAvoidingMoves(Color color) const;

    Color getColorOne() const;
    Color getColorTwo() const;
    Color oppositeColor(Color color) const;

    void makeMove(FullMove const &move);                    
    bool undoMove();   

    Piece const& getPieceAt(int row, int col) const;
    bool isInStaleMate(Color color) const;
    int getAlphaBetaBoardScore(Color color) const;

    Context& getContext() { return getContextImpl(); }

};


#endif /* BoardComputerInterface_h */
