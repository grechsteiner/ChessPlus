// CastleBoardMove.cc

#include <vector>

#include "CastleBoardMove.h"

// Basic ctor
CastleBoardMove::CastleBoardMove(BoardSquare const &fromSquare, BoardSquare const &toSquare, BoardSquare const &captureSquare, BoardSquare const &rookFromSquare, BoardSquare const &rookToSquare, bool doesEnableEnpassant, PieceData const &movedPieceData, std::optional<PieceData> const &capturedPieceData) :
    Cloneable<BoardMove, CastleBoardMove>(fromSquare, toSquare, captureSquare, doesEnableEnpassant, movedPieceData, capturedPieceData), rookFromSquare(rookFromSquare), rookToSquare(rookToSquare) {}

// Copy ctor
CastleBoardMove::CastleBoardMove(CastleBoardMove const &other) : 
    Cloneable<BoardMove, CastleBoardMove>(other), rookFromSquare(other.rookFromSquare), rookToSquare(other.rookToSquare) {}

// Move ctor
CastleBoardMove::CastleBoardMove(CastleBoardMove &&other) noexcept : 
    Cloneable<BoardMove, CastleBoardMove>(std::move(other)), rookFromSquare(std::move(other.rookFromSquare)), rookToSquare(std::move(other.rookToSquare)) {}

// Copy assignment
CastleBoardMove& CastleBoardMove::operator=(CastleBoardMove const &other) {
    if (this != &other) {
        BoardMove::operator=(other);
        rookFromSquare = other.rookFromSquare;
        rookToSquare = other.rookToSquare;
    }
    return *this;
}

// Move assignment
CastleBoardMove& CastleBoardMove::operator=(CastleBoardMove &&other) noexcept {
    if (this != &other) {
        BoardMove::operator=(std::move(other));
        rookFromSquare = std::move(other.rookFromSquare);
        rookToSquare = std::move(other.rookToSquare);
    }
    return *this;
}

bool CastleBoardMove::equals(BoardMove const &other) const {
    CastleBoardMove const &derivedOther = static_cast<CastleBoardMove const&>(other);
    return 
        fromSquare == derivedOther.fromSquare &&
        toSquare == derivedOther.toSquare &&
        captureSquare == derivedOther.captureSquare &&
        doesEnableEnpassant == derivedOther.doesEnableEnpassant &&
        movedPieceData == derivedOther.movedPieceData &&
        capturedPieceData == derivedOther.capturedPieceData &&
        rookFromSquare == derivedOther.rookFromSquare &&
        rookToSquare == derivedOther.rookToSquare;
}

void CastleBoardMove::makeBoardMoveImpl(ChessBoard &chessBoard) const {
    // TODO
}
void CastleBoardMove::undoBoardMoveImpl(ChessBoard &chessBoard) const {
    // TODO
}
