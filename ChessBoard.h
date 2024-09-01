// ChessBoard.h

#ifndef ChessBoard_h
#define ChessBoard_h

#include <vector>
#include <optional>

#include "Constants.h"

class UserMove;
class BoardMove;
class UserSquare;
class BoardSquare;
struct PieceInfo;


class ChessBoard {

private:
    virtual std::optional<PieceInfo> getPieceInfoAtImpl(BoardSquare const &boardSquare) const = 0;
    virtual std::vector<BoardSquare> allBoardSquaresImpl() const = 0;

    virtual bool isSquareOnBoardImpl(BoardSquare const &boardSquare) const = 0;
    virtual bool isSquareEmptyImpl(BoardSquare const &boardSquare) const = 0;
    virtual bool isSquareOwnTeamImpl(BoardSquare const &boardSquare, Team team) const = 0;
    virtual bool isSquareOtherTeamImpl(BoardSquare const &boardSquare, Team team) const = 0;
    virtual bool isSquareAttackedImpl(BoardSquare const &boardSquare, Team team) const = 0;
    
    virtual bool setPositionImpl(BoardSquare const &boardSquare, Team team, PieceType pieceType, PieceDirection pieceDirection, bool hasMoved, std::optional<int> pieceScore = std::nullopt) = 0;
    virtual bool clearPositionImpl(BoardSquare const &boardSquare) = 0;
    virtual void clearBoardImpl() = 0;
    virtual bool setBoardSizeImpl(int newNumRows, int newNumCols) = 0;

    virtual std::vector<BoardMove> getLegalMovesAtSquareImpl(BoardSquare const &boardSquare) const = 0;
    virtual std::vector<BoardMove> getLegalMovesImpl(Team team) const = 0; 
    virtual std::vector<BoardMove> getCapturingMovesImpl(Team team) const = 0;
    virtual std::vector<BoardMove> getCheckApplyingMovesImpl(Team team) const = 0;
    virtual std::vector<BoardMove> getCaptureAvoidingMovesImpl(Team team) const = 0;

    virtual Team getTeamOneImpl() const = 0;
    virtual Team getTeamTwoImpl() const = 0;
    virtual Team getOtherTeamImpl(Team team) const = 0;

    virtual std::optional<BoardMove> createBoardMoveImpl(BoardSquare const &fromSquare, BoardSquare const &toSquare, std::optional<PieceType> promotionPieceType = std::nullopt) const = 0;
    virtual std::optional<BoardMove> getLastCompletedMoveImpl() const = 0;
    virtual std::vector<BoardMove> const& getAllCompletedMovesImpl() const = 0;

    virtual bool makeMoveImpl(BoardMove const &move) = 0;                    
    virtual bool undoMoveImpl() = 0;  
    virtual bool redoMoveImpl() = 0; 

    virtual int getNumRowsImpl() const = 0;
    virtual int getNumColsImpl() const = 0;

    virtual bool isInCheckImpl(Team team) const = 0;
    virtual bool isInCheckMateImpl(Team team) const = 0;
    virtual bool isInStaleMateImpl(Team team) const = 0;

public:
    std::optional<PieceInfo> getPieceInfoAt(BoardSquare const &boardSquare) const;
    std::vector<BoardSquare> allBoardSquares() const;

    bool isSquareOnBoard(BoardSquare const &boardSquare) const;
    bool isSquareEmpty(BoardSquare const &boardSquare) const;
    bool isSquareOwnTeam(BoardSquare const &boardSquare, Team team) const;
    bool isSquareOtherTeam(BoardSquare const &boardSquare, Team team) const;
    bool isSquareAttacked(BoardSquare const &boardSquare, Team team) const;
    
    bool setPosition(BoardSquare const &boardSquare, Team team, PieceType pieceType, PieceDirection pieceDirection, bool hasMoved, std::optional<int> pieceScore = std::nullopt);    
    bool clearPosition(BoardSquare const &boardSquare);
    void clearBoard();
    bool setBoardSize(int newNumRows, int newNumCols);

    std::vector<BoardMove> getLegalMovesAtSquare(BoardSquare const &boardSquare) const;
    std::vector<BoardMove> getLegalMoves(Team team) const; 
    std::vector<BoardMove> getCapturingMoves(Team team) const;
    std::vector<BoardMove> getCheckApplyingMoves(Team team) const;
    std::vector<BoardMove> getCaptureAvoidingMoves(Team team) const;

    // Review below
    Team getTeamOne() const;
    Team getTeamTwo() const;
    Team getOtherTeam(Team team) const;

    std::optional<BoardMove> createBoardMove(BoardSquare const &fromSquare, BoardSquare const &toSquare, std::optional<PieceType> promotionPieceType = std::nullopt) const;
    std::optional<BoardMove> getLastCompletedMove() const;
    std::vector<BoardMove> const& getAllCompletedMoves() const;

    bool makeMove(BoardMove const &move);
    bool undoMove();  
    bool redoMove(); 

    int getNumRows() const;
    int getNumCols() const;

    bool isInCheck(Team team) const;
    bool isInCheckMate(Team team) const;
    bool isInStaleMate(Team team) const;

};


#endif /* ChessBoard_h */
