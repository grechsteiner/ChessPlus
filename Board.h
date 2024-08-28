// Board.h

#ifndef Board_h
#define Board_h

#include <memory>
#include <vector>
#include <utility>
#include <set>

#include "BoardGameInterface.h"
#include "BoardDisplayInterface.h"
#include "BoardComputerInterface.h"
#include "BoardMoveInterface.h"
#include "BoardPieceInterface.h"
#include "Constants.h"
#include "Piece.h"
#include "Move.h"
#include "StandardOpeningTrie.h"
#include "FullMove.h"
#include "UserEnteredMove.h"


class Context;

class Board : public BoardPieceInterface, public BoardMoveInterface, public BoardComputerInterface, public BoardDisplayInterface, public BoardGameInterface {

private:
    // TODO: Change when 3+ colours
    Color colorOne = Color::WHITE;
    Color colorTwo = Color::BLACK;

    // TODO: Read in from file, separate from board class
    StandardOpeningTrie const &standardOpeningTrie = StandardOpeningTrie::Hardcoded;

    std::vector<std::vector<std::unique_ptr<Piece>>> grid;

    std::vector<FullMove> completedMoves;
    std::vector<FullMove> redoMoves;

    void initializeBoard();

    std::vector<FullMove> getPseudoLegalMoves(Color color) const;   
    std::vector<FullMove> getAllPseudoLegalAttackingMoves(Color color) const;

    bool doesMoveApplyCheck(FullMove const &fullMove) const;
    bool doesMoveCapturePiece(FullMove const &fullMove) const;
    bool doesMoveHavePieceAttackedAfter(FullMove const &fullMove) const;
    bool canMakeMove(Color color) const;
    bool isInCheckAfterMove(FullMove const &fullMove) const;                 

    // BoardPieceInterface
    Piece const& getPieceAtImpl(int row, int col) const override;
    bool isEmptySquareOnBoardImplementation(int row, int col) const override;
    bool isOpposingColorOnBoardImplementation(int row, int col, Color color) const override;
    bool isEmptySquareOrOpposingColorOnBoardImplementation(int row, int col, Color color) const override;
    bool isSquareCheckAttackedImplementation(int attackedRow, int attackedCol, Color color) const override;
    bool hasMoveBeenMadeImplementation() const override;
    FullMove const& getLastMoveImplementation() const override;
    int getNumRowsImplementation() const override;
    int getNumColsImplementation() const override;

    // BoardMoveInterface (getPieceAtImpl done above)
    // Piece const& getPieceAtImpl(int row, int col) const;
    void setPositionImpl(int row, int col, Color pieceColor, PieceType pieceType, PieceDirection pieceDirection, bool hasMoved, int pieceScore = -1) override;
    void clearPositionImpl(int row, int col) override;
    void swapPositionsImpl(int rowOne, int colOne, int rowTwo, int colTwo) override;
    void setHasMovedImpl(int row, int col, bool hasMoved) override;

    // BoardComputerInterface (getPieceAtImpl done above)
    std::vector<FullMove> getLegalMovesImpl(Color color) const override; 
    std::vector<FullMove> getCapturingMovesImpl(Color color) const override;
    std::vector<FullMove> getCheckApplyingMovesImpl(Color color) const override;
    std::vector<FullMove> getCaptureAvoidingMovesImpl(Color color) const override;

    Color getColorOneImpl() const override;
    Color getColorTwoImpl() const override;
    Color oppositeColorImpl(Color color) const override;

    void makeMoveImpl(FullMove const &move) override;                    
    bool undoMoveImpl() override;   

    // Piece const& getPieceAtImpl(int row, int col) const override;
    bool isInStaleMateImpl(Color color) const override;
    int getAlphaBetaBoardScoreImpl(Color color) const override;


    // Board Display Interface (getPieceAtImpl done above)
    int getNumRowsImpl() const override;
    int getNumColsImpl() const override;

    // Piece const& getPieceAtImpl(int row, int col) const = 0;
    std::vector<std::pair<std::string, std::string>> getMatchingOpeningsImpl() const override;

