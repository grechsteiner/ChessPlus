// Board.h

#ifndef Board_h
#define Board_h

#include <memory>
#include <vector>
#include <utility>
#include <set>
#include <optional>

#include "ChessBoard.h"
#include "Constants.h"
#include "Piece.h"

#include "StandardOpeningTrie.h"
#include "BoardMove.h"
#include "UserMove.h"
#include "BoardSquare.h"
#include "PieceInfo.h"


class Context;

class Board : public ChessBoard {

private:


    // TODO: Change when 3+ colours
    Team teamOne = Team::TEAM_ONE;
    Team teamTwo = Team::TEAM_TWO;

    std::vector<std::vector<std::unique_ptr<Piece>>> grid;

    std::vector<BoardMove> completedMoves;
    std::vector<BoardMove> redoMoves;


    /* Utility */
    void initializeBoard(std::vector<std::vector<std::unique_ptr<Piece>>> &grid);

    std::vector<BoardMove> getPseudoLegalMovesAtSquare(BoardSquare const &boardSquare, bool onlyAttackingMoves) const;
    std::vector<BoardMove> getPseudoLegalMoves(Team team, bool onlyAttackingMoves) const;   

    // Does not perform any checks of whether of not move is legal
    void performMove(BoardMove const &boardMove);

    bool canMakeMove(Team team) const;
    bool isMoveValid(BoardMove const &boardMove) const;
    bool doesMoveApplyCheck(BoardMove const &boardMove) const;
    bool doesMoveCapturePiece(BoardMove const &boardMove) const;
    bool doesMoveLeavePieceAttacked(BoardMove const &boardMove) const;
    bool isInCheckAfterMove(BoardMove const &boardMove) const;   


    /* ChessBoard Interface */
    std::optional<PieceInfo> getPieceInfoAtImpl(BoardSquare const &boardSquare) const override;
    std::vector<BoardSquare> allBoardSquaresImpl() const override;

    bool isSquareOnBoardImpl(BoardSquare const &boardSquare) const override;
    bool isSquareEmptyImpl(BoardSquare const &boardSquare) const override;
    bool isSquareOwnTeamImpl(BoardSquare const &boardSquare, Team team) const override;
    bool isSquareOtherTeamImpl(BoardSquare const &boardSquare, Team team) const override;
    bool isSquareAttackedImpl(BoardSquare const &boardSquare, Team team) const override;
    
    bool setPositionImpl(BoardSquare const &boardSquare, Team team, PieceType pieceType, PieceDirection pieceDirection, bool hasMoved, std::optional<int> pieceScore = std::nullopt) override;
    bool clearPositionImpl(BoardSquare const &boardSquare) override;
    void clearBoardImpl() override;
    bool setBoardSizeImpl(int newNumRows, int newNumCols) override; // Set board to have provided coordinates, returning true if coordinates are valid, false otherwise, Does not change the state of any pieces on the board

    std::vector<BoardMove> getLegalMovesAtSquareImpl(BoardSquare const &boardSquare) const override;
    std::vector<BoardMove> getLegalMovesImpl(Team team) const override; 
    std::vector<BoardMove> getCapturingMovesImpl(Team team) const override;
    std::vector<BoardMove> getCheckApplyingMovesImpl(Team team) const override;
    std::vector<BoardMove> getCaptureAvoidingMovesImpl(Team team) const override;

    Team getTeamOneImpl() const override;
    Team getTeamTwoImpl() const override;
    Team getOtherTeamImpl(Team team) const override;

    std::optional<BoardMove> createBoardMoveImpl(BoardSquare const &fromSquare, BoardSquare const &toSquare, std::optional<PieceType> promotionPieceType = std::nullopt) const override;
    std::optional<BoardMove> getLastCompletedMoveImpl() const override;
    std::vector<BoardMove> const& getAllCompletedMovesImpl() const override;
    
    bool makeMoveImpl(BoardMove const &move) override;                    
    bool undoMoveImpl() override;  
    bool redoMoveImpl() override; 

    int getNumRowsImpl() const override;
    int getNumColsImpl() const override;

    bool isInCheckImpl(Team team) const override;
    bool isInCheckMateImpl(Team team) const override;
    bool isInStaleMateImpl(Team team) const override;

public:
    Board();

    // Max number of letters in alphabet
    // TODO: Remove max once graphic logic is updated
    // TODO: Define value in .cc (let implementer choose values)
    static int const maxNumRows = 26;
    static int const maxNumCols = 26;
    static int const minNumRows = 4;
    static int const minNumCols = 8;

    

};


#endif /* Board_h */
