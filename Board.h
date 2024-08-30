// Board.h

#ifndef Board_h
#define Board_h

#include <memory>
#include <vector>
#include <utility>
#include <set>

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

    std::vector<BoardMove> getPseudoLegalMoves(Team team) const;   
    std::vector<BoardMove> getAllPseudoLegalAttackingMoves(Team team) const;

    bool doesMoveApplyCheck(BoardMove const &boardMove) const;
    bool doesMoveCapturePiece(BoardMove const &boardMove) const;
    bool doesMoveHavePieceAttackedAfter(BoardMove const &boardMove) const;
    bool canMakeMove(Team team) const;
    bool isInCheckAfterMove(BoardMove const &boardMove) const;   

    std::vector<BoardMove> getPieceMovesAtSquare(BoardSquare const &boardSquare, bool onlyAttackingMoves) const;


    /* ChessBoard Interface */
    PieceInfo getPieceInfoAtImpl(BoardSquare const &boardSquare) const override;
    std::vector<BoardSquare> allBoardSquaresImpl() const override;

    bool isEmptySquareOnBoardImpl(BoardSquare const &boardSquare) const override;
    bool isOpposingTeamOnBoardImpl(BoardSquare const &boardSquare, Team team) const override;
    bool isEmptySquareOrOpposingTeamOnBoardImpl(BoardSquare const &boardSquare, Team team) const override;
    bool isSquareAttackedImpl(BoardSquare const &boardSquare, Team team) const override;
    
    bool isSquareOnBoardImpl(BoardSquare const &boardSquare) const override;
    void setPositionImpl(BoardSquare const &boardSquare, Team team, PieceType pieceType, PieceDirection pieceDirection, bool hasMoved, int pieceScore = -1) override;
    bool clearPositionImpl(BoardSquare const &boardSquare) override;
    void clearBoardImpl() override;
    void swapPositionsImpl(BoardSquare const &boardSquareOne, BoardSquare const &boardSquareTwo) override;
    void setHasMovedImpl(BoardSquare const &boardSquare, bool hasMoved) override;
    bool setBoardSizeImpl(int newNumRows, int newNumCols) override; // Set board to have provided coordinates, returning true if coordinates are valid, false otherwise, Does not change the state of any pieces on the board
    void applyStandardSetupImpl() override;

    std::vector<BoardMove> getLegalMovesImpl(Team team) const override; 
    std::vector<BoardMove> getCapturingMovesImpl(Team team) const override;
    std::vector<BoardMove> getCheckApplyingMovesImpl(Team team) const override;
    std::vector<BoardMove> getCaptureAvoidingMovesImpl(Team team) const override;

    Team getTeamOneImpl() const override;
    Team getTeamTwoImpl() const override;
    Team getOtherTeamImpl(Team team) const override;

    std::unique_ptr<BoardMove> generateBoardMoveImpl(UserMove const &userMove) const override;
    BoardMove const& getLastMadeMoveImpl() const override;
    std::vector<BoardMove> const& getAllMadeMovesImpl() const override;
    bool hasMoveBeenMadeImpl() const override;
    void makeMoveImpl(BoardMove const &move) override;                    
    bool undoMoveImpl() override;  
    bool redoMoveImpl() override; 

    int getNumRowsImpl() const override;
    int getNumColsImpl() const override;

    bool isInCheckImpl(Team team) const override;
    bool isInCheckMateImpl(Team team) const override;
    bool isInStaleMateImpl(Team team) const override;
    bool isInStaleMateImpl() const override;
    bool hasGameFinishedImpl() const override;
    bool isBoardInValidStateImpl() const override;

public:
    Board();

    // Max number of letters in alphabet
    // TODO: Remove max once graphic logic is updated
    static int const maxNumRows = 26;
    static int const maxNumCols = 26;
    static int const minNumRows = 4;
    static int const minNumCols = 8;

    // TODO: Utility
    

};


#endif /* Board_h */
