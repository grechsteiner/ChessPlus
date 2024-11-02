// ChessBoard.h

#ifndef ChessBoard_h
#define ChessBoard_h

#include <vector>
#include <stack>
#include <optional>
#include <memory>

#include "Constants.h"

class BoardSquare;
class OldBoardMove;
struct PieceInfo;
struct PieceData;


/**
 * ChessBoard Interface Class
 */
class ChessBoard {

private:
    virtual std::unique_ptr<ChessBoard> cloneImpl() const = 0;

    virtual std::optional<PieceData> getPieceDataAtImpl(BoardSquare const &boardSquare) const = 0;
    virtual std::optional<PieceInfo> getPieceInfoAtImpl(BoardSquare const &boardSquare) const = 0;
    virtual std::vector<BoardSquare> getAllBoardSquaresImpl() const = 0;

    virtual bool isSquareOnBoardImpl(BoardSquare const &boardSquare) const = 0;
    virtual bool isSquareEmptyImpl(BoardSquare const &boardSquare) const = 0;
    virtual bool isSquareSameTeamImpl(BoardSquare const &boardSquare, Team ownTeam) const = 0;
    virtual bool isSquareOtherTeamImpl(BoardSquare const &boardSquare, Team ownTeam) const = 0;
    virtual bool isSquareAttackedImpl(BoardSquare const &boardSquare, Team ownTeam) const = 0;

    virtual bool isInCheckImpl(Team team) const = 0;
    virtual bool isInCheckMateImpl(Team team) const = 0;
    virtual bool isInStaleMateImpl(Team team) const = 0;

    virtual std::vector<OldBoardMove> generateAllLegalMovesAtSquareImpl(BoardSquare const &boardSquare) const = 0;
    virtual std::vector<OldBoardMove> generateAllLegalMovesImpl(Team team) const = 0; 
    virtual std::vector<OldBoardMove> generateCapturingMovesImpl(Team team) const = 0;
    virtual std::vector<OldBoardMove> generateCheckApplyingMovesImpl(Team team) const = 0;
    virtual std::vector<OldBoardMove> generateCaptureAvoidingMovesImpl(Team team) const = 0;

    virtual bool setPositionImpl(BoardSquare const &boardSquare, PieceData const &pieceData) = 0;
    virtual bool clearPositionImpl(BoardSquare const &boardSquare) = 0;
    virtual void clearBoardImpl() = 0;

    virtual std::optional<OldBoardMove> createBoardMoveImpl(BoardSquare const &fromSquare, BoardSquare const &toSquare, std::optional<PieceType> promotionPieceType = std::nullopt) const = 0;
    virtual bool makeMoveImpl(OldBoardMove const &boardMove) = 0;                    
    virtual bool undoMoveImpl() = 0;  
    virtual bool redoMoveImpl() = 0; 

    virtual std::optional<OldBoardMove> getLastCompletedMoveImpl() const = 0;
    virtual std::stack<OldBoardMove> const& getAllCompletedMovesImpl() const = 0;

    virtual Team getTeamOneImpl() const = 0;
    virtual Team getTeamTwoImpl() const = 0;

    virtual int getNumRowsImpl() const = 0;
    virtual int getNumColsImpl() const = 0;

public:
    std::unique_ptr<ChessBoard> clone() const;
    virtual ~ChessBoard() = default;

    std::optional<PieceData> getPieceDataAt(BoardSquare const &boardSquare) const;
    std::optional<PieceInfo> getPieceInfoAt(BoardSquare const &boardSquare) const;
    std::vector<BoardSquare> getAllBoardSquares() const;

    bool isSquareOnBoard(BoardSquare const &boardSquare) const;
    bool isSquareEmpty(BoardSquare const &boardSquare) const;
    bool isSquareSameTeam(BoardSquare const &boardSquare, Team ownTeam) const;
    bool isSquareOtherTeam(BoardSquare const &boardSquare, Team ownTeam) const;
    bool isSquareAttacked(BoardSquare const &boardSquare, Team ownTeam) const;

    bool isInCheck(Team team) const;
    bool isInCheckMate(Team team) const;
    bool isInStaleMate(Team team) const;

    std::vector<OldBoardMove> generateAllLegalMovesAtSquare(BoardSquare const &boardSquare) const;
    std::vector<OldBoardMove> generateAllLegalMoves(Team team) const; 
    std::vector<OldBoardMove> generateCapturingMoves(Team team) const;
    std::vector<OldBoardMove> generateCheckApplyingMoves(Team team) const;
    std::vector<OldBoardMove> generateCaptureAvoidingMoves(Team team) const;

    bool setPosition(BoardSquare const &boardSquare, PieceData const &pieceData);    
    bool clearPosition(BoardSquare const &boardSquare);
    void clearBoard();

    std::optional<OldBoardMove> createBoardMove(BoardSquare const &fromSquare, BoardSquare const &toSquare, std::optional<PieceType> promotionPieceType = std::nullopt) const;
    bool makeMove(OldBoardMove const &boardMove);
    bool undoMove();  
    bool redoMove(); 

    std::optional<OldBoardMove> getLastCompletedMove() const;
    std::stack<OldBoardMove> const& getAllCompletedMoves() const;

    Team getTeamOne() const;
    Team getTeamTwo() const;

    int getNumRows() const;
    int getNumCols() const;
};


#endif /* ChessBoard_h */
