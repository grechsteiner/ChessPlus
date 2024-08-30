// ChessBoard.h

#ifndef ChessBoard_h
#define ChessBoard_h

#include <vector>

#include "Constants.h"

class UserMove;
class BoardMove;
class UserSquare;
class BoardSquare;
struct PieceInfo;


class ChessBoard {

private:
    virtual PieceInfo getPieceInfoAtImpl(BoardSquare const &boardSquare) const = 0;
    virtual std::vector<BoardSquare> allBoardSquaresImpl() const = 0;

    virtual bool isEmptySquareOnBoardImpl(BoardSquare const &boardSquare) const = 0;
    virtual bool isOpposingColorOnBoardImpl(BoardSquare const &boardSquare, Color color) const = 0;
    virtual bool isEmptySquareOrOpposingColorOnBoardImpl(BoardSquare const &boardSquare, Color color) const = 0;
    virtual bool isSquareAttackedImpl(BoardSquare const &boardSquare, Color color) const = 0;
    
    virtual bool isSquareOnBoardImpl(BoardSquare const &boardSquare) const = 0;
    virtual bool isSquareOnBoardImpl(UserSquare const &userSquare) const = 0;
    virtual void setPositionImpl(UserSquare const &userSquare, Color pieceColor, PieceType pieceType, PieceDirection pieceDirection, bool hasMoved, int pieceScore = -1) = 0;
    virtual void setPositionImpl(BoardSquare const &boardSquare, Color pieceColor, PieceType pieceType, PieceDirection pieceDirection, bool hasMoved, int pieceScore = -1) = 0;
    virtual bool clearPositionImpl(UserSquare const &userSquare) = 0;
    virtual bool clearPositionImpl(BoardSquare const &boardSquare) = 0;
    virtual void clearBoardImpl() = 0;
    virtual void swapPositionsImpl(BoardSquare const &boardSquareOne, BoardSquare const &boardSquareTwo) = 0;
    virtual void setHasMovedImpl(BoardSquare const &boardSquare, bool hasMoved) = 0;
    virtual bool setBoardSizeImpl(int newNumRows, int newNumCols) = 0;
    virtual void applyStandardSetupImpl() = 0;

    virtual std::vector<BoardMove> getLegalMovesImpl(Color color) const = 0; 
    virtual std::vector<BoardMove> getCapturingMovesImpl(Color color) const = 0;
    virtual std::vector<BoardMove> getCheckApplyingMovesImpl(Color color) const = 0;
    virtual std::vector<BoardMove> getCaptureAvoidingMovesImpl(Color color) const = 0;

    virtual Color getColorOneImpl() const = 0;
    virtual Color getColorTwoImpl() const = 0;
    virtual Color oppositeColorImpl(Color color) const = 0;

    virtual std::unique_ptr<BoardMove> generateBoardMoveImpl(UserMove const &userMove) const = 0;
    virtual BoardMove const& getLastMadeMoveImpl() const = 0;
    virtual std::vector<BoardMove> const& getAllMadeMovesImpl() const = 0;
    virtual bool hasMoveBeenMadeImpl() const = 0;
    virtual void makeMoveImpl(BoardMove const &move) = 0;                    
    virtual bool undoMoveImpl() = 0;  
    virtual bool redoMoveImpl() = 0; 

    virtual int getNumRowsImpl() const = 0;
    virtual int getNumColsImpl() const = 0;

    virtual bool isInCheckImpl(Color color) const = 0;
    virtual bool isInCheckMateImpl(Color color) const = 0;
    virtual bool isInStaleMateImpl(Color color) const = 0;
    virtual bool isInStaleMateImpl() const = 0;
    virtual bool hasGameFinishedImpl() const = 0;
    virtual bool isBoardInValidStateImpl() const = 0;

public:
    PieceInfo getPieceInfoAt(BoardSquare const &boardSquare) const;
    std::vector<BoardSquare> allBoardSquares() const;

    bool isEmptySquareOnBoard(BoardSquare const &boardSquare) const;
    bool isOpposingColorOnBoard(BoardSquare const &boardSquare, Color color) const;
    bool isEmptySquareOrOpposingColorOnBoard(BoardSquare const &boardSquare, Color color) const;
    bool isSquareAttacked(BoardSquare const &boardSquare, Color color) const;
    
    bool isSquareOnBoard(BoardSquare const &boardSquare) const;
    bool isSquareOnBoard(UserSquare const &userSquare) const;
    void setPosition(UserSquare const &userSquare, Color pieceColor, PieceType pieceType, PieceDirection pieceDirection, bool hasMoved, int pieceScore = -1);
    void setPosition(BoardSquare const &boardSquare, Color pieceColor, PieceType pieceType, PieceDirection pieceDirection, bool hasMoved, int pieceScore = -1);
    bool clearPosition(UserSquare const &userSquare);
    bool clearPosition(BoardSquare const &boardSquare);
    void clearBoard();
    void swapPositions(BoardSquare const &boardSquareOne, BoardSquare const &boardSquareTwo);
    void setHasMoved(BoardSquare const &boardSquareTwo, bool hasMoved);
    bool setBoardSize(int newNumRows, int newNumCols);
    void applyStandardSetup();

    std::vector<BoardMove> getLegalMoves(Color color) const; 
    std::vector<BoardMove> getCapturingMoves(Color color) const;
    std::vector<BoardMove> getCheckApplyingMoves(Color color) const;
    std::vector<BoardMove> getCaptureAvoidingMoves(Color color) const;

    Color getColorOne() const;
    Color getColorTwo() const;
    Color oppositeColor(Color color) const;

    std::unique_ptr<BoardMove> generateBoardMove(UserMove const &userMove) const;
    BoardMove const& getLastMadeMove() const;
    std::vector<BoardMove> const& getAllMadeMoves() const;
    bool hasMoveBeenMade() const;
    void makeMove(BoardMove const &move);                    
    bool undoMove();  
    bool redoMove(); 

    int getNumRows() const;
    int getNumCols() const;

    bool isInCheck(Color color) const;
    bool isInCheckMate(Color color) const;
    bool isInStaleMate(Color color) const;
    bool isInStaleMate() const;
    bool hasGameFinished() const;
    bool isBoardInValidState() const;

};


#endif /* ChessBoard_h */
