// BoardMove.h

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
 * BoardMove Class
 * Represents a move to be performed on a ChessBoard
 * Includes logic for making & undoing itself on a provided ChessBoard (command pattern)
 * If BoardMove is not valid for provided board (i.e. fromSquare doesn't exist) behaviour is undefined
 */
class BoardMove final {

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
    explicit BoardMove(
        MoveType moveType, PieceData const &movedPieceData,
        BoardSquare const &fromSquare, BoardSquare const &toSquare, BoardSquare const &captureSquare, std::optional<PieceData> const &capturedPieceData,
        std::optional<PieceType> promotionPieceType, std::optional<BoardSquare> const &rookFromSquare, std::optional<BoardSquare> const &rookToSquare);

public:
    static BoardMove createBasicMove(
        MoveType moveType, PieceData const &movedPieceData, 
        BoardSquare const &fromSquare, BoardSquare const &toSquare, BoardSquare const &captureSquare, std::optional<PieceInfo> const &capturedPieceInfo = std::nullopt);
    static BoardMove createPromotionMove(
        PieceType promotionPieceType, 
        MoveType moveType, PieceData const &movedPieceData, 
        BoardSquare const &fromSquare, BoardSquare const &toSquare, BoardSquare const &captureSquare, std::optional<PieceInfo> const &capturedPieceInfo = std::nullopt);
    static BoardMove createCastleMove(
        BoardSquare const &rookFromSquare, BoardSquare const &rookToSquare, 
        MoveType moveType, PieceData const &movedPieceData, 
        BoardSquare const &fromSquare, BoardSquare const &toSquare, BoardSquare const &captureSquare, std::optional<PieceInfo> const &capturedPieceInfo = std::nullopt);

    BoardMove(BoardMove const &other) = default;
    BoardMove(BoardMove &&other) noexcept;
    BoardMove& operator=(const BoardMove& other) = default;
    BoardMove& operator=(BoardMove&& other) noexcept;
    ~BoardMove() = default;

    bool operator==(BoardMove const &other) const;
        
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
