// BoardMove.h

#ifndef BoardMove_h
#define BoardMove_h

#include "Constants.h"
#include "UserMove.h"
#include "BoardSquare.h"



class ChessBoard;
class UserMove;


class BoardMove {

private:
    BoardSquare fromSquare;
    BoardSquare toSquare;
    BoardSquare captureSquare;

    // General Info
    MoveType moveType;
    bool isAttackingMove;
    PieceType promotionPieceType;

    // Moved Piece Info (needed for undoing promotion of non pawn)
    bool hasMoved;
    PieceType pieceType;
    int pieceScore;

    // Captured Piece Info
    Color capturedColor;
    PieceType capturedPieceType;
    PieceDirection capturedPieceDirection;
    bool capturedHasMoved;
    int capturedPieceScore;

    // Logic is exact same for move & undo except for setting hasMoved
    void performRookCastle(ChessBoard &board, bool isUndo) const;

public:

    BoardMove(BoardSquare const &fromSquare, BoardSquare const &toSquare, BoardSquare const &captureSquare, 
            MoveType moveType, bool isAttackingMove, PieceType promotionPieceType,
            bool hasMoved, PieceType pieceType, int pieceScore,
            Color capturedColor, PieceType capturedPieceType, PieceDirection capturedPieceDirection, bool capturedHasMoved, int capturedPieceScore);

   static const BoardMove DEFAULT;

    BoardMove(BoardMove const &other) = default;
    BoardMove(BoardMove &&other) = default;
    BoardMove& operator=(const BoardMove& other) = default;
    BoardMove& operator=(BoardMove&& other) = default;
    ~BoardMove() = default;

    bool operator==(BoardMove const &other) const;
        
    // Commands
    void makeMove(ChessBoard &board) const;
    void undoMove(ChessBoard &board) const;

    bool isEqualToBoardMove(UserMove const &userMove, int numRowsOnBoard, int numColsOnBoard) const;


    /* Getters */
    // TODO: Probably don't need all of these, if any
    
    // Squares
    BoardSquare const& getFromSquare() const;
    BoardSquare const& getToSquare() const;
    BoardSquare const& getCaptureSquare() const;

    // General Info
    MoveType getMoveType() const;
    bool getIsAttackingMove() const;
    PieceType getPromotionPieceType() const;

    // Moved Piece Info
    bool getHasMoved() const;
    PieceType getPieceType() const;
    int getPieceScore() const;

    // Captured Piece Info
    Color getCapturedColor() const;
    PieceType getCapturedPieceType() const;
    PieceDirection getCapturedPieceDirection() const;
    bool getCapturedHasMoved() const;
    int getCapturedPieceScore() const;
};

#endif /* BoardMove */
