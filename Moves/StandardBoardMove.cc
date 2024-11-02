// StandardBoardMove.cc

#include <vector>

#include "StandardBoardMove.h"
#include "ChessBoard.h"

// Basic ctor
StandardBoardMove::StandardBoardMove(BoardSquare const &fromSquare, BoardSquare const &toSquare, BoardSquare const &captureSquare, bool doesEnableEnpassant, PieceData const &movedPieceData, std::optional<PieceData> const &capturedPieceData) :
    Cloneable<BoardMove, StandardBoardMove>(fromSquare, toSquare, captureSquare, doesEnableEnpassant, movedPieceData, capturedPieceData) {}

// Copy ctor
StandardBoardMove::StandardBoardMove(StandardBoardMove const &other) : 
    Cloneable<BoardMove, StandardBoardMove>(other) {}

// Move ctor
StandardBoardMove::StandardBoardMove(StandardBoardMove &&other) noexcept : 
    Cloneable<BoardMove, StandardBoardMove>(std::move(other)) {}

// Copy assignment
StandardBoardMove& StandardBoardMove::operator=(StandardBoardMove const &other) {
    if (this != &other) {
        BoardMove::operator=(other);
    }
    return *this;
}

// Move assignment
StandardBoardMove& StandardBoardMove::operator=(StandardBoardMove &&other) noexcept {
    if (this != &other) {
        BoardMove::operator=(std::move(other));
    }
    return *this;
}

bool StandardBoardMove::equals(BoardMove const &other) const {
    StandardBoardMove const &derivedOther = static_cast<StandardBoardMove const&>(other);
    return 
        fromSquare == derivedOther.fromSquare &&
        toSquare == derivedOther.toSquare &&
        captureSquare == derivedOther.captureSquare &&
        doesEnableEnpassant == derivedOther.doesEnableEnpassant &&
        movedPieceData == derivedOther.movedPieceData &&
        capturedPieceData == derivedOther.capturedPieceData;
}

void StandardBoardMove::makeBoardMoveImpl(ChessBoard &chessBoard) const {
    chessBoard.clearPosition(captureSquare);
    chessBoard.setPosition(toSquare, PieceData(movedPieceData.pieceType, movedPieceData.pieceLevel, movedPieceData.team, movedPieceData.pieceDirection, true));
    chessBoard.clearPosition(fromSquare);
}

void StandardBoardMove::undoBoardMoveImpl(ChessBoard &chessBoard) const {
    chessBoard.setPosition(fromSquare, movedPieceData);
    chessBoard.clearPosition(toSquare);

    // Place Captured Piece Back
    if (capturedPieceData.has_value()) {
        chessBoard.setPosition(captureSquare, capturedPieceData.value());    
    } else {
        chessBoard.clearPosition(captureSquare);
    }
}
