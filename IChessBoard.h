// IChessBoard.h

#ifndef IChessBoard_h
#define IChessBoard_h

#include <vector>
#include <stack>
#include <optional>
#include <memory>

#include "Constants.h"

class BoardSquare;
class BoardMove;
class PieceData;


/**
 * ChessBoard Interface Class
 */
class IChessBoard {

private:
    virtual std::unique_ptr<IChessBoard> cloneImpl() const = 0;

    virtual std::optional<PieceData> getPieceDataAtImpl(BoardSquare const &boardSquare) const = 0;
    virtual std::vector<BoardSquare> getAllBoardSquaresImpl() const = 0;

    virtual bool isSquareOnBoardImpl(BoardSquare const &boardSquare) const = 0;
    virtual bool isSquareEmptyImpl(BoardSquare const &boardSquare) const = 0;
    virtual bool isSquareSameTeamImpl(BoardSquare const &boardSquare, Team ownTeam) const = 0;
    virtual bool isSquareOtherTeamImpl(BoardSquare const &boardSquare, Team ownTeam) const = 0;
    virtual bool isSquareAttackedImpl(BoardSquare const &boardSquare, Team ownTeam) const = 0;

    virtual bool isInCheckImpl(Team team) const = 0;
    virtual bool isInCheckMateImpl(Team team) const = 0;
    virtual bool isInStaleMateImpl(Team team) const = 0;

    virtual std::vector<BoardMove> generateAllLegalMovesAtSquareImpl(BoardSquare const &boardSquare) const = 0;
    virtual std::vector<BoardMove> generateAllLegalMovesImpl(Team team) const = 0; 
    virtual std::vector<BoardMove> generateCapturingMovesImpl(Team team) const = 0;
    virtual std::vector<BoardMove> generateCheckApplyingMovesImpl(Team team) const = 0;
    virtual std::vector<BoardMove> generateCaptureAvoidingMovesImpl(Team team) const = 0;

    virtual bool setPositionImpl(BoardSquare const &boardSquare, Team team, PieceType pieceType, PieceDirection pieceDirection, bool hasMoved, std::optional<int> pieceScore = std::nullopt) = 0;
    virtual bool clearPositionImpl(BoardSquare const &boardSquare) = 0;
    virtual void clearBoardImpl() = 0;

    virtual std::optional<BoardMove> createBoardMoveImpl(BoardSquare const &fromSquare, BoardSquare const &toSquare, std::optional<PieceType> promotionPieceType = std::nullopt) const = 0;
    virtual bool makeMoveImpl(BoardMove const &boardMove) = 0;                    
    virtual bool undoMoveImpl() = 0;  
    virtual bool redoMoveImpl() = 0; 

    virtual std::optional<BoardMove> getLastCompletedMoveImpl() const = 0;
    virtual std::stack<BoardMove> const& getAllCompletedMovesImpl() const = 0;

    virtual Team getTeamOneImpl() const = 0;
    virtual Team getTeamTwoImpl() const = 0;

    virtual int getNumRowsImpl() const = 0;
    virtual int getNumColsImpl() const = 0;

public:
    std::unique_ptr<IChessBoard> clone() const;
    virtual ~IChessBoard() = default;

    std::optional<PieceData> getPieceDataAt(BoardSquare const &boardSquare) const;
    std::vector<BoardSquare> getAllBoardSquares() const;

    bool isSquareOnBoard(BoardSquare const &boardSquare) const;
    bool isSquareEmpty(BoardSquare const &boardSquare) const;
    bool isSquareSameTeam(BoardSquare const &boardSquare, Team ownTeam) const;
    bool isSquareOtherTeam(BoardSquare const &boardSquare, Team ownTeam) const;
    bool isSquareAttacked(BoardSquare const &boardSquare, Team ownTeam) const;

    bool isInCheck(Team team) const;
    bool isInCheckMate(Team team) const;
    bool isInStaleMate(Team team) const;

    std::vector<BoardMove> generateAllLegalMovesAtSquare(BoardSquare const &boardSquare) const;
    std::vector<BoardMove> generateAllLegalMoves(Team team) const; 
    std::vector<BoardMove> generateCapturingMoves(Team team) const;
    std::vector<BoardMove> generateCheckApplyingMoves(Team team) const;
    std::vector<BoardMove> generateCaptureAvoidingMoves(Team team) const;

    bool setPosition(BoardSquare const &boardSquare, Team team, PieceType pieceType, PieceDirection pieceDirection, bool hasMoved, std::optional<int> pieceScore = std::nullopt);    
    bool clearPosition(BoardSquare const &boardSquare);
    void clearBoard();

    std::optional<BoardMove> createBoardMove(BoardSquare const &fromSquare, BoardSquare const &toSquare, std::optional<PieceType> promotionPieceType = std::nullopt) const;
    bool makeMove(BoardMove const &boardMove);
    bool undoMove();  
    bool redoMove(); 

    std::optional<BoardMove> getLastCompletedMove() const;
    std::stack<BoardMove> const& getAllCompletedMoves() const;

    Team getTeamOne() const;
    Team getTeamTwo() const;

    int getNumRows() const;
    int getNumCols() const;
};


#endif /* IChessBoard_h */
