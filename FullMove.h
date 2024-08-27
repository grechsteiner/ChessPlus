// FullMove.h

#ifndef FullMove_h
#define FullMove_h

#include "Constants.h"
#include "BoardMoveInterface.h"



class FullMove {

private:
    int const fromRow, toRow, captureRow;     // 0: top row
    int const fromCol, toCol, captureCol;     // 0: leftmost col

    // General Info
    bool const hasMoved;
    PieceType const promotionPieceType;
    MoveType const moveType;
    bool const isAttackingMove;

    // Moved Piece Info (needed for undoing promotion of non pawn)
    PieceType const pieceType;
    int const pieceScore;

    // Captured Piece Info
    Color const capturedColor;
    PieceType const capturedPieceType;
    PieceDirection const capturedPieceDirection;
    bool const capturedHasMoved;
    int const capturedPieceScore;

    // Logic is exact same for move & undo except for setting hasMoved
    void performRookCastle(BoardMoveInterface &board, bool isUndo) const;

public:

    FullMove(int fromRow, int fromCol, int toRow, int toCol, int captureRow, int captureCol, 
            bool hasMoved, PieceType promotionPieceType, MoveType moveType, bool isAttackingMove,
            PieceType pieceType, int pieceScore,
            Color capturedColor, PieceType capturedPieceType, PieceDirection capturedPieceDirection, bool capturedHasMoved, int capturedPieceScore);

    // captureRow/captureCol default set to toRow/toCol
    FullMove(int fromRow, int fromCol, int toRow, int toCol,
            bool hasMoved, PieceType promotionPieceType, MoveType moveType, bool isAttackingMove,
            PieceType pieceType, int pieceScore,
            Color capturedColor, PieceType capturedPieceType, PieceDirection capturedPieceDirection, bool capturedHasMoved, int capturedPieceScore);

    FullMove(FullMove const &other);
    FullMove(FullMove &&other);
    FullMove& operator=(const FullMove& other) = delete;
    FullMove& operator=(FullMove&& other) = delete;
    ~FullMove() = default;
        
    std::string const& toString() const;

    // Commands
    void makeMove(BoardMoveInterface &board) const;
    bool undoMove(BoardMoveInterface &board) const;


    /* Getters */
    // TODO: Probably don't need all of these, if any
    
    // Squares
    int getFromRow() const;
    int getToRow() const;
    int getCaptureRow() const;
    int getFromCol() const;
    int getToCol() const;
    int getCaptureCol() const;

    // General Info
    bool getHasMoved() const;
    PieceType getPromotionPieceType() const;
    MoveType getMoveType() const;
    bool getIsAttackingMove() const;

    // Moved Piece Info
    PieceType getPieceType() const;
    int getPieceScore() const;

    // Captured Piece Info
    Color getCapturedColor() const;
    PieceType getCapturedPieceType() const;
    PieceDirection getCapturedPieceDirection() const;
    bool getCapturedHasMoved() const;
    int getCapturedPieceScore() const;
};


#endif /* FullMove_h */
