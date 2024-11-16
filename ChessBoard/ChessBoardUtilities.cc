// ChessBoardUtilities.cc

#include <memory>

#include "ChessBoardUtilities.h"
#include "ChessBoard.h"
#include "PieceData.h"
#include "Piece.h"


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

    // Stalemate
    if (chessBoard->isInStaleMate(chessBoard->getTeamOne()) || chessBoard->isInStaleMate(chessBoard->getTeamTwo())) {
        return false;
    }

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

// Standard chess setup
// False if can't be applied with current board size
// Centred if more than backrow num col
bool ChessBoardUtilities::applyStandardSetup(std::unique_ptr<ChessBoard> &chessBoard, PieceLevel pieceLevel) {
    static std::vector<PieceType> const standardBackrowSetupOrder = {
        PieceType::ROOK,
        PieceType::KNIGHT,
        PieceType::BISHOP,
        PieceType::QUEEN,
        PieceType::KING,
        PieceType::BISHOP,
        PieceType::KNIGHT,
        PieceType::ROOK
    };

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
        Team teamOne = chessBoard->getTeamOne();
        chessBoard->setPosition(BoardSquare(bottomRow, currentBoardCol), PieceData(currentPieceType, pieceLevel, teamOne, PieceDirection::NORTH, false));
        chessBoard->setPosition(BoardSquare(bottomRow - 1, currentBoardCol), PieceData(PieceType::PAWN, pieceLevel, teamOne, PieceDirection::NORTH, false));

        // Team Two
        Team teamTwo = chessBoard->getTeamTwo();
        chessBoard->setPosition(BoardSquare(topRow, currentBoardCol), PieceData(currentPieceType, pieceLevel, teamTwo, PieceDirection::SOUTH, false));
        chessBoard->setPosition(BoardSquare(topRow + 1, currentBoardCol), PieceData(PieceType::PAWN, pieceLevel, teamTwo, PieceDirection::SOUTH, false));
    }
    return true;
}

bool ChessBoardUtilities::isGameOver(std::unique_ptr<ChessBoard> const &chessBoard) {
    Team teamOne = chessBoard->getTeamOne();
    Team teamTwo = chessBoard->getTeamTwo();
    return 
        chessBoard->isInCheckMate(teamOne) || 
        chessBoard->isInCheckMate(teamTwo) || 
        chessBoard->isInStaleMate(teamOne) || 
        chessBoard->isInStaleMate(teamTwo);
}

int ChessBoardUtilities::getNumPiecesOnBoard(std::unique_ptr<ChessBoard> const &chessBoard, Team team) {
    int numPieces = 0;
    for (ChessBoard::BoardSquareIterator it = chessBoard->begin(); it != chessBoard->end(); ++it) {
        std::optional<PieceData> pieceData = chessBoard->getPieceDataAt(*it);
        if (pieceData.has_value() && pieceData.value().team == team) {
            numPieces++;
        }
    }
    return numPieces;
}
