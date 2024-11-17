// ChessBoardUtilities.cc

#include "ChessBoardUtilities.h"

#include <memory>
#include <optional>

#include "ChessBoard.h"
#include "Constants.h"
#include "PieceData.h"


/*
 * True if ChessBoard argument is in a legal setup state, false otherwise
 * Legal setup state:
 * - 1 King per team
 * - No team in checkmate or stalemate
 * - No pawns in a location where they should be promoted
 */
bool ChessBoardUtilities::isBoardInLegalSetupState(std::unique_ptr<ChessBoard> const &chessBoard) {
    int topRow = 0;
    int bottomRow = chessBoard->getNumRowsOnBoard() - 1;
    int leftCol = 0;
    int rightCol = chessBoard->getNumColsOnBoard() - 1;

    int teamOneKingCount = 0;
    int teamTwoKingCount = 0;

    // Check for stalemate
    if (chessBoard->isInStaleMate(chessBoard->getTeamOne()) || chessBoard->isInStaleMate(chessBoard->getTeamTwo())) {
        return false;
    }

    // Check for checkmate, king count, pawn location
    for (ChessBoard::BoardSquareIterator it = chessBoard->begin(); it != chessBoard->end(); ++it) {
        std::optional<PieceData> pieceData = chessBoard->getPieceDataAt(*it);

        if (pieceData.has_value()) {
            PieceType pieceType = pieceData.value().pieceType;
            Team team = pieceData.value().team;
            PieceDirection pieceDirection = pieceData.value().pieceDirection;

            if (pieceType == PieceType::KING) {
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
                int boardRow = (*it).boardRow;
                int boardCol = (*it).boardCol;

                // Pawn position
                if ((pieceDirection == PieceDirection::NORTH && boardRow == topRow) ||
                    (pieceDirection == PieceDirection::SOUTH && boardRow == bottomRow) ||
                    (pieceDirection == PieceDirection::EAST && boardCol == leftCol) ||
                    (pieceDirection == PieceDirection::WEST && boardCol == rightCol)) {

                    return false;
                }
            }
        }
    }

    return teamOneKingCount == 1 && teamTwoKingCount == 1;
}

/*
 * Apply the standard setup to the ChessBoard argument
 * False if ChessBoard argument is too small for the standard setup, true otherwise
 */
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

    if (chessBoard->getNumRowsOnBoard() < 4 || chessBoard->getNumColsOnBoard() < standardBackrowSetupOrder.size()) {
        return false;
    }

    int topRow = 0;
    int bottomRow = chessBoard->getNumRowsOnBoard() - 1;
    int firstPieceCol = (chessBoard->getNumColsOnBoard() - 8) / 2;
    chessBoard->clearBoard();
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

/*
 * True if the game is over when it is the Team arguments turn
 */
bool ChessBoardUtilities::isGameOver(std::unique_ptr<ChessBoard> const &chessBoard, Team currentTurn) {
    return 
        chessBoard->isInCheckMate(currentTurn) || 
        chessBoard->isInStaleMate(currentTurn);
}

/*
 * Return the number of Pieces that are on the Team arguments team
 */
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
