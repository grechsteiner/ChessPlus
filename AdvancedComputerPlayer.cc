// AdvancedComputerPlayer.cc

#include <random>
#include <vector>
#include <tuple>
#include <algorithm>

#include "AdvancedComputerPlayer.h"
#include "MoveShuffler.h"


Move AdvancedComputerPlayer::getMoveImplementation(Board &board, Color color) const {
    return std::get<1>(alphaBetaSearch(board, depth, color, 1000, -1000));
}

std::tuple<int, Move> AdvancedComputerPlayer::alphaBetaSearch(Board &board, int currentDepth, Color color, int beta, int alpha) const {

    if (currentDepth == 0) {
        if (board.isInStaleMate(color)) {
            return std::make_tuple(0, Move::DEFAULT);
        }
        return std::make_tuple(board.getAlphaBetaBoardScore(color), Move::DEFAULT);
    }

    int bestScore = (color == board.getColorOne()) ? -10000 : 10000;
    Move bestMove = Move::DEFAULT;
    std::vector<Move> allMoves = board.getLegalMoves(color);
    allMoves = rank_moves(board, allMoves);
    if (color == board.getColorOne()) {
        for (Move const &move : allMoves) {
            board.makeMove(move);
            int currentScore = std::get<0>(alphaBetaSearch(board, currentDepth - 1, board.oppositeColor(color), beta, alpha));
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
        for (Move const &move : allMoves) {
            board.makeMove(move);
            int currentScore = std::get<0>(alphaBetaSearch(board, currentDepth - 1, board.oppositeColor(color), beta, alpha));
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
        if (board.isInStaleMate(color)) {
            return std::make_tuple(0, Move::DEFAULT);
        }
        return std::make_tuple(board.getAlphaBetaBoardScore(color), Move::DEFAULT);
    }

    return std::make_tuple(bestScore, bestMove);
}

struct ScoredMove {
    Move move;
    int score;

    ScoredMove(const Move& m, int s) : move(m), score(s) {}
};

std::vector<Move> AdvancedComputerPlayer::rank_moves(Board& board, const std::vector<Move>& moves) const {
    std::vector<ScoredMove> scored_moves;

    // Assign values to each move
    for (const auto& move : moves) {
        int score = 0;

        CompletedMove completed(move, board.getGrid());
        int capturedRow = completed.getVectorRow(board.getGrid().size(), completed.getCapturedRow());
        int capturedCol = completed.getVectorCol(completed.getCapturedCol());
        score += board.getPieceAt(capturedRow, capturedCol)->getPieceScore();

        
        scored_moves.emplace_back(move, score);
    }

    // Sort moves by score in descending order
    std::sort(scored_moves.begin(), scored_moves.end(), [](const ScoredMove& a, const ScoredMove& b) {
        return a.score > b.score;
    });

    // Randomize moves with the same score
    std::vector<Move> final_list;
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
