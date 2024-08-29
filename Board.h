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
#include "Move.h"
#include "StandardOpeningTrie.h"
#include "FullMove.h"
#include "UserEnteredMove.h"


class Context;

class Board : public ChessBoard {

private:
    // TODO: Change when 3+ colours
    Color colorOne = Color::WHITE;
    Color colorTwo = Color::BLACK;

    StandardOpeningTrie const &standardOpeningTrie = StandardOpeningTrie::Hardcoded;         // TODO: Read in from file, separate from board class

    std::vector<std::vector<std::unique_ptr<Piece>>> grid;

    std::vector<FullMove> completedMoves;
    std::vector<FullMove> redoMoves;


    /* Utility */
    void initializeBoard();

    std::vector<FullMove> getPseudoLegalMoves(Color color) const;   
    std::vector<FullMove> getAllPseudoLegalAttackingMoves(Color color) const;

    bool doesMoveApplyCheck(FullMove const &fullMove) const;
    bool doesMoveCapturePiece(FullMove const &fullMove) const;
    bool doesMoveHavePieceAttackedAfter(FullMove const &fullMove) const;
    bool canMakeMove(Color color) const;
    bool isInCheckAfterMove(FullMove const &fullMove) const;   



    /* ChessBoard Interface */
    Piece const& getPieceAtImpl(int row, int col) const override;

    bool isEmptySquareOnBoardImpl(int row, int col) const override;
    bool isOpposingColorOnBoardImpl(int row, int col, Color color) const override;
    bool isEmptySquareOrOpposingColorOnBoardImpl(int row, int col, Color color) const override;
    bool isSquareCheckAttackedImpl(int attackedRow, int attackedCol, Color color) const override;
    
    bool isSquareOnBoardImpl(int row, char col) const override;
    void setPositionImpl(int row, char col, Color pieceColor, PieceType pieceType, PieceDirection pieceDirection, bool hasMoved, int pieceScore = -1) override;
    void setPositionImpl(int row, int col, Color pieceColor, PieceType pieceType, PieceDirection pieceDirection, bool hasMoved, int pieceScore = -1) override;
    bool clearPositionImpl(int row, char col) override;
    bool clearPositionImpl(int row, int col) override;
    void clearBoardImpl() override;
    void swapPositionsImpl(int rowOne, int colOne, int rowTwo, int colTwo) override;
    void setHasMovedImpl(int row, int col, bool hasMoved) override;
    bool setBoardSizeImpl(int newNumRows, int newNumCols) override; // Set board to have provided coordinates, returning true if coordinates are valid, false otherwise, Does not change the state of any pieces on the board
    void applyStandardSetupImpl() override;

    std::vector<FullMove> getLegalMovesImpl(Color color) const override; 
    std::vector<FullMove> getCapturingMovesImpl(Color color) const override;
    std::vector<FullMove> getCheckApplyingMovesImpl(Color color) const override;
    std::vector<FullMove> getCaptureAvoidingMovesImpl(Color color) const override;

    Color getColorOneImpl() const override;
    Color getColorTwoImpl() const override;
    Color oppositeColorImpl(Color color) const override;

    std::unique_ptr<FullMove> generateFullMoveImpl(UserEnteredMove const &userEnteredMove) const override;
    FullMove const& getLastMoveImpl() const override;
    bool hasMoveBeenMadeImpl() const override;
    void makeMoveImpl(FullMove const &move) override;                    
    bool undoMoveImpl() override;  
    bool redoMoveImpl() override; 

    int getNumRowsImpl() const override;
    int getNumColsImpl() const override;

    bool isInCheckImpl(Color color) const override;
    bool isInCheckMateImpl(Color color) const override;
    bool isInStaleMateImpl(Color color) const override;
    bool isInStaleMateImpl() const override;
    bool hasGameFinishedImpl() const override;
    bool isBoardInValidStateImpl() const override;

    std::vector<std::pair<std::string, std::string>> getMatchingOpeningsImpl() const override;      // vector<pair(openingName, to_string(move))>
    int getAlphaBetaBoardScoreImpl(Color color) const override;                                     // TODO: Shouldn't be part of board, can do through getPieceAt()

public:
    Board();

    // Max number of letters in alphabet
    // TODO: Remove max once graphic logic is updated
    static int const maxRows = 26;
    static int const maxCols = 26;

    // TODO: Utility
    bool isSquareOnBoard(int row, int col) const;  

};


#endif /* Board_h */
