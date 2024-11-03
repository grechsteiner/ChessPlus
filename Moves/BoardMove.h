// BoardMove.h

#ifndef BoardMove_h
#define BoardMove_h

#include <optional>

#include "BoardSquare.h"
#include "Constants.h"
#include "PieceData.h"
#include "PieceInfo.h"

class ChessBoard;


class BoardMove {

private:
    virtual bool equals(BoardMove const &other) const = 0;

    virtual std::unique_ptr<BoardMove> cloneImpl() const = 0;
    virtual void makeBoardMoveImpl(ChessBoard &chessBoard) const = 0;
    virtual void undoBoardMoveImpl(ChessBoard &chessBoard) const = 0;
    virtual std::optional<PieceType> getPromotionPieceTypeImpl() const = 0;

protected:
    explicit BoardMove(BoardSquare const &fromSquare, BoardSquare const &toSquare, BoardSquare const &captureSquare, bool doesEnableEnpassant, PieceData const &movedPieceData, std::optional<PieceData> const &capturedPieceData = std::nullopt);
    BoardMove(BoardMove const &other) = default;
    BoardMove(BoardMove &&other) noexcept;
    BoardMove& operator=(BoardMove const &other) = default;
    BoardMove& operator=(BoardMove &&other) noexcept;

    BoardSquare fromSquare;
    BoardSquare toSquare;
    BoardSquare captureSquare;

    bool doesEnableEnpassant;
    PieceData movedPieceData;
    std::optional<PieceData> capturedPieceData;
   
public:
    bool operator==(BoardMove const &other) const;
    virtual ~BoardMove() = default;

    std::unique_ptr<BoardMove> clone() const;
    void makeBoardMove(ChessBoard &chessBoard) const;
    void undoBoardMove(ChessBoard &chessBoard) const;

    BoardSquare const& getFromSquare() const;
    BoardSquare const& getToSquare() const;
    BoardSquare const& getCaptureSquare() const;

    bool getDoesEnableEnpassant() const;
    PieceData const& getMovedPieceData() const;
    std::optional<PieceData> getCapturedPieceData() const;

    std::optional<PieceType> getPromotionPieceType() const;
};


#endif /* BoardMove */
