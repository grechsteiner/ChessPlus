// BoardMove.h

#ifndef BoardMove_h
#define BoardMove_h

#include <memory>
#include <optional>

#include "BoardSquare.h"
#include "ChessBoard.h"
#include "Constants.h"
#include "PieceData.h"


/**
 * Abstract BoardMove Class
 */
class BoardMove {
private:
    virtual bool equals(BoardMove const &other) const = 0;

    virtual std::unique_ptr<BoardMove> cloneImpl() const = 0;
    virtual void makeBoardMoveImpl(ChessBoard &chessBoard) const = 0;
    virtual void undoBoardMoveImpl(ChessBoard &chessBoard) const = 0;
    virtual std::optional<PieceType> getPromotionPieceTypeImpl() const = 0;

protected:
    BoardSquare fromSquare;
    BoardSquare toSquare;
    BoardSquare captureSquare;

    bool doesEnableEnpassant;
    PieceData movedPieceData;
    std::optional<PieceData> capturedPieceData;

    explicit BoardMove(BoardSquare const &fromSquare, BoardSquare const &toSquare, BoardSquare const &captureSquare, bool doesEnableEnpassant, PieceData const &movedPieceData, std::optional<PieceData> const &capturedPieceData = std::nullopt);
    BoardMove(BoardMove const &other);
    BoardMove(BoardMove &&other) noexcept;
    BoardMove& operator=(BoardMove const &other);
    BoardMove& operator=(BoardMove &&other) noexcept;
   
public:
    bool operator==(BoardMove const &other) const;
    bool operator!=(BoardMove const &other) const;

    virtual ~BoardMove() = default;

    std::unique_ptr<BoardMove> clone() const;
    void makeBoardMove(ChessBoard &chessBoard) const;
    void undoBoardMove(ChessBoard &chessBoard) const;
    std::optional<PieceType> getPromotionPieceType() const;

    BoardSquare const& getFromSquare() const;
    BoardSquare const& getToSquare() const;
    BoardSquare const& getCaptureSquare() const;

    bool getDoesEnableEnpassant() const;
    PieceData const& getMovedPieceData() const;
    std::optional<PieceData> getCapturedPieceData() const;
};


#endif /* BoardMove */
