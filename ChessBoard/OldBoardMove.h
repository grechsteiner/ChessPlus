// OldBoardMove.h

#ifndef BoardMove_h
#define BoardMove_h

#include <optional>

#include "BoardSquare.h"
#include "Constants.h"
#include "PieceData.h"
#include "PieceInfo.h"

class ChessBoard;


enum class MoveType {
    STANDARD,
    CASTLE,
    ENPASSANT,
    DOUBLE_PAWN
};


/**
 * OldBoardMove Class
 * Represents a move to be performed on a ChessBoard
 * Includes logic for making & undoing itself on a provided ChessBoard (command pattern)
 * If OldBoardMove is not valid for provided board (i.e. fromSquare doesn't exist) behaviour is undefined
 */
class OldBoardMove final {

private:
    MoveType moveType;
    PieceData movedPieceData;                       // PieceData of moved Piece (needed for undoing promotion)

    BoardSquare fromSquare;
    BoardSquare toSquare;
    BoardSquare captureSquare;
    std::optional<PieceData> capturedPieceData;     // PieceData of captured Piece (needed for undoing capture)

    // Promotion move
    std::optional<PieceType> promotionPieceType;

    // Castle move
    std::optional<BoardSquare> rookFromSquare;
    std::optional<BoardSquare> rookToSquare;

    // Utility method for performing the rook logic for castle moves
    void performRookCastle(ChessBoard &chessBoard, bool isUndo) const;

    // Private to prevent construction
    explicit OldBoardMove(
        MoveType moveType, PieceData const &movedPieceData,
        BoardSquare const &fromSquare, BoardSquare const &toSquare, BoardSquare const &captureSquare, std::optional<PieceData> const &capturedPieceData,
        std::optional<PieceType> promotionPieceType, std::optional<BoardSquare> const &rookFromSquare, std::optional<BoardSquare> const &rookToSquare);

public:
    static OldBoardMove createBasicMove(
        MoveType moveType, PieceData const &movedPieceData, 
        BoardSquare const &fromSquare, BoardSquare const &toSquare, BoardSquare const &captureSquare, std::optional<PieceInfo> const &capturedPieceInfo = std::nullopt);
    static OldBoardMove createPromotionMove(
        PieceType promotionPieceType, 
        MoveType moveType, PieceData const &movedPieceData, 
        BoardSquare const &fromSquare, BoardSquare const &toSquare, BoardSquare const &captureSquare, std::optional<PieceInfo> const &capturedPieceInfo = std::nullopt);
    static OldBoardMove createCastleMove(
        BoardSquare const &rookFromSquare, BoardSquare const &rookToSquare, 
        MoveType moveType, PieceData const &movedPieceData, 
        BoardSquare const &fromSquare, BoardSquare const &toSquare, BoardSquare const &captureSquare, std::optional<PieceInfo> const &capturedPieceInfo = std::nullopt);

    OldBoardMove(OldBoardMove const &other) = default;
    OldBoardMove(OldBoardMove &&other) noexcept;
    OldBoardMove& operator=(const OldBoardMove& other) = default;
    OldBoardMove& operator=(OldBoardMove&& other) noexcept;
    ~OldBoardMove() = default;

    bool operator==(OldBoardMove const &other) const;
        
    void makeBoardMove(ChessBoard &chessBoard) const;
    void undoBoardMove(ChessBoard &chessBoard) const;

    MoveType getMoveType() const;
    PieceData const& getMovedPieceData() const;

    BoardSquare const& getFromSquare() const;
    BoardSquare const& getToSquare() const;
    BoardSquare const& getCaptureSquare() const;
    std::optional<PieceData> getCapturedPieceData() const;

    std::optional<PieceType> getPromotionPieceType() const;
    std::optional<BoardSquare> getRookFromSquare() const;
    std::optional<BoardSquare> getRookToSquare() const;
};


#endif /* BoardMove */
