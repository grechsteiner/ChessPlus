// ChessBoardImpl.h

#ifndef ChessBoardImpl_h
#define ChessBoardImpl_h

#include <memory>
#include <optional>
#include <vector>

#include "BoardMove.h"
#include "BoardSquare.h"
#include "ChessBoard.h"
#include "Cloneable.h"
#include "Constants.h"
#include "Piece.h"
#include "PieceData.h"
#include "PieceInfo.h"


/**
 * ChessBoardImpl ChessBoard Class
 */
class ChessBoardImpl final : public Cloneable<ChessBoard, ChessBoardImpl> {

private:
    Team teamOne = Team::TEAM_ONE;
    Team teamTwo = Team::TEAM_TWO;

    std::vector<std::vector<std::unique_ptr<Piece>>> grid;

    std::vector<std::unique_ptr<BoardMove>> completedMoves;
    std::vector<std::unique_ptr<BoardMove>> redoMoves;


    /* Specific To ChessBoardImpl */
    Team getOtherTeam(Team team) const;

    std::vector<std::unique_ptr<BoardMove>> generateAllPseudoLegalMovesAtSquare(BoardSquare const &boardSquare, bool onlyAttackingMoves) const;
    std::vector<std::unique_ptr<BoardMove>> generateAllPseudoLegalMoves(Team team, bool onlyAttackingMoves) const;   

    void clearRedoMoves();
    bool canMakeMove(Team team) const;

    bool doesMoveApplyCheck(std::unique_ptr<BoardMove> const &boardMove) const;
    bool doesMoveCapturePiece(std::unique_ptr<BoardMove> const &boardMove) const;
    bool doesMoveLeavePieceAttacked(std::unique_ptr<BoardMove> const &boardMove) const;
    bool doesMoveWinGame(std::unique_ptr<BoardMove> const &boardMove) const;
    bool doesMoveLeaveTeamInCheck(std::unique_ptr<BoardMove> const &boardMove) const;   


    /* ChessBoard Interface Implementation */
    std::optional<PieceData> getPieceDataAtImpl(BoardSquare const &boardSquare) const override;
    std::optional<PieceInfo> getPieceInfoAtImpl(BoardSquare const &boardSquare) const override;

    bool isSquareOnBoardImpl(BoardSquare const &boardSquare) const override;
    bool isSquareEmptyImpl(BoardSquare const &boardSquare) const override;
    bool isSquareSameTeamImpl(BoardSquare const &boardSquare, Team ownTeam) const override;
    bool isSquareOtherTeamImpl(BoardSquare const &boardSquare, Team ownTeam) const override;
    bool isSquareAttackedImpl(BoardSquare const &boardSquare, Team ownTeam) const override;

    bool isInCheckImpl(Team team) const override;
    bool isInCheckMateImpl(Team team) const override;
    bool isInStaleMateImpl(Team team) const override;
    
    std::vector<std::unique_ptr<BoardMove>> generateAllLegalMovesAtSquareImpl(BoardSquare const &boardSquare) const override;
    std::vector<std::unique_ptr<BoardMove>> generateAllLegalMovesImpl(Team team) const override; 
    std::vector<std::unique_ptr<BoardMove>> generateCheckApplyingMovesImpl(Team team) const override;
    std::vector<std::unique_ptr<BoardMove>> generateCapturingMovesImpl(Team team) const override;
    std::vector<std::unique_ptr<BoardMove>> generateCaptureAvoidingMovesImpl(Team team) const override;
    std::vector<std::unique_ptr<BoardMove>> generateWinningMovesImpl(Team team) const override;

    void setPositionImpl(BoardSquare const &boardSquare, PieceData const &pieceData) override;
    void clearPositionImpl(BoardSquare const &boardSquare) override;
    void clearBoardImpl() override;

    std::optional<std::unique_ptr<BoardMove>> createBoardMoveImpl(BoardSquare const &fromSquare, BoardSquare const &toSquare, std::optional<PieceType> promotionPieceType = std::nullopt) const override;
    bool isMoveLegalImpl(std::unique_ptr<BoardMove> const &boardMove) const override;
    void makeMoveImpl(std::unique_ptr<BoardMove> const &boardMove) override;    
    bool undoMoveImpl() override;                               // True if move is available to be undone (only performs undo if move available to be undone)
    bool redoMoveImpl() override;                               // True if move is available to be redone (only performs redo if move available to be redone)

    std::vector<std::unique_ptr<BoardMove>> const& getCompletedMovesImpl() const override;

    Team getTeamOneImpl() const override;
    Team getTeamTwoImpl() const override;

    int getNumRowsOnBoardImpl() const override;
    int getNumColsOnBoardImpl() const override;

    BoardSquareIterator beginImpl() override;
    BoardSquareIterator beginImpl() const override;
    BoardSquareIterator cbeginImpl() const override;
    BoardSquareIterator endImpl() override;
    BoardSquareIterator endImpl() const override;
    BoardSquareIterator cendImpl() const override;

    ReverseBoardSquareIterator rbeginImpl() override;
    ReverseBoardSquareIterator rbeginImpl() const override;
    ReverseBoardSquareIterator crbeginImpl() const override;
    ReverseBoardSquareIterator rendImpl() override;
    ReverseBoardSquareIterator rendImpl() const override;
    ReverseBoardSquareIterator crendImpl() const override;

public:
    explicit ChessBoardImpl(int numRowsOnBoard, int numColsOnBoard);
    ChessBoardImpl(ChessBoardImpl const &other);
    ChessBoardImpl(ChessBoardImpl &&other) noexcept;
    ChessBoardImpl& operator=(ChessBoardImpl const &other);
    ChessBoardImpl& operator=(ChessBoardImpl &&other) noexcept;
    virtual ~ChessBoardImpl() = default;
};


#endif /* ChessBoardImpl_h */
