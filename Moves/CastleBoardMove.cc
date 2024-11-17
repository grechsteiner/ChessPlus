// CastleBoardMove.cc

#include "CastleBoardMove.h"

#include <optional>
#include <utility>

#include "BoardMove.h"
#include "BoardSquare.h"
#include "Cloneable.h"
#include "Constants.h"
#include "PieceData.h"


/*
 * Basic ctor
 */
CastleBoardMove::CastleBoardMove(BoardSquare const &fromSquare, BoardSquare const &toSquare, BoardSquare const &captureSquare, BoardSquare const &rookFromSquare, BoardSquare const &rookToSquare, bool doesEnableEnpassant, PieceData const &movedPieceData, std::optional<PieceData> const &capturedPieceData) :
    Cloneable<BoardMove, CastleBoardMove>(fromSquare, toSquare, captureSquare, doesEnableEnpassant, movedPieceData, capturedPieceData), rookFromSquare(rookFromSquare), rookToSquare(rookToSquare) { }

/*
 * Copy ctor
 */
CastleBoardMove::CastleBoardMove(CastleBoardMove const &other) : 
    Cloneable<BoardMove, CastleBoardMove>(other), rookFromSquare(other.rookFromSquare), rookToSquare(other.rookToSquare) { }

/*
 * Move ctor
 */
CastleBoardMove::CastleBoardMove(CastleBoardMove &&other) noexcept : 
    Cloneable<BoardMove, CastleBoardMove>(std::move(other)), rookFromSquare(std::move(other.rookFromSquare)), rookToSquare(std::move(other.rookToSquare)) { }

/*
 * Copy assignment
 */
CastleBoardMove& CastleBoardMove::operator=(CastleBoardMove const &other) {
    if (this != &other) {
        BoardMove::operator=(other);
        rookFromSquare = other.rookFromSquare;
        rookToSquare = other.rookToSquare;
    }
    return *this;
}

/*
 * Move assignment
 */
CastleBoardMove& CastleBoardMove::operator=(CastleBoardMove &&other) noexcept {
    if (this != &other) {
        BoardMove::operator=(std::move(other));
        rookFromSquare = std::move(other.rookFromSquare);
        rookToSquare = std::move(other.rookToSquare);
    }
    return *this;
}

/*
 * Equality
 */
bool CastleBoardMove::operator==(CastleBoardMove const &other) const {
    return 
        fromSquare == other.fromSquare &&
        toSquare == other.toSquare &&
        captureSquare == other.captureSquare &&
        doesEnableEnpassant == other.doesEnableEnpassant &&
        movedPieceData == other.movedPieceData &&
        capturedPieceData == other.capturedPieceData &&
        rookFromSquare == other.rookFromSquare &&
        rookToSquare == other.rookToSquare;
}

/*
 * Inequality
 */
bool CastleBoardMove::operator!=(CastleBoardMove const &other) const {
    return !(*this == other);
}

/*
 * Polymorphic equality
 */
bool CastleBoardMove::equals(BoardMove const &other) const {
    CastleBoardMove const &derivedOther = static_cast<CastleBoardMove const&>(other);
    return *this == derivedOther;
}

/*
 * Apply itself to ChessBoard argument
 */
void CastleBoardMove::makeBoardMoveImpl(ChessBoard &chessBoard) const {
    chessBoard.clearPosition(captureSquare);
    chessBoard.setPosition(toSquare, PieceData(movedPieceData.pieceType, movedPieceData.pieceLevel, movedPieceData.team, movedPieceData.pieceDirection, true));
    chessBoard.clearPosition(fromSquare);

    // Apply Castle (rook part)
    performRookCastle(chessBoard, false);
}

/*
 * Un-apply itself to ChessBoard argument
 */
void CastleBoardMove::undoBoardMoveImpl(ChessBoard &chessBoard) const {
    chessBoard.setPosition(fromSquare, movedPieceData);
    chessBoard.clearPosition(toSquare);

    // Place captured Piece back
    if (capturedPieceData.has_value()) {
        chessBoard.setPosition(captureSquare, capturedPieceData.value());    
    } else {
        chessBoard.clearPosition(captureSquare);
    }

    // Undo Castle (rook part)
    performRookCastle(chessBoard, true);
}

/*
 * Utility method for performing the rook logic of a CastleBoardMove
 */
void CastleBoardMove::performRookCastle(ChessBoard &chessBoard, bool undoingMove) const {
    PieceData rookPieceData = undoingMove 
        ? chessBoard.getPieceDataAt(rookToSquare).value() 
        : chessBoard.getPieceDataAt(rookFromSquare).value();

    if (undoingMove) {
        chessBoard.setPosition(rookFromSquare, PieceData(rookPieceData.pieceType, rookPieceData.pieceLevel, rookPieceData.team, rookPieceData.pieceDirection, false));
        chessBoard.clearPosition(rookToSquare);
    } else {
        chessBoard.setPosition(rookToSquare, PieceData(rookPieceData.pieceType, rookPieceData.pieceLevel, rookPieceData.team, rookPieceData.pieceDirection, true));
        chessBoard.clearPosition(rookFromSquare);
    }
}
