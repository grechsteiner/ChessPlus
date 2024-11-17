// StandardBoardMove.cc

#include "StandardBoardMove.h"

#include <optional>
#include <utility>

#include "BoardMove.h"
#include "BoardSquare.h"
#include "Cloneable.h"
#include "Constants.h"
#include "PieceData.h"


// Basic ctor
StandardBoardMove::StandardBoardMove(BoardSquare const &fromSquare, BoardSquare const &toSquare, BoardSquare const &captureSquare, bool doesEnableEnpassant, PieceData const &movedPieceData, std::optional<PieceData> const &capturedPieceData) :
    Cloneable<BoardMove, StandardBoardMove>(fromSquare, toSquare, captureSquare, doesEnableEnpassant, movedPieceData, capturedPieceData) { }

// Copy ctor
StandardBoardMove::StandardBoardMove(StandardBoardMove const &other) : 
    Cloneable<BoardMove, StandardBoardMove>(other) { }

// Move ctor
StandardBoardMove::StandardBoardMove(StandardBoardMove &&other) noexcept : 
    Cloneable<BoardMove, StandardBoardMove>(std::move(other)) { }

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

// Equality
bool StandardBoardMove::operator==(StandardBoardMove const &other) const {
    return 
        fromSquare == other.fromSquare &&
        toSquare == other.toSquare &&
        captureSquare == other.captureSquare &&
        doesEnableEnpassant == other.doesEnableEnpassant &&
        movedPieceData == other.movedPieceData &&
        capturedPieceData == other.capturedPieceData;
}

// Inequality
bool StandardBoardMove::operator!=(StandardBoardMove const &other) const {
    return !(*this == other);
}

/*
 * Polymorphic equality
 */
bool StandardBoardMove::equals(BoardMove const &other) const {
    StandardBoardMove const &derivedOther = static_cast<StandardBoardMove const&>(other);
    return *this == derivedOther;
}

/*
 * Apply itself to ChessBoard argument
 */
void StandardBoardMove::makeBoardMoveImpl(ChessBoard &chessBoard) const {
    chessBoard.clearPosition(captureSquare);
    chessBoard.setPosition(toSquare, PieceData(movedPieceData.pieceType, movedPieceData.pieceLevel, movedPieceData.team, movedPieceData.pieceDirection, true));
    chessBoard.clearPosition(fromSquare);
}

/*
 * Un-apply itself to ChessBoard argument
 */
void StandardBoardMove::undoBoardMoveImpl(ChessBoard &chessBoard) const {
    chessBoard.setPosition(fromSquare, movedPieceData);
    chessBoard.clearPosition(toSquare);

    // Place captured Piece back
    if (capturedPieceData.has_value()) {
        chessBoard.setPosition(captureSquare, capturedPieceData.value());    
    }
}
