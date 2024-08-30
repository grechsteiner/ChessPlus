// AdvancedComputerPlayer.cc

#include <random>
#include <vector>
#include <tuple>
#include <algorithm>

#include "AdvancedComputerPlayer.h"
#include "MoveShuffler.h"


BoardMove AdvancedComputerPlayer::getMoveImplementation(ChessBoard &board, Team team) const {
    return std::get<1>(alphaBetaSearch(board, depth, team, 1000, -1000));
}

std::tuple<int, BoardMove> AdvancedComputerPlayer::alphaBetaSearch(ChessBoard &board, int currentDepth, Team team, int beta, int alpha) const {

    if (currentDepth == 0) {
        if (board.isInStaleMate(team)) {
            return std::make_tuple(0, BoardMove::DEFAULT);
        }
        return std::make_tuple(getAlphaBetaBoardScore(board, team), BoardMove::DEFAULT);
    }

    int bestScore = (team == board.getTeamOne()) ? -10000 : 10000;
    BoardMove bestMove = BoardMove::DEFAULT;
    std::vector<BoardMove> allMoves = board.getLegalMoves(team);
    allMoves = rank_moves(board, allMoves);
    if (team == board.getTeamOne()) {
        for (BoardMove const &move : allMoves) {
            board.makeMove(move);
            int currentScore = std::get<0>(alphaBetaSearch(board, currentDepth - 1, board.getOtherTeam(team), beta, alpha));
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
            int currentScore = std::get<0>(alphaBetaSearch(board, currentDepth - 1, board.getOtherTeam(team), beta, alpha));
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
            return std::make_tuple(0, BoardMove::DEFAULT);
        }
        return std::make_tuple(getAlphaBetaBoardScore(board, team), BoardMove::DEFAULT);
    }

    return std::make_tuple(bestScore, bestMove);
}

struct ScoredMove {
    BoardMove move;
    int score;

    ScoredMove(const BoardMove& m, int s) : move(m), score(s) {}
};

std::vector<BoardMove> AdvancedComputerPlayer::rank_moves(ChessBoard& board, const std::vector<BoardMove>& moves) const {
    std::vector<ScoredMove> scored_moves;

    // Assign values to each move
    for (const auto& move : moves) {
        int score = 0;
        score += board.getPieceInfoAt(move.getCaptureSquare()).pieceScore;
        scored_moves.emplace_back(move, score);
    }

    // Sort moves by score in descending order
    std::sort(scored_moves.begin(), scored_moves.end(), [](const ScoredMove& a, const ScoredMove& b) {
        return a.score > b.score;
    });

    // Randomize moves with the same score
    std::vector<BoardMove> final_list;
    int current_value = scored_moves[0].score;
    std::vector<ScoredMove> temp_list;

    std::random_device rd;
    std::mt19937 g(rd());

    for (const auto& scored_move : scored_moves) {
        if (scored_move.score != current_value) {
            std::shuffle(temp_list.begin(), temp_list.end(), g);
            for (const auto& temp_move : temp_list) {
                final_list.push_back(temp_move.move);
            }

            current_value = scored_move.score;
            temp_list.clear();
        }
        temp_list.push_back(scored_move);
    }

    // Shuffle and add the last set of moves
    std::shuffle(temp_list.begin(), temp_list.end(), g);
    for (const auto& temp_move : temp_list) {
        final_list.push_back(temp_move.move);
    }

    return final_list;
}

int AdvancedComputerPlayer::getAlphaBetaBoardScore(ChessBoard& board, Team team) const {
    int totalScore = 0;

    for (BoardSquare const &boardSquare : board.allBoardSquares()) {
        int numBoardRows = board.getNumRows();
        int numBoardCols = board.getNumCols();


        if (board.getPieceInfoAt(boardSquare).team == board.getTeamOne()) {
            totalScore += board.getPieceInfoAt(boardSquare).pieceScore * 10;
            // Advance bonus, only until row before pawns so no stupid sacrifice
            switch (board.getPieceInfoAt(boardSquare).pieceDirection) {
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
        } else if (board.getPieceInfoAt(boardSquare).team == board.getTeamTwo()) {
            totalScore -= board.getPieceInfoAt(boardSquare).pieceScore * 10;
            // Advance bonus, only until row before pawns so no stupid sacrifice
            switch (board.getPieceInfoAt(boardSquare).pieceDirection) {
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
