// ChessBoard.h

#ifndef ChessBoard_h
#define ChessBoard_h

#include <vector>

#include "FullMove.h"
#include "Constants.h"
#include "Piece.h"

class Context;


class ChessBoard {

private:
    virtual std::vector<BoardMove> getLegalMovesImpl(Color color) const = 0; 
    virtual std::vector<BoardMove> getCapturingMovesImpl(Color color) const = 0;
    virtual std::vector<BoardMove> getCheckApplyingMovesImpl(Color color) const = 0;
    virtual std::vector<BoardMove> getCaptureAvoidingMovesImpl(Color color) const = 0;

    virtual Color getColorOneImpl() const = 0;
    virtual Color getColorTwoImpl() const = 0;
    virtual Color oppositeColorImpl(Color color) const = 0;

    virtual void makeMoveImpl(BoardMove const &move) = 0;                    
    virtual bool undoMoveImpl() = 0;   

    virtual Piece const& getPieceAtImpl(int row, int col) const = 0;
    virtual bool isInStaleMateImpl(Color color) const = 0;
    virtual int getAlphaBetaBoardScoreImpl(Color color) const = 0;

    virtual Context& getContextImpl() = 0;

public:
    std::vector<BoardMove> getLegalMoves(Color color) const; 
    std::vector<BoardMove> getCapturingMoves(Color color) const;
    std::vector<BoardMove> getCheckApplyingMoves(Color color) const;
    std::vector<BoardMove> getCaptureAvoidingMoves(Color color) const;

    Color getColorOne() const;
    Color getColorTwo() const;
    Color oppositeColor(Color color) const;

    void makeMove(BoardMove const &move);                    
    bool undoMove();   

    Piece const& getPieceAt(int row, int col) const;
    bool isInStaleMate(Color color) const;
    int getAlphaBetaBoardScore(Color color) const;

    Context& getContext() { return getContextImpl(); }

};


#endif /* ChessBoard_h */
