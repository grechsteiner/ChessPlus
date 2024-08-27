// Board.h

#ifndef Board_h
#define Board_h

#include <memory>
#include <vector>
#include <utility>
#include <set>

#include "BoardPieceInterface.h"
#include "Constants.h"
#include "Piece.h"
#include "Move.h"
#include "StandardOpeningTrie.h"


class Board : public BoardPieceInterface {

private:
    Color colorOne = Color::WHITE;
    Color colorTwo = Color::BLACK;

    // TODO: Read in from file
    StandardOpeningTrie const &standardOpeningTrie = StandardOpeningTrie::Hardcoded;

    std::vector<std::vector<std::unique_ptr<Piece>>> grid;
    std::vector<CompletedMove> completedMoves;
    std::vector<CompletedMove> redoMoves;   // TODO

    void initializeBoard();

    std::vector<Move> getPseudoLegalMoves(Color color) const;   
    std::vector<Move> getAllPseudoLegalAttackingMoves(Color color) const;

    bool doesMoveApplyCheck(Move const &move) const;
    bool doesMoveCapturePiece(Move const &move) const;
    bool doesMoveHavePieceAttackedAfter(Move const &move) const;
    bool canMakeMove(Color color) const;
    bool isInCheckAfterMove(Move const &move) const;                 

    // BoardPieceInterface
    const std::unique_ptr<Piece>& getPieceAtImplementation(int row, int col) const override;
    bool isEmptySquareOnBoardImplementation(int row, int col) const override;
    bool isOpposingColorOnBoardImplementation(int row, int col, Color color) const override;
    bool isEmptySquareOrOpposingColorOnBoardImplementation(int row, int col, Color color) const override;
    bool isSquareCheckAttackedImplementation(int attackedRow, int attackedCol, Color color) const override;
    bool lastMoveImplementation() const override;
    const CompletedMove& getLastMoveImplementation() const override;
    int getNumRowsImplementation() const override;
    int getNumColsImplementation() const override;

public:
    Board();

    Color oppositeColor(Color color) const;
    Color getColorOne() const;
    Color getColorTwo() const;

    // Max number of letters in alphabet
    static int const maxRows = 26;
    static int const maxCols = 26;

    // vector<pair(openingName, to_string(move))>
    std::vector<std::pair<std::string, std::string>> getMatchingOpenings() const;

    // Set board to have provided coordinates, returning true if coordinates are valid, false otherwise
    // Does not change the state of any pieces on the board
    bool setBoardSize(int newNumRows, int newNumCols);

    bool isSquareOnBoard(int row, char col) const;
    bool isSquareOnBoard(int row, int col) const;

    std::vector<Move> getLegalMoves(Color color) const; 
    std::vector<Move> getCapturingMoves(Color color) const;
    std::vector<Move> getCheckApplyingMoves(Color color) const;
    std::vector<Move> getCaptureAvoidingMoves(Color color) const;    
    

    bool isInCheck(Color color) const;
    bool isInCheckMate(Color color) const;

    bool isMoveLegal(Move const &move) const;                 
    void makeMove(Move const &move);                    
    bool undoMove();                                   
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


#endif /* Board_h */
