// ChessBoard.h

#ifndef ChessBoard_h
#define ChessBoard_h

#include <memory>
#include <optional>
#include <vector>

#include "BoardMove.h"
#include "BoardSquare.h"
#include "Constants.h"
#include "PieceData.h"
#include "PieceInfo.h"


/**
 * Abstract ChessBoard Class
 */
class ChessBoard {

public:
    /**
     * BoardSquare Iterator Class
     */
    class BoardSquareIterator final {
    private:
        BoardSquare boardSquare;
        int numRowsOnBoard;
        int numColsOnBoard;
        
        explicit BoardSquareIterator(int row, int col, int numRowsOnBoard, int numColsOnBoard);
        friend class ChessBoard;

    public:
        BoardSquareIterator(BoardSquareIterator const &other);
        BoardSquareIterator(BoardSquareIterator &&other) noexcept;
        BoardSquareIterator& operator=(BoardSquareIterator const &other);
        BoardSquareIterator& operator=(BoardSquareIterator &&other) noexcept;
        virtual ~BoardSquareIterator() = default;

        BoardSquare operator*() const;
        BoardSquareIterator& operator++();
        bool operator==(BoardSquareIterator const &other) const;
        bool operator!=(BoardSquareIterator const &other) const;
    };

    /**
     * ReverseBoardSquare Iterator Class
     */
    class ReverseBoardSquareIterator final {
    private:
        BoardSquare boardSquare;
        int numRowsOnBoard;
        int numColsOnBoard;

        explicit ReverseBoardSquareIterator(int row, int col, int numRowsOnBoard, int numColsOnBoard);
        friend class ChessBoard;

    public:
        ReverseBoardSquareIterator(ReverseBoardSquareIterator const &other);
        ReverseBoardSquareIterator(ReverseBoardSquareIterator &&other) noexcept;
        ReverseBoardSquareIterator& operator=(ReverseBoardSquareIterator const &other);
        ReverseBoardSquareIterator& operator=(ReverseBoardSquareIterator &&other) noexcept;
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
    virtual bool isMoveLegalImpl(std::unique_ptr<BoardMove> const &boardMove) const = 0;        
    virtual void makeMoveImpl(std::unique_ptr<BoardMove> const &boardMove) = 0;           
    virtual bool undoMoveImpl() = 0;  
    virtual bool redoMoveImpl() = 0; 

    virtual std::vector<std::unique_ptr<BoardMove>> const& getCompletedMovesImpl() const = 0;

    virtual Team getTeamOneImpl() const = 0;
    virtual Team getTeamTwoImpl() const = 0;

    virtual int getNumRowsOnBoardImpl() const = 0;
    virtual int getNumColsOnBoardImpl() const = 0;

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
    explicit ChessBoard();
    ChessBoard(ChessBoard const &other);
    ChessBoard(ChessBoard &&other) noexcept;
    ChessBoard& operator=(ChessBoard const &other);
    ChessBoard& operator=(ChessBoard &&other) noexcept;

    BoardSquareIterator createBoardSquareIterator(int row, int col, int numRowsOnBoard, int numColsOnBoard) const;
    ReverseBoardSquareIterator createReverseBoardSquareIterator(int row, int col, int numRowsOnBoard, int numColsOnBoard) const;

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
    bool isMoveLegal(std::unique_ptr<BoardMove> const &boardMove) const;
    void makeMove(std::unique_ptr<BoardMove> const &boardMove);
    bool undoMove();  
    bool redoMove(); 

    std::vector<std::unique_ptr<BoardMove>> const& getCompletedMoves() const;

    Team getTeamOne() const;
    Team getTeamTwo() const;

    int getNumRowsOnBoard() const;
    int getNumColsOnBoard() const;

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