    bool isInCheckImpl(Color color) const override;
    bool isInCheckMateImpl(Color color) const override;
    //bool isInStaleMateImpl(Color color) const override;


    // Board Game Interface
    bool isInStaleMateImpl() const override;
    bool hasGameFinishedImpl() const override;
    bool isBoardInValidStateImpl() const override;

    void setPositionImpl(int row, char col, Color pieceColor, PieceType pieceType, PieceDirection pieceDirection, bool hasMoved, int pieceScore = -1) override;
    bool clearPositionImpl(int row, char col) override;
    void clearBoardImpl() override;
    
    bool isSquareOnBoardImpl(int row, char col) const override;
    bool setBoardSizeImpl(int newNumRows, int newNumCols) override;
    void applyStandardSetupImpl() override;

    std::unique_ptr<FullMove> generateFullMoveImpl(UserEnteredMove const &userEnteredMove) const override;
    //void makeMoveImpl(FullMove const &move) override;                    
    //bool undoMoveImpl() override;            
    bool redoMoveImpl() override;


    std::unique_ptr<Context> context;
    Context& getContextImpl() override { return *context; }
    

public:
    Board();

    Color oppositeColor(Color color) const;
    Color getColorOne() const;
    Color getColorTwo() const;

    // Max number of letters in alphabet
    // TODO: Remove max once graphic logic is updated
    static int const maxRows = 26;
    static int const maxCols = 26;

    // vector<pair(openingName, to_string(move))>
    std::vector<std::pair<std::string, std::string>> getMatchingOpenings() const;

    // Set board to have provided coordinates, returning true if coordinates are valid, false otherwise
    // Does not change the state of any pieces on the board
    bool setBoardSize(int newNumRows, int newNumCols);

    bool isSquareOnBoard(int row, char col) const;
    bool isSquareOnBoard(int row, int col) const;

    std::vector<FullMove> getLegalMoves(Color color) const; 
    std::vector<FullMove> getCapturingMoves(Color color) const;
    std::vector<FullMove> getCheckApplyingMoves(Color color) const;
    std::vector<FullMove> getCaptureAvoidingMoves(Color color) const;    
    

    bool isInCheck(Color color) const;
    bool isInCheckMate(Color color) const;

    std::unique_ptr<FullMove> generateFullMove(UserEnteredMove const &userEnteredMove) const;                 
    void makeMove(FullMove const &move);                    
    bool undoMove();            
    bool redoMove();                       
    bool hasGameFinished() const;
    bool isInStaleMate(Color colour) const;
    bool isInStaleMate() const;


    void setPosition(int row, char col, Color pieceColor, PieceType pieceType, PieceDirection pieceDirection, bool hasMoved, int pieceScore = -1);
    void setPosition(int row, int col, Color pieceColor, PieceType pieceType, PieceDirection pieceDirection, bool hasMoved, int pieceScore = -1);
    bool clearPosition(int row, char col);
    bool clearPosition(int row, int col);
    void clearBoard();
    void applyStandardSetup();
    bool isBoardInValidState() const;

    int getAlphaBetaBoardScore(Color color) const;   

    const std::vector<std::vector<std::unique_ptr<Piece>>>& getGrid() const {
        return grid;
    }

};


// Interface Converter
class Context {
private:
    Board &board;

public:
    Context(Board &board) : board(board) {}
    BoardPieceInterface& getPieceInterface() { return dynamic_cast<BoardPieceInterface&>(board); }
    BoardMoveInterface& getMoveInterface() { return dynamic_cast<BoardMoveInterface&>(board); }
    BoardDisplayInterface& getDisplayInterface() { return dynamic_cast<BoardDisplayInterface&>(board); }
    BoardComputerInterface& getComputerInterface() { return dynamic_cast<BoardComputerInterface&>(board); }
    BoardGameInterface& getGameInterface() { return dynamic_cast<BoardGameInterface&>(board); }
};


#endif /* Board_h */
