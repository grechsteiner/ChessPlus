// ChessBoardImpl.h

#ifndef ChessBoard_h
#define ChessBoard_h

#include <vector>
#include <stack>
#include <optional>
#include <memory>

#include "IChessBoard.h"
#include "Cloneable.h"
#include "Constants.h"
#include "BoardMove.h"
#include "Piece.h"

class BoardSquare;
struct PieceInfo;
struct PieceData;


/**
 * ChessBoardImpl ChessBoard Class
 */
class ChessBoardImpl : public Cloneable<IChessBoard, ChessBoardImpl> {

private:
    int numRows;    // Initialize at construction time to avoid constantly getting size of vector
    int numCols;    // Initialize at construction time to avoid constantly getting size of vector

    Team teamOne = Team::TEAM_ONE;
    Team teamTwo = Team::TEAM_TWO;

    std::stack<BoardMove> completedMoves;
    std::stack<BoardMove> redoMoves;

    std::vector<std::vector<std::unique_ptr<Piece>>> grid;


    /* Specific To Board Class */
    Team getOtherTeam(Team team) const;

    void clearCompletedMoves();
    void clearRedoMoves();

    std::vector<BoardMove> generateAllPseudoLegalMovesAtSquare(BoardSquare const &boardSquare, bool onlyAttackingMoves) const;
    std::vector<BoardMove> generateAllPseudoLegalMoves(Team team, bool onlyAttackingMoves) const;   

    bool canMakeMove(Team team) const;
    bool isMoveValid(BoardMove const &boardMove) const;

    void performMove(BoardMove const &boardMove);   // Does not perform any checks of whether of not move is legal
    void performUndoMove();                         // Does not perform any checks on if move is available to be undone
    void performRedoMove();                         // Does not perform any checks on if move is available to be redone

    bool doesMoveApplyCheck(BoardMove const &boardMove) const;
    bool doesMoveCapturePiece(BoardMove const &boardMove) const;
    bool doesMoveLeavePieceAttacked(BoardMove const &boardMove) const;
    bool doesMoveLeaveTeamInCheck(BoardMove const &boardMove) const;   


    /* ChessBoard Interface */
    std::optional<PieceInfo> getPieceInfoAtImpl(BoardSquare const &boardSquare) const override;
    std::vector<BoardSquare> getAllBoardSquaresImpl() const override;

    bool isSquareOnBoardImpl(BoardSquare const &boardSquare) const override;
    bool isSquareEmptyImpl(BoardSquare const &boardSquare) const override;
    bool isSquareSameTeamImpl(BoardSquare const &boardSquare, Team ownTeam) const override;
    bool isSquareOtherTeamImpl(BoardSquare const &boardSquare, Team ownTeam) const override;
    bool isSquareAttackedImpl(BoardSquare const &boardSquare, Team ownTeam) const override;

    bool isInCheckImpl(Team team) const override;
    bool isInCheckMateImpl(Team team) const override;
    bool isInStaleMateImpl(Team team) const override;
    
    std::vector<BoardMove> generateAllLegalMovesAtSquareImpl(BoardSquare const &boardSquare) const override;
    std::vector<BoardMove> generateAllLegalMovesImpl(Team team) const override; 
    std::vector<BoardMove> generateCapturingMovesImpl(Team team) const override;
    std::vector<BoardMove> generateCheckApplyingMovesImpl(Team team) const override;
    std::vector<BoardMove> generateCaptureAvoidingMovesImpl(Team team) const override;

    // If BoardSquare is on board, completedMoves and redoMoves are erased
    bool setPositionImpl(BoardSquare const &boardSquare, PieceData const &pieceData) override;
    bool clearPositionImpl(BoardSquare const &boardSquare) override;
    void clearBoardImpl() override;

    std::optional<BoardMove> createBoardMoveImpl(BoardSquare const &fromSquare, BoardSquare const &toSquare, std::optional<PieceType> promotionPieceType = std::nullopt) const override;
    bool makeMoveImpl(BoardMove const &boardMove) override;     // True if move is legal move on board (only performs move if legal)         
    bool undoMoveImpl() override;                               // True if move is available to be undone (only performs undo if move available to be undone)
    bool redoMoveImpl() override;                               // True if move is available to be redone (only performs redo if move available to be redone)

    std::optional<BoardMove> getLastCompletedMoveImpl() const override;
    std::stack<BoardMove> const& getAllCompletedMovesImpl() const override;

    Team getTeamOneImpl() const override;
    Team getTeamTwoImpl() const override;

    int getNumRowsImpl() const override;
    int getNumColsImpl() const override;

public:
    explicit ChessBoardImpl(int numRows, int numCols);     // Behaviour undefined if either are negative
    ChessBoardImpl(ChessBoardImpl const &other);
    ChessBoardImpl(ChessBoardImpl &&other) noexcept;
    ChessBoardImpl& operator=(ChessBoardImpl const &other);
    ChessBoardImpl& operator=(ChessBoardImpl &&other) noexcept;
    virtual ~ChessBoardImpl() = default;
};


#endif /* ChessBoard_h */
