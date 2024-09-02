// AdvancedComputerPlayer.cc

#include <random>
#include <vector>
#include <tuple>
#include <algorithm>
#include <optional>

#include "AdvancedComputerPlayer.h"
#include "MoveShuffler.h"
#include "PieceInfo.h"


BoardMove AdvancedComputerPlayer::getMoveImplementation(ChessBoard &board, Team team) const {
    return alphaBetaSearch(board, depth, team, -1000, 1000).boardMove.value();
}

AdvancedComputerPlayer::ScoredBoardMove AdvancedComputerPlayer::alphaBetaSearch(ChessBoard &board, int currentDepth, Team team, int alpha, int beta) const {

    if (currentDepth == 0) {
        if (board.isInStaleMate(team)) {
            return ScoredBoardMove(0);
        }
        return ScoredBoardMove(getAlphaBetaBoardScore(board, team));
    }

    int bestScore = (team == board.getTeamOne()) ? -10000 : 10000;
    std::optional<BoardMove> bestMove;
    std::vector<BoardMove> allMoves = board.getLegalMoves(team);
    allMoves = rankMoves(board, allMoves);
    if (team == board.getTeamOne()) {
        for (BoardMove const &move : allMoves) {
            board.makeMove(move);
            int currentScore = alphaBetaSearch(board, currentDepth - 1, board.getOtherTeam(team), alpha, beta).score;
            board.undoMove();   
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
        for (BoardMove const &move : allMoves) {
            board.makeMove(move);
            int currentScore = alphaBetaSearch(board, currentDepth - 1, board.getOtherTeam(team), alpha, beta).score;
            board.undoMove();    
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
        if (board.isInStaleMate(team)) {
            return ScoredBoardMove(0);
        }
        return ScoredBoardMove(getAlphaBetaBoardScore(board, team));
    }

    return ScoredBoardMove(bestScore, bestMove);
}

std::vector<BoardMove> AdvancedComputerPlayer::rankMoves(ChessBoard& board, std::vector<BoardMove> const &moves) const {
    std::vector<ScoredBoardMove> scoredBoardMoves;

    // Assign values to each move
    for (BoardMove const &move : moves) {
        int score = 0;
        std::optional<PieceInfo> pieceInfo = board.getPieceInfoAt(move.getCaptureSquare());
        if (pieceInfo.has_value()) {
            score += pieceInfo.value().getPieceScore();
        }
        scoredBoardMoves.emplace_back(ScoredBoardMove(score, move));
    }

    // Sort moves by score in descending order
    std::sort(scoredBoardMoves.begin(), scoredBoardMoves.end(), [](const ScoredBoardMove& a, const ScoredBoardMove& b) {
        return a.score > b.score;
    });

    // Randomize moves with the same score
    std::vector<BoardMove> finalOrder;
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

int AdvancedComputerPlayer::getAlphaBetaBoardScore(ChessBoard& board, Team team) const {
    int totalScore = 0;

    for (BoardSquare const &boardSquare : board.allBoardSquares()) {
        int numBoardRows = board.getNumRows();
        int numBoardCols = board.getNumCols();


        std::optional<PieceInfo> pieceInfo = board.getPieceInfoAt(boardSquare);
        if (pieceInfo.has_value()) {
            if (pieceInfo.value().getTeam() == board.getTeamOne()) {
                totalScore += pieceInfo.value().getPieceScore() * 10;
                // Advance bonus, only until row before pawns so no stupid sacrifice
                switch (pieceInfo.value().getPieceDirection()) {
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
                        break;
                }
            } else if (pieceInfo.value().getTeam() == board.getTeamTwo()) {
                totalScore -= pieceInfo.value().getPieceScore() * 10;
                // Advance bonus, only until row before pawns so no stupid sacrifice
                switch (pieceInfo.value().getPieceDirection()) {
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
                        break;
                }
            }
        }

        
    }

    // Checkmate
    if (board.isInCheckMate(team)) {
        if (team == board.getTeamTwo()) {
            totalScore += 1000;
        } else {
            totalScore -= 1000;
        }
    }

    return totalScore;
}
