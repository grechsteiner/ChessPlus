// BoardMoveFactory.cc 

#include "BoardMoveFactory.h"
#include "BoardMove.h"
#include "StandardBoardMove.h"
#include "PromotionBoardMove.h"
#include "CastleBoardMove.h"
#include "PieceData.h"


// Static
std::unique_ptr<BoardMove> BoardMoveFactory::createStandardMove(BoardSquare const &fromSquare, BoardSquare const &toSquare, BoardSquare const &captureSquare, bool doesEnableEnpassant, PieceData const &movedPieceData, std::optional<PieceData> const &capturedPieceData) {
    return std::make_unique<StandardBoardMove>(fromSquare, toSquare, captureSquare, doesEnableEnpassant, movedPieceData, capturedPieceData);
}
    
// Static
std::unique_ptr<BoardMove> BoardMoveFactory::createPromotionMove(BoardSquare const &fromSquare, BoardSquare const &toSquare, BoardSquare const &captureSquare, PieceType promotionPieceType, bool doesEnableEnpassant, PieceData const &movedPieceData, std::optional<PieceData> const &capturedPieceData) {
    return std::make_unique<PromotionBoardMove>(fromSquare, toSquare, captureSquare, promotionPieceType, doesEnableEnpassant, movedPieceData, capturedPieceData);
}
    
// Static
std::unique_ptr<BoardMove> BoardMoveFactory::createCastleMove(BoardSquare const &fromSquare, BoardSquare const &toSquare, BoardSquare const &captureSquare, BoardSquare const &rookFromSquare, BoardSquare const &rookToSquare,  bool doesEnableEnpassant, PieceData const &movedPieceData, std::optional<PieceData> const &capturedPieceData) {
    return std::make_unique<CastleBoardMove>(fromSquare, toSquare, captureSquare, rookFromSquare, rookToSquare, doesEnableEnpassant, movedPieceData, capturedPieceData);
}
