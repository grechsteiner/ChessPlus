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
    virtual bool isOpposingTeamOnBoardImpl(BoardSquare const &boardSquare, Team team) const = 0;
    virtual bool isEmptySquareOrOpposingTeamOnBoardImpl(BoardSquare const &boardSquare, Team team) const = 0;
    virtual bool isSquareAttackedImpl(BoardSquare const &boardSquare, Team team) const = 0;
    
    virtual bool isSquareOnBoardImpl(BoardSquare const &boardSquare) const = 0;
    virtual void setPositionImpl(BoardSquare const &boardSquare, Team team, PieceType pieceType, PieceDirection pieceDirection, bool hasMoved, int pieceScore = -1) = 0;
    virtual bool clearPositionImpl(BoardSquare const &boardSquare) = 0;
    virtual void clearBoardImpl() = 0;
    virtual void swapPositionsImpl(BoardSquare const &boardSquareOne, BoardSquare const &boardSquareTwo) = 0;
    virtual void setHasMovedImpl(BoardSquare const &boardSquare, bool hasMoved) = 0;
    virtual bool setBoardSizeImpl(int newNumRows, int newNumCols) = 0;
    virtual void applyStandardSetupImpl() = 0;

    virtual std::vector<BoardMove> getLegalMovesImpl(Team team) const = 0; 
    virtual std::vector<BoardMove> getCapturingMovesImpl(Team team) const = 0;
    virtual std::vector<BoardMove> getCheckApplyingMovesImpl(Team team) const = 0;
    virtual std::vector<BoardMove> getCaptureAvoidingMovesImpl(Team team) const = 0;

    virtual Team getTeamOneImpl() const = 0;
    virtual Team getTeamTwoImpl() const = 0;
    virtual Team getOtherTeamImpl(Team team) const = 0;

    virtual std::unique_ptr<BoardMove> generateBoardMoveImpl(BoardSquare const &fromSquare, BoardSquare const &toSquare, PieceType promotionPieceType) const = 0;
    virtual BoardMove const& getLastMadeMoveImpl() const = 0;
    virtual std::vector<BoardMove> const& getAllMadeMovesImpl() const = 0;
    virtual bool hasMoveBeenMadeImpl() const = 0;
    virtual void makeMoveImpl(BoardMove const &move) = 0;                    
    virtual bool undoMoveImpl() = 0;  
    virtual bool redoMoveImpl() = 0; 

    virtual int getNumRowsImpl() const = 0;
    virtual int getNumColsImpl() const = 0;

    virtual bool isInCheckImpl(Team team) const = 0;
    virtual bool isInCheckMateImpl(Team team) const = 0;
    virtual bool isInStaleMateImpl(Team team) const = 0;
    virtual bool isInStaleMateImpl() const = 0;
    virtual bool hasGameFinishedImpl() const = 0;
    virtual bool isBoardInValidStateImpl() const = 0;

public:
    PieceInfo getPieceInfoAt(BoardSquare const &boardSquare) const;
    std::vector<BoardSquare> allBoardSquares() const;

    bool isEmptySquareOnBoard(BoardSquare const &boardSquare) const;
    bool isOpposingTeamOnBoard(BoardSquare const &boardSquare, Team team) const;
    bool isEmptySquareOrOpposingTeamOnBoard(BoardSquare const &boardSquare, Team team) const;
    bool isSquareAttacked(BoardSquare const &boardSquare, Team team) const;
    
    bool isSquareOnBoard(BoardSquare const &boardSquare) const;
    void setPosition(BoardSquare const &boardSquare, Team team, PieceType pieceType, PieceDirection pieceDirection, bool hasMoved, int pieceScore = -1);
    bool clearPosition(BoardSquare const &boardSquare);
    void clearBoard();
    void swapPositions(BoardSquare const &boardSquareOne, BoardSquare const &boardSquareTwo);
    void setHasMoved(BoardSquare const &boardSquareTwo, bool hasMoved);
    bool setBoardSize(int newNumRows, int newNumCols);
    void applyStandardSetup();

    std::vector<BoardMove> getLegalMoves(Team team) const; 
    std::vector<BoardMove> getCapturingMoves(Team team) const;
    std::vector<BoardMove> getCheckApplyingMoves(Team team) const;
    std::vector<BoardMove> getCaptureAvoidingMoves(Team team) const;

    Team getTeamOne() const;
    Team getTeamTwo() const;
    Team getOtherTeam(Team team) const;

    std::unique_ptr<BoardMove> generateBoardMove(BoardSquare const &fromSquare, BoardSquare const &toSquare, PieceType promotionPieceType) const;
    BoardMove const& getLastMadeMove() const;
    std::vector<BoardMove> const& getAllMadeMoves() const;
    bool hasMoveBeenMade() const;
    void makeMove(BoardMove const &move);                    
    bool undoMove();  
    bool redoMove(); 

    int getNumRows() const;
    int getNumCols() const;

    bool isInCheck(Team team) const;
    bool isInCheckMate(Team team) const;
    bool isInStaleMate(Team team) const;
    bool isInStaleMate() const;
    bool hasGameFinished() const;
    bool isBoardInValidState() const;

};


#endif /* ChessBoard_h */
