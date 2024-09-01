// BoardMove.h

#ifndef BoardMove_h
#define BoardMove_h

#include "Constants.h"
#include "UserMove.h"
#include "BoardSquare.h"
#include "PieceInfo.h"



class ChessBoard;
class UserMove;


class BoardMove {

private:
    BoardSquare fromSquare;
    BoardSquare toSquare;
    BoardSquare captureSquare;

    // Moved Piece Info (needed for undoing promotion of non pawn)
    PieceInfo movedPieceInfo;

    // Captured Piece Info
    std::optional<PieceInfo> capturedPieceInfo;

    // General Info
    MoveType moveType;
    bool isAttackingMove;
    std::optional<PieceType> promotionPieceType;


    // Logic is exact same for move & undo except for setting hasMoved and which is fromRookSquare and which is toRookSquare
    void performRookCastle(ChessBoard &board, bool isUndo) const;

public:

    BoardMove(BoardSquare const &fromSquare, BoardSquare const &toSquare, BoardSquare const &captureSquare,
            PieceInfo movedPieceInfo, std::optional<PieceInfo> capturedPieceInfo,
            MoveType moveType, bool isAttackingMove, std::optional<PieceType> promotionPieceType = std::nullopt);

    // TODO
    BoardMove(BoardMove const &other) = default;
    BoardMove(BoardMove &&other) = default;
    BoardMove& operator=(const BoardMove& other) = default;
    BoardMove& operator=(BoardMove&& other) = default;
    ~BoardMove() = default;

    bool operator==(BoardMove const &other) const;
        
    // Commands
    void makeBoardMove(ChessBoard &board) const;
    void undoBoardMove(ChessBoard &board) const;

    /* Getters */
    // TODO: Probably don't need all of these, if any
    
    // Squares
    BoardSquare getFromSquare() const;
    BoardSquare getToSquare() const;
    BoardSquare getCaptureSquare() const;

    // Moved Piece Info
    PieceInfo getMovedPieceInfo() const;

    // Captured Piece Info
    std::optional<PieceInfo> getCapturedPieceInfo() const;

    // General Info
    MoveType getMoveType() const;
    bool getIsAttackingMove() const;
    std::optional<PieceType> getPromotionPieceType() const;
};

#endif /* BoardMove */
