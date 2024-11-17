// AdvancedComputerPlayer.cc

#include "LevelFiveComputer.h"

#include <cassert>
#include <memory>
#include <utility>
#include <vector>

#include "BoardMove.h"
#include "ChessBoard.h"
#include "Cloneable.h"
#include "ComputerPlayer.h"
#include "Constants.h"


#pragma mark - ScoredAlphaBetaMove

/*
 * Static
 *
 * Used by alpha-beta algorithm 
 */
const LevelFiveComputer::ScoredAlphaBetaMove LevelFiveComputer::emptyScoredAlphaBetaMove(0, std::nullopt);

// Basic ctor
LevelFiveComputer::ScoredAlphaBetaMove::ScoredAlphaBetaMove(int alphaBetaScore, std::optional<std::unique_ptr<BoardMove>> const &boardMove) :
    alphaBetaScore(alphaBetaScore), boardMove(boardMove.has_value() ? std::make_optional<std::unique_ptr<BoardMove>>(boardMove.value()->clone()) : std::nullopt) { }

// Copy ctor
LevelFiveComputer::ScoredAlphaBetaMove::ScoredAlphaBetaMove(ScoredAlphaBetaMove const &other) :
    alphaBetaScore(other.alphaBetaScore), boardMove(other.boardMove.has_value() ? std::make_optional<std::unique_ptr<BoardMove>>(other.boardMove.value()->clone()) : std::nullopt) { }

// Move ctor
LevelFiveComputer::ScoredAlphaBetaMove::ScoredAlphaBetaMove(ScoredAlphaBetaMove &&other) noexcept :
    alphaBetaScore(other.alphaBetaScore), boardMove(std::move(other.boardMove)) {}

// Copy assignment
LevelFiveComputer::ScoredAlphaBetaMove& LevelFiveComputer::ScoredAlphaBetaMove::operator=(ScoredAlphaBetaMove const &other) {
    if (this != &other) {
        alphaBetaScore = other.alphaBetaScore;
        boardMove = other.boardMove.has_value() ? std::make_optional<std::unique_ptr<BoardMove>>(other.boardMove.value()->clone()) : std::nullopt;
    }
    return *this;
}

// Move assignment
LevelFiveComputer::ScoredAlphaBetaMove& LevelFiveComputer::ScoredAlphaBetaMove::operator=(ScoredAlphaBetaMove &&other) noexcept {
    if (this != &other) {
        alphaBetaScore = other.alphaBetaScore;
        boardMove = std::move(other.boardMove);
    }
    return *this;
}


#pragma mark - ScoredBoardMove

// Basic ctor
LevelFiveComputer::ScoredBoardMove::ScoredBoardMove(int score, std::unique_ptr<BoardMove> const &boardMove) :
    score(score), boardMove(boardMove->clone()) { }

// Copy ctor
LevelFiveComputer::ScoredBoardMove::ScoredBoardMove(ScoredBoardMove const &other) :
    score(other.score), boardMove(other.boardMove->clone()) { }

// Move ctor
LevelFiveComputer::ScoredBoardMove::ScoredBoardMove(ScoredBoardMove &&other) noexcept :
    score(other.score), boardMove(std::move(other.boardMove)) { }

// Copy assignment
LevelFiveComputer::ScoredBoardMove& LevelFiveComputer::ScoredBoardMove::operator=(ScoredBoardMove const &other) {
    if (this != &other) {
        score = other.score;
        boardMove = other.boardMove->clone();
    }
    return *this;
}

// Move assignment
LevelFiveComputer::ScoredBoardMove& LevelFiveComputer::ScoredBoardMove::operator=(ScoredBoardMove &&other) noexcept {
    if (this != &other) {
        score = other.score;
        boardMove = std::move(other.boardMove);
    }
    return *this;
}


#pragma mark - LevelFiveComputer

// Basic ctor
LevelFiveComputer::LevelFiveComputer(Team team) : 
    Cloneable<ComputerPlayer, LevelFiveComputer>(team) { }

// Copy ctor
LevelFiveComputer::LevelFiveComputer(LevelFiveComputer const &other) :
    Cloneable<ComputerPlayer, LevelFiveComputer>(other) { }

// Move ctor
LevelFiveComputer::LevelFiveComputer(LevelFiveComputer &&other) noexcept :
    Cloneable<ComputerPlayer, LevelFiveComputer>(std::move(other)) { }

