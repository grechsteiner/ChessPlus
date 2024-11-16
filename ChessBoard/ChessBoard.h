// ChessBoard.h

#ifndef ChessBoard_h
#define ChessBoard_h

#include <vector>
#include <optional>
#include <memory>

#include "Constants.h"
#include "BoardSquare.h"

#include "BoardMove.h"
#include "PieceData.h"
#include "PieceInfo.h"

/**
 * ChessBoard Interface Class
 */
class ChessBoard {

public:
    class BoardSquareIterator final {
    private:
        explicit BoardSquareIterator(int row, int col, int numRows, int numCols);
        BoardSquare boardSquare;
        int numRows;
        int numCols;

        friend class ChessBoard;

    public:
        virtual ~BoardSquareIterator() = default;
        BoardSquare operator*() const;
        BoardSquareIterator& operator++();
        bool operator==(BoardSquareIterator const &other) const;
        bool operator!=(BoardSquareIterator const &other) const;
    };

    class ReverseBoardSquareIterator final {
    private:
        explicit ReverseBoardSquareIterator(int row, int col, int numRows, int numCols);
        BoardSquare boardSquare;
        int numRows;
        int numCols;

        friend class ChessBoard;

    public:
        virtual ~ReverseBoardSquareIterator() = default;
        BoardSquare operator*() const;
        ReverseBoardSquareIterator& operator++();
        bool operator==(ReverseBoardSquareIterator const &other) const;
        bool operator!=(ReverseBoardSquareIterator const &other) const;
    };

private:
    virtual std::unique_ptr<ChessBoard> cloneImpl() const = 0;

    virtual std::optional<PieceData> getPieceDataAtImpl(BoardSquare const &boardSquare) const = 0;
    virtual std::optional<PieceInfo> getPieceInfoAtImpl(BoardSquare const &boardSquare) const = 0;

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
    virtual std::vector<std::unique_ptr<BoardMove>> generateCheckApplyingMovesImpl(Team team) const = 0;
    virtual std::vector<std::unique_ptr<BoardMove>> generateCapturingMovesImpl(Team team) const = 0;
    virtual std::vector<std::unique_ptr<BoardMove>> generateCaptureAvoidingMovesImpl(Team team) const = 0;
    virtual std::vector<std::unique_ptr<BoardMove>> generateWinningMovesImpl(Team team) const = 0;

    virtual void setPositionImpl(BoardSquare const &boardSquare, PieceData const &pieceData) = 0;
    virtual void clearPositionImpl(BoardSquare const &boardSquare) = 0;
    virtual void clearBoardImpl() = 0;

    virtual std::optional<std::unique_ptr<BoardMove>> createBoardMoveImpl(BoardSquare const &fromSquare, BoardSquare const &toSquare, std::optional<PieceType> promotionPieceType = std::nullopt) const = 0;
    virtual void makeMoveImpl(std::unique_ptr<BoardMove> const &boardMove) = 0; 
    virtual bool isMoveValidImpl(std::unique_ptr<BoardMove> const &boardMove) const = 0;                   
    virtual bool undoMoveImpl() = 0;  
    virtual bool redoMoveImpl() = 0; 

    virtual std::vector<std::unique_ptr<BoardMove>> const& getCompletedMovesImpl() const = 0;

    virtual Team getTeamOneImpl() const = 0;
    virtual Team getTeamTwoImpl() const = 0;

    virtual int getNumRowsImpl() const = 0;
    virtual int getNumColsImpl() const = 0;

    virtual BoardSquareIterator beginImpl() = 0;
    virtual BoardSquareIterator beginImpl() const = 0;
    virtual BoardSquareIterator cbeginImpl() const = 0;
    virtual BoardSquareIterator endImpl() = 0;
    virtual BoardSquareIterator endImpl() const = 0;
    virtual BoardSquareIterator cendImpl() const = 0;

    virtual ReverseBoardSquareIterator rbeginImpl() = 0;
    virtual ReverseBoardSquareIterator rbeginImpl() const = 0;
    virtual ReverseBoardSquareIterator crbeginImpl() const = 0;
    virtual ReverseBoardSquareIterator rendImpl() = 0;
    virtual ReverseBoardSquareIterator rendImpl() const = 0;
    virtual ReverseBoardSquareIterator crendImpl() const = 0;

protected:
    BoardSquareIterator createBoardSquareIterator(int row, int col, int numRows, int numCols) const;
    ReverseBoardSquareIterator createReverseBoardSquareIterator(int row, int col, int numRows, int numCols) const;

public:
    std::unique_ptr<ChessBoard> clone() const;
    virtual ~ChessBoard() = default;

    std::optional<PieceData> getPieceDataAt(BoardSquare const &boardSquare) const;
    std::optional<PieceInfo> getPieceInfoAt(BoardSquare const &boardSquare) const;

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
    std::vector<std::unique_ptr<BoardMove>> generateCheckApplyingMoves(Team team) const;
    std::vector<std::unique_ptr<BoardMove>> generateCapturingMoves(Team team) const;
    std::vector<std::unique_ptr<BoardMove>> generateCaptureAvoidingMoves(Team team) const;
    std::vector<std::unique_ptr<BoardMove>> generateWinningMoves(Team team) const;

    void setPosition(BoardSquare const &boardSquare, PieceData const &pieceData);    
    void clearPosition(BoardSquare const &boardSquare);
    void clearBoard();

    std::optional<std::unique_ptr<BoardMove>> createBoardMove(BoardSquare const &fromSquare, BoardSquare const &toSquare, std::optional<PieceType> promotionPieceType = std::nullopt) const;
    void makeMove(std::unique_ptr<BoardMove> const &boardMove);
    bool isMoveValid(std::unique_ptr<BoardMove> const &boardMove) const;
    bool undoMove();  
    bool redoMove(); 

    std::vector<std::unique_ptr<BoardMove>> const& getCompletedMoves() const;

    Team getTeamOne() const;
    Team getTeamTwo() const;

    int getNumRows() const;
    int getNumCols() const;

    BoardSquareIterator begin();
    BoardSquareIterator begin() const;
    BoardSquareIterator cbegin() const;
    BoardSquareIterator end();
    BoardSquareIterator end() const;
    BoardSquareIterator cend() const;

    ReverseBoardSquareIterator rbegin();
    ReverseBoardSquareIterator rbegin() const;
    ReverseBoardSquareIterator crbegin() const;
    ReverseBoardSquareIterator rend();
    ReverseBoardSquareIterator rend() const;
    ReverseBoardSquareIterator crend() const;
};


#endif /* ChessBoard_h */
