// BoardMove.h

#ifndef BoardMove_h
#define BoardMove_h

#include <optional>

#include "BoardSquare.h"
#include "Constants.h"
#include "PieceInfo.h"

class ChessBoard;


enum class MoveType {
    STANDARD,
    CASTLE,
    ENPASSANT,
    DOUBLE_PAWN
};


/**
 * BoardMove Class
 * Represents a move to be performed on a ChessBoard
 * Includes logic for making & undoing itself on a provided ChessBoard (command pattern)
 * If BoardMove is not valid for provided board (i.e. fromSquare doesn't exist) behaviour is undefined
 */
class BoardMove final {

private:
    MoveType moveType;
    PieceInfo movedPieceInfo;                       // PieceInfo of moved Piece (needed for undoing promotion)

    BoardSquare fromSquare;
    BoardSquare toSquare;
    BoardSquare captureSquare;
    std::optional<PieceInfo> capturedPieceInfo;     // PieceInfo of captured Piece (needed for undoing capture)

    // Promotion move
    std::optional<PieceType> promotionPieceType;

    // Castle move
    std::optional<BoardSquare> rookFromSquare;
    std::optional<BoardSquare> rookToSquare;

    // Utility method for performing the rook logic for castle moves
    void performRookCastle(ChessBoard &board, bool isUndo) const;

    // Private to prevent construction
    explicit BoardMove(
        MoveType moveType, PieceInfo const &movedPieceInfo,
        BoardSquare const &fromSquare, BoardSquare const &toSquare, BoardSquare const &captureSquare, std::optional<PieceInfo> const &capturedPieceInfo,
        std::optional<PieceType> promotionPieceType, std::optional<BoardSquare> const &rookFromSquare, std::optional<BoardSquare> const &rookToSquare);

public:
    static BoardMove createBasicMove(
        MoveType moveType, PieceInfo const &movedPieceInfo, 
        BoardSquare const &fromSquare, BoardSquare const &toSquare, BoardSquare const &captureSquare, std::optional<PieceInfo> const &capturedPieceInfo = std::nullopt);
    static BoardMove createPromotionMove(
        PieceType promotionPieceType, 
        MoveType moveType, PieceInfo const &movedPieceInfo, 
        BoardSquare const &fromSquare, BoardSquare const &toSquare, BoardSquare const &captureSquare, std::optional<PieceInfo> const &capturedPieceInfo = std::nullopt);
    static BoardMove createCastleMove(
        BoardSquare const &rookFromSquare, BoardSquare const &rookToSquare, 
        MoveType moveType, PieceInfo const &movedPieceInfo, 
        BoardSquare const &fromSquare, BoardSquare const &toSquare, BoardSquare const &captureSquare, std::optional<PieceInfo> const &capturedPieceInfo = std::nullopt);

    BoardMove(BoardMove const &other) = default;
    BoardMove(BoardMove &&other) noexcept;
    BoardMove& operator=(const BoardMove& other) = default;
    BoardMove& operator=(BoardMove&& other) noexcept;
    ~BoardMove() = default;

    bool operator==(BoardMove const &other) const;
        
    void makeBoardMove(ChessBoard &board) const;
    void undoBoardMove(ChessBoard &board) const;

    MoveType getMoveType() const;
    PieceInfo const& getMovedPieceInfo() const;

    BoardSquare const& getFromSquare() const;
    BoardSquare const& getToSquare() const;
    BoardSquare const& getCaptureSquare() const;
    std::optional<PieceInfo> getCapturedPieceInfo() const;

    std::optional<PieceType> getPromotionPieceType() const;
    std::optional<BoardSquare> getRookFromSquare() const;
    std::optional<BoardSquare> getRookToSquare() const;
};


#endif /* BoardMove */