// Copy assignment
LevelFiveComputer& LevelFiveComputer::operator=(LevelFiveComputer &other) {
    if (this != &other) {
        ComputerPlayer::operator=(other);
    }
    return *this;
}

// Move assignment
LevelFiveComputer& LevelFiveComputer::operator=(LevelFiveComputer &&other) noexcept {
    if (this != &other) {
        ComputerPlayer::operator=(std::move(other));
    }
    return *this;
}

/*
 * Generate a move
 */
std::unique_ptr<BoardMove> LevelFiveComputer::generateMoveImpl(std::unique_ptr<ChessBoard> const &chessBoard) const {
    std::unique_ptr<ChessBoard> tempChessBoard = chessBoard->clone();
    return getBestAlphaBetaMove(tempChessBoard, team, depth, -KING_SCORE, KING_SCORE).boardMove.value();
}

/*
 * Alpha-beta algorithm, with several personal additions
 */
LevelFiveComputer::ScoredAlphaBetaMove LevelFiveComputer::getBestAlphaBetaMove(std::unique_ptr<ChessBoard> &tempChessBoard, Team currentTeam, int currentDepth, int alpha, int beta) const {
    static int const positiveInfinity = std::numeric_limits<int>::max();
    static int const negativeInfinity = std::numeric_limits<int>::min();
    
    // End of recursion
    if (currentDepth == 0) {
        return tempChessBoard->isInStaleMate(currentTeam)
            ? emptyScoredAlphaBetaMove
            : ScoredAlphaBetaMove(getAlphaBetaBoardScore(tempChessBoard, currentTeam));
    }

    // Initial best score, try and beat it
    int bestScore = currentTeam == tempChessBoard->getTeamOne()
        ? negativeInfinity 
        : positiveInfinity;
 
    // Rank the moves before playing them out, speeds up alpha-beta
    std::vector<std::unique_ptr<BoardMove>> rankedMoves = generateRankedMoves(tempChessBoard, currentTeam);

    // Determine the best move
    std::unique_ptr<BoardMove> bestMove;
    if (currentTeam == tempChessBoard->getTeamOne()) {
        for (std::unique_ptr<BoardMove> const &rankedMove : rankedMoves) {
            tempChessBoard->makeMove(rankedMove);
            int currentScore = getBestAlphaBetaMove(tempChessBoard, tempChessBoard->getTeamTwo(), currentDepth - 1, alpha, beta).alphaBetaScore;
            tempChessBoard->undoMove();
            if (currentScore > bestScore) {
                bestScore = currentScore;
                bestMove = rankedMove->clone();
            }
            if (bestScore >= beta) {
                break;
            } else if (bestScore > alpha) {
                alpha = bestScore;
            }
        }
    } else {
        std::reverse(rankedMoves.begin(), rankedMoves.end());
        for (std::unique_ptr<BoardMove> const &rankedMove : rankedMoves) {
            tempChessBoard->makeMove(rankedMove);
            int currentScore = getBestAlphaBetaMove(tempChessBoard, tempChessBoard->getTeamOne(), currentDepth - 1, alpha, beta).alphaBetaScore;
            tempChessBoard->undoMove();    
            if (currentScore < bestScore) {
                bestScore = currentScore;
                bestMove = rankedMove->clone();
            }
            if (bestScore <= alpha) {
                break;
            } else if (bestScore < beta) {
                beta = bestScore;
            }
        }
    }

    // Did we find a move
    if (bestScore == positiveInfinity || bestScore == negativeInfinity) {
        return tempChessBoard->isInStaleMate(team)
            ? emptyScoredAlphaBetaMove
            : ScoredAlphaBetaMove(getAlphaBetaBoardScore(tempChessBoard, currentTeam));
    }

    // Return the best move
    return ScoredAlphaBetaMove(bestScore, std::make_optional<std::unique_ptr<BoardMove>>(std::move(bestMove)));
}

/*
 * Calculate the alpha-beta score for the Team argument
 * Applies advancement bonus to promote aggression
 */
