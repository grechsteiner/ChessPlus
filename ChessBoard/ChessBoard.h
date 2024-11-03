// ChessBoard.h

#ifndef ChessBoard_h
#define ChessBoard_h

#include <vector>
#include <optional>
#include <memory>

#include "Constants.h"

struct BoardSquare;
class BoardMove;
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

    virtual std::vector<std::unique_ptr<BoardMove>> generateAllLegalMovesAtSquareImpl(BoardSquare const &boardSquare) const = 0;
    virtual std::vector<std::unique_ptr<BoardMove>> generateAllLegalMovesImpl(Team team) const = 0; 
    virtual std::vector<std::unique_ptr<BoardMove>> generateCapturingMovesImpl(Team team) const = 0;
    virtual std::vector<std::unique_ptr<BoardMove>> generateCheckApplyingMovesImpl(Team team) const = 0;
    virtual std::vector<std::unique_ptr<BoardMove>> generateCaptureAvoidingMovesImpl(Team team) const = 0;

    virtual bool setPositionImpl(BoardSquare const &boardSquare, PieceData const &pieceData) = 0;
    virtual bool clearPositionImpl(BoardSquare const &boardSquare) = 0;
    virtual void clearBoardImpl() = 0;

    virtual std::optional<std::unique_ptr<BoardMove>> createBoardMoveImpl(BoardSquare const &fromSquare, BoardSquare const &toSquare, std::optional<PieceType> promotionPieceType = std::nullopt) const = 0;
    virtual bool makeMoveImpl(std::unique_ptr<BoardMove> const &boardMove) = 0;                    
    virtual bool undoMoveImpl() = 0;  
    virtual bool redoMoveImpl() = 0; 

    virtual std::vector<std::unique_ptr<BoardMove>> const& getCompletedMovesImpl() const = 0;

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

    std::vector<std::unique_ptr<BoardMove>> generateAllLegalMovesAtSquare(BoardSquare const &boardSquare) const;
    std::vector<std::unique_ptr<BoardMove>> generateAllLegalMoves(Team team) const; 
    std::vector<std::unique_ptr<BoardMove>> generateCapturingMoves(Team team) const;
    std::vector<std::unique_ptr<BoardMove>> generateCheckApplyingMoves(Team team) const;
    std::vector<std::unique_ptr<BoardMove>> generateCaptureAvoidingMoves(Team team) const;

    bool setPosition(BoardSquare const &boardSquare, PieceData const &pieceData);    
    bool clearPosition(BoardSquare const &boardSquare);
    void clearBoard();

    std::optional<std::unique_ptr<BoardMove>> createBoardMove(BoardSquare const &fromSquare, BoardSquare const &toSquare, std::optional<PieceType> promotionPieceType = std::nullopt) const;
    bool makeMove(std::unique_ptr<BoardMove> const &boardMove);
    bool undoMove();  
    bool redoMove(); 

    std::vector<std::unique_ptr<BoardMove>> const& getCompletedMoves() const;

    Team getTeamOne() const;
    Team getTeamTwo() const;

    int getNumRows() const;
    int getNumCols() const;
};


#endif /* ChessBoard_h */
