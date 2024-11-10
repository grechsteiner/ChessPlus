// ChessBoardUtilities.cc

#include <memory>

#include "ChessBoardUtilities.h"
#include "ChessBoard.h"
#include "PieceData.h"
#include "Piece.h"


// Static
std::vector<PieceType> const ChessBoardUtilities::standardBackrowSetupOrder = {
    PieceType::ROOK,
    PieceType::KNIGHT,
    PieceType::BISHOP,
    PieceType::QUEEN,
    PieceType::KING,
    PieceType::BISHOP,
    PieceType::KNIGHT,
    PieceType::ROOK
};

// Static
// 1 king per team
// Not in checkmate
// No pawns in places where they should be promoted
bool ChessBoardUtilities::isBoardInLegalSetupState(std::unique_ptr<ChessBoard> const &chessBoard) {
    int topRow = 0;
    int bottomRow = chessBoard->getNumRows() - 1;
    int leftCol = 0;
    int rightCol = chessBoard->getNumCols() - 1;

    int teamOneKingCount = 0;
    int teamTwoKingCount = 0;

    for (ChessBoard::BoardSquareIterator it = chessBoard->begin(); it != chessBoard->end(); ++it) {
        std::optional<PieceData> pieceData = chessBoard->getPieceDataAt(*it);
        if (pieceData.has_value()) {

            PieceType pieceType = pieceData.value().pieceType;
            if (pieceType == PieceType::KING) {
                Team team = pieceData.value().team;

                // Checkmate
                if (chessBoard->isSquareAttacked(*it, team)) {
                    return false;
                }

                // King count
                if (team == chessBoard->getTeamOne()) {
                    teamOneKingCount++;
                } else if (team == chessBoard->getTeamTwo()) {
                    teamTwoKingCount++;
                }
            } else if (pieceType == PieceType::PAWN) {
                PieceDirection pieceDirection = pieceData.value().pieceDirection;
                int boardRow = (*it).boardRow;
                int boardCol = (*it).boardCol;

                // Is pawn in position where it should be promoted
                bool isPawnInPromotionPosition = 
                    (pieceDirection == PieceDirection::NORTH && boardRow == topRow) ||
                    (pieceDirection == PieceDirection::SOUTH && boardRow == bottomRow) ||
                    (pieceDirection == PieceDirection::EAST && boardCol == leftCol) ||
                    ((pieceDirection == PieceDirection::WEST && boardCol == rightCol));
                if (isPawnInPromotionPosition) {
                    return false;
                }
            }
        }
        
    }

    return teamOneKingCount == 1 && teamTwoKingCount == 1;
}

// Static
// Standard chess setup
// False if can't be applied with current board size
// Centred if more than backrow num col
bool ChessBoardUtilities::applyStandardSetup(std::unique_ptr<ChessBoard> &chessBoard) {
    static PieceLevel const pieceLevelForStandardSetup = PieceLevel::BASIC;

    if (chessBoard->getNumRows() < 4 || chessBoard->getNumCols() < standardBackrowSetupOrder.size()) {
        return false;
    }

    chessBoard->clearBoard();
 
    int firstPieceCol = (chessBoard->getNumCols() - 8) / 2;
    int topRow = 0;
    int bottomRow = chessBoard->getNumRows() - 1;
    for (int standardBackrowIndex = 0; standardBackrowIndex < standardBackrowSetupOrder.size(); ++standardBackrowIndex) {
        PieceType currentPieceType = standardBackrowSetupOrder[standardBackrowIndex];
        int currentBoardCol = standardBackrowIndex + firstPieceCol;

        // Team One
        chessBoard->setPosition(BoardSquare(bottomRow, currentBoardCol), PieceData(currentPieceType, pieceLevelForStandardSetup, Team::TEAM_ONE, PieceDirection::NORTH, false));
        chessBoard->setPosition(BoardSquare(bottomRow - 1, currentBoardCol), PieceData(PieceType::PAWN, pieceLevelForStandardSetup, Team::TEAM_ONE, PieceDirection::NORTH, false));

        // Team Two
        chessBoard->setPosition(BoardSquare(topRow, currentBoardCol), PieceData(currentPieceType, pieceLevelForStandardSetup, Team::TEAM_TWO, PieceDirection::SOUTH, false));
        chessBoard->setPosition(BoardSquare(topRow + 1, currentBoardCol), PieceData(PieceType::PAWN, pieceLevelForStandardSetup, Team::TEAM_TWO, PieceDirection::SOUTH, false));
    }
    return true;
}
