// AdvancedComputerPlayer.cc

#include <random>
#include <vector>
#include <tuple>
#include <algorithm>
#include <optional>
#include <memory>
#include <cassert>

#include "AdvancedComputerPlayer.h"
#include "MoveShuffler.h"
#include "PieceInfo.h"


OldBoardMove AdvancedComputerPlayer::getMoveImpl(ChessBoard const &chessBoard, Team team) const {
    std::unique_ptr<ChessBoard> tempChessBoard = chessBoard.clone();
    return alphaBetaSearch(*tempChessBoard, depth, team, -1000, 1000).boardMove.value();
}

ScoredBoardMove AdvancedComputerPlayer::alphaBetaSearch(ChessBoard &chessBoard, int currentDepth, Team team, int alpha, int beta) const {

    if (currentDepth == 0) {
        if (chessBoard.isInStaleMate(team)) {
            return ScoredBoardMove(0);
        }
        return ScoredBoardMove(getAlphaBetaBoardScore(chessBoard, team));
    }

    int bestScore = (team == chessBoard.getTeamOne()) ? -10000 : 10000;
    std::optional<OldBoardMove> bestMove;
    std::vector<OldBoardMove> allMoves = chessBoard.generateAllLegalMoves(team);
    allMoves = rankMoves(chessBoard, allMoves);
    if (team == chessBoard.getTeamOne()) {
        for (OldBoardMove const &move : allMoves) {
            chessBoard.makeMove(move);
            int currentScore = alphaBetaSearch(chessBoard, currentDepth - 1, chessBoard.getTeamTwo(), alpha, beta).score;
            chessBoard.undoMove();   
            if (currentScore > bestScore) {
                bestScore = currentScore;
                bestMove = move;
            }
            if (bestScore >= beta) {
                break;
            } else if (bestScore > alpha) {
                alpha = bestScore;
            }
        }

    } else {
        for (OldBoardMove const &move : allMoves) {
            chessBoard.makeMove(move);
            int currentScore = alphaBetaSearch(chessBoard, currentDepth - 1, chessBoard.getTeamOne(), alpha, beta).score;
            chessBoard.undoMove();    
            if (currentScore < bestScore) {
                bestScore = currentScore;
                bestMove = move;
            }
            if (bestScore <= alpha) {
                break;
            } else if (bestScore < beta) {
                beta = bestScore;
            }
            
        }
    }

    if (bestScore == 10000 || bestScore == -10000) {
        if (chessBoard.isInStaleMate(team)) {
            return ScoredBoardMove(0);
        }
        return ScoredBoardMove(getAlphaBetaBoardScore(chessBoard, team));
    }

    return ScoredBoardMove(bestScore, bestMove);
}

std::vector<OldBoardMove> AdvancedComputerPlayer::rankMoves(ChessBoard const &chessBoard, std::vector<OldBoardMove> const &moves) const {
    std::vector<ScoredBoardMove> scoredBoardMoves;

    // Assign values to each move
    for (OldBoardMove const &move : moves) {
        int score = 0;
        std::optional<PieceInfo> pieceInfo = chessBoard.getPieceInfoAt(move.getCaptureSquare());
        if (pieceInfo.has_value()) {
            score += pieceInfo.value().pieceScore;
        }
        scoredBoardMoves.emplace_back(ScoredBoardMove(score, move));
    }

    // Sort moves by score in descending order
    std::sort(scoredBoardMoves.begin(), scoredBoardMoves.end(), [](const ScoredBoardMove& a, const ScoredBoardMove& b) {
        return a.score > b.score;
    });

    // Randomize moves with the same score
    std::vector<OldBoardMove> finalOrder;
    int currentValue = scoredBoardMoves[0].score;
    std::vector<ScoredBoardMove> tempOrder;

    std::random_device rd;
    std::mt19937 g(rd());

    for (ScoredBoardMove const &scoredBoardMove : scoredBoardMoves) {
        if (scoredBoardMove.score != currentValue) {
            std::shuffle(tempOrder.begin(), tempOrder.end(), g);
            for (ScoredBoardMove const &tempScoredBoardMove : tempOrder) {
                finalOrder.push_back(tempScoredBoardMove.boardMove.value());
            }

            currentValue = scoredBoardMove.score;
            tempOrder.clear();
        }
        tempOrder.push_back(scoredBoardMove);
    }

    // Shuffle and add the last set of moves
    std::shuffle(tempOrder.begin(), tempOrder.end(), g);
    for (ScoredBoardMove const &tempScoredBoardMove : tempOrder) {
        finalOrder.push_back(tempScoredBoardMove.boardMove.value());
    }

    return finalOrder;
}

int AdvancedComputerPlayer::getAlphaBetaBoardScore(ChessBoard const &chessBoard, Team team) const {
    int totalScore = 0;

    for (BoardSquare const &boardSquare : chessBoard.getAllBoardSquares()) {
        int numBoardRows = chessBoard.getNumRows();
        int numBoardCols = chessBoard.getNumCols();


        std::optional<PieceInfo> pieceInfo = chessBoard.getPieceInfoAt(boardSquare);
        if (pieceInfo.has_value()) {
            if (pieceInfo.value().pieceData.team == chessBoard.getTeamOne()) {
                totalScore += pieceInfo.value().pieceScore * 10;
                // Advance bonus, only until row before pawns so no stupid sacrifice
                switch (pieceInfo.value().pieceData.pieceDirection) {
                    case PieceDirection::NORTH:
                        totalScore += min(numBoardRows - 1 - boardSquare.getBoardRow(), numBoardRows - 4);
                        break;
                    case PieceDirection::SOUTH:
                        totalScore += min(numBoardRows, numBoardRows - 4);
                        break;
                    case PieceDirection::EAST:
                        totalScore += min(numBoardCols - 1 - boardSquare.getBoardCol(), numBoardCols - 4);
                        break;
                    case PieceDirection::WEST:
                        totalScore += min(numBoardCols, numBoardCols - 4);
                        break;
                    default:
                        assert(false);
                }
            } else if (pieceInfo.value().pieceData.team == chessBoard.getTeamTwo()) {
                totalScore -= pieceInfo.value().pieceScore * 10;
                // Advance bonus, only until row before pawns so no stupid sacrifice
                switch (pieceInfo.value().pieceData.pieceDirection) {
                    case PieceDirection::NORTH:
                        totalScore -= min(numBoardRows - 1 - boardSquare.getBoardRow(), numBoardRows - 4);
                        break;
                    case PieceDirection::SOUTH:
                        totalScore -= min(numBoardRows, numBoardRows - 4);
                        break;
                    case PieceDirection::EAST:
                        totalScore -= min(numBoardCols - 1 - boardSquare.getBoardCol(), numBoardCols - 4);
                        break;
                    case PieceDirection::WEST:
                        totalScore -= min(numBoardCols, numBoardCols - 4);
                        break;
                    default:
                        assert(false);
                }
            }
        }

        
    }

    // Checkmate
    if (chessBoard.isInCheckMate(team)) {
        if (team == chessBoard.getTeamTwo()) {
            totalScore += 1000;
        } else {
            totalScore -= 1000;
        }
    }

    return totalScore;
}