int LevelFiveComputer::getAlphaBetaBoardScore(std::unique_ptr<ChessBoard> const &currentChessBoard, Team currentTeam) const {
    int totalScore = 0;

    // Standard score
    for (ChessBoard::BoardSquareIterator it = currentChessBoard->begin(); it != currentChessBoard->end(); ++it) {
        int numBoardRows = currentChessBoard->getNumRowsOnBoard();
        int numBoardCols = currentChessBoard->getNumColsOnBoard();

        // Check if there's a piece at the current BoardSquare
        if (!currentChessBoard->isSquareEmpty(*it)) {
            // Standard score of current Piece
            int pieceScore = currentChessBoard->getPieceInfoAt(*it).value().pieceScore * 10;

            // Advancement bonus, limited as to not induce pointless sacrifices
            int advancementBonus = 0;
            switch (currentChessBoard->getPieceDataAt(*it).value().pieceDirection) {
                case PieceDirection::NORTH:
                    advancementBonus = std::min(numBoardRows - 1 - (*it).boardRow, numBoardRows - 4);
                    break;
                case PieceDirection::SOUTH:
                    advancementBonus = std::min(numBoardRows, numBoardRows - 4);
                    break;
                case PieceDirection::EAST:
                    advancementBonus = std::min(numBoardCols - 1 - (*it).boardCol, numBoardCols - 4);
                    break;
                case PieceDirection::WEST:
                    advancementBonus = std::min(numBoardCols, numBoardCols - 4);
                    break;
                default:
                    assert(false);
            }
            
            // Total score of current piece, negative if Team two
            int totalPieceScore = pieceScore + advancementBonus;
            if (currentTeam == currentChessBoard->getTeamTwo()) {
                totalPieceScore *= -1;
            }

            // Add to total calculated alpha-beta score
            totalScore += totalPieceScore;
        }
    }

    // Checkmate
    if (currentChessBoard->isInCheckMate(currentTeam)) {
        if (currentTeam == currentChessBoard->getTeamTwo()) {
            totalScore += KING_SCORE;
        } else {
            totalScore -= KING_SCORE;
        }
    }

    // Return total calculated alpha-beta score
    return totalScore;
}

/*
 * Generate all legal and rank them, speeds up alpha-beta algorithm
 */
std::vector<std::unique_ptr<BoardMove>> LevelFiveComputer::generateRankedMoves(std::unique_ptr<ChessBoard> const &currentChessBoard, Team currentTeam) const {
    // All moves
    std::vector<std::unique_ptr<BoardMove>> moves = currentChessBoard->generateAllLegalMoves(currentTeam);

    // Assign a score to each move
    std::vector<ScoredBoardMove> scoredBoardMoves;
    for (std::unique_ptr<BoardMove> &move : moves) {
        int score = 0;
        std::optional<PieceInfo> capturedPieceInfo = currentChessBoard->getPieceInfoAt(move->getCaptureSquare());
        if (capturedPieceInfo.has_value()) {
            score += capturedPieceInfo.value().pieceScore;
        }
        scoredBoardMoves.emplace_back(ScoredBoardMove(score, std::move(move)));
    }

    // Sort moves by score in descending order
    std::sort(scoredBoardMoves.begin(), scoredBoardMoves.end(), [](ScoredBoardMove const &a, ScoredBoardMove const &b) {
        return a.score > b.score;
    });

    // Randomize order of moves with the same score
    std::vector<std::unique_ptr<BoardMove>> rankedBoardMoves;
    int scoreCurrentlyProcessing = scoredBoardMoves.front().score;
    std::vector<std::unique_ptr<BoardMove>> boardMovesWithCurrentScore;
    for (ScoredBoardMove &scoredBoardMove : scoredBoardMoves) {
        if (scoredBoardMove.score == scoreCurrentlyProcessing) {
            boardMovesWithCurrentScore.emplace_back(std::move(scoredBoardMove.boardMove));
        } else {
            shuffle(boardMovesWithCurrentScore);
            for (std::unique_ptr<BoardMove> &boardMoveWithCurrentScore : boardMovesWithCurrentScore) {
                rankedBoardMoves.emplace_back(std::move(boardMoveWithCurrentScore));
            }
            scoreCurrentlyProcessing = scoredBoardMove.score;
            boardMovesWithCurrentScore.clear();
            boardMovesWithCurrentScore.emplace_back(std::move(scoredBoardMove.boardMove));
        }
    }
    // Randomize last group of moves (those with the lowest score)
    shuffle(boardMovesWithCurrentScore);
    for (std::unique_ptr<BoardMove> &boardMoveWithCurrentScore : boardMovesWithCurrentScore) {
        rankedBoardMoves.emplace_back(std::move(boardMoveWithCurrentScore));
    }

    // Return the ranked moves
    return rankedBoardMoves;
}
