// AdvancedComputerPlayer.cc

#include <vector>
#include <cassert>
#include <limits>

#include "BoardSquare.h"
#include "Constants.h"
#include "LevelFiveComputer.h"


#pragma mark - ScoredAlphaBetaMove


// Static
const LevelFiveComputer::ScoredAlphaBetaMove LevelFiveComputer::emptyScoredAlphaBetaMove(0, std::nullopt);

// Basic ctor
LevelFiveComputer::ScoredAlphaBetaMove::ScoredAlphaBetaMove(int alphaBetaScore, std::optional<std::unique_ptr<BoardMove>> const &boardMove) :
    alphaBetaScore(alphaBetaScore), boardMove(boardMove.has_value() ? std::make_optional<std::unique_ptr<BoardMove>>(boardMove.value()->clone()) : std::nullopt) {}

// Copy ctor
LevelFiveComputer::ScoredAlphaBetaMove::ScoredAlphaBetaMove(ScoredAlphaBetaMove const &other) :
    alphaBetaScore(other.alphaBetaScore), boardMove(other.boardMove.has_value() ? std::make_optional<std::unique_ptr<BoardMove>>(other.boardMove.value()->clone()) : std::nullopt) {}

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

// MoveAssignment
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
    score(score), boardMove(boardMove->clone()) {}

// Copy ctor
LevelFiveComputer::ScoredBoardMove::ScoredBoardMove(ScoredBoardMove const &other) :
    score(other.score), boardMove(other.boardMove->clone()) {}

// Move ctor
LevelFiveComputer::ScoredBoardMove::ScoredBoardMove(ScoredBoardMove &&other) noexcept :
    score(other.score), boardMove(std::move(other.boardMove)) {}

// Copy assignment
LevelFiveComputer::ScoredBoardMove& LevelFiveComputer::ScoredBoardMove::operator=(ScoredBoardMove const &other) {
    if (this != &other) {
        score = other.score;
        boardMove = other.boardMove->clone();
    }
    return *this;
}

// MoveAssignment
LevelFiveComputer::ScoredBoardMove& LevelFiveComputer::ScoredBoardMove::operator=(ScoredBoardMove &&other) noexcept {
    if (this != &other) {
        score = other.score;
        boardMove = std::move(other.boardMove);
    }
    return *this;
}


#pragma mark - LevelFiveComputer

// Basic ctor
LevelFiveComputer::LevelFiveComputer(ChessBoard const &chessBoard, Team team) : 
    Cloneable<ComputerPlayer, LevelFiveComputer>(chessBoard, team) {}

// Copy ctor
LevelFiveComputer::LevelFiveComputer(LevelFiveComputer const &other) :
    Cloneable<ComputerPlayer, LevelFiveComputer>(other) {}

// Move ctor
LevelFiveComputer::LevelFiveComputer(LevelFiveComputer &&other) noexcept :
    Cloneable<ComputerPlayer, LevelFiveComputer>(std::move(other)) {}

std::unique_ptr<BoardMove> LevelFiveComputer::generateMoveImpl() const {
    return getBestAlphaBetaMove(*chessBoard.clone(), team, depth, -KingScore, KingScore).boardMove.value();
}

LevelFiveComputer::ScoredAlphaBetaMove LevelFiveComputer::getBestAlphaBetaMove(ChessBoard &tempChessBoard, Team currentTeam, int currentDepth, int alpha, int beta) const {
    static int const positiveInfinity = std::numeric_limits<int>::max();
    static int const negativeInfinity = std::numeric_limits<int>::min();
    
    if (currentDepth == 0) {
        return tempChessBoard.isInStaleMate(currentTeam)
            ? emptyScoredAlphaBetaMove
            : ScoredAlphaBetaMove(getAlphaBetaBoardScore(tempChessBoard, currentTeam));
    }

    int bestScore = currentTeam == tempChessBoard.getTeamOne()
        ? negativeInfinity 
        : positiveInfinity;
        
    std::unique_ptr<BoardMove> bestMove;
    std::vector<std::unique_ptr<BoardMove>> rankedMoves = generateRankedMoves(tempChessBoard, currentTeam);

    if (currentTeam == tempChessBoard.getTeamOne()) {
        for (std::unique_ptr<BoardMove> const &rankedMove : rankedMoves) {
            tempChessBoard.makeMove(rankedMove);
            int currentScore = getBestAlphaBetaMove(tempChessBoard, tempChessBoard.getTeamTwo(), currentDepth - 1, alpha, beta).alphaBetaScore;
            tempChessBoard.undoMove();
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
        std::reverse(rankedMoves.begin(), rankedMoves.end());   // Want moves from bottom of board first (alpha beta optimization)
        for (std::unique_ptr<BoardMove> const &rankedMove : rankedMoves) {
            tempChessBoard.makeMove(rankedMove);
            int currentScore = getBestAlphaBetaMove(tempChessBoard, tempChessBoard.getTeamOne(), currentDepth - 1, alpha, beta).alphaBetaScore;
            tempChessBoard.undoMove();    
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

    if (bestScore == positiveInfinity || bestScore == negativeInfinity) {
        return tempChessBoard.isInStaleMate(team)
            ? emptyScoredAlphaBetaMove
            : ScoredAlphaBetaMove(getAlphaBetaBoardScore(tempChessBoard, currentTeam));
    }

    return ScoredAlphaBetaMove(bestScore, std::make_optional<std::unique_ptr<BoardMove>>(std::move(bestMove)));
}

int LevelFiveComputer::getAlphaBetaBoardScore(ChessBoard const &currentChessBoard, Team currentTeam) const {
    int totalScore = 0;

    // Standard score
    for (ChessBoard::BoardSquareIterator it = chessBoard.begin(); it != chessBoard.end(); ++it) {
        int numBoardRows = chessBoard.getNumRows();
        int numBoardCols = chessBoard.getNumCols();

        if (!chessBoard.isSquareEmpty(*it)) {
            int pieceScore = chessBoard.getPieceInfoAt(*it).value().pieceScore * 10;

            // Advancement bonus
            int advancementBonus = 0;
            switch (chessBoard.getPieceDataAt(*it).value().pieceDirection) {
                case PieceDirection::NORTH:
                    advancementBonus = min(numBoardRows - 1 - (*it).boardRow, numBoardRows - 4);
                    break;
                case PieceDirection::SOUTH:
                    advancementBonus = min(numBoardRows, numBoardRows - 4);
                    break;
                case PieceDirection::EAST:
                    advancementBonus = min(numBoardCols - 1 - (*it).boardCol, numBoardCols - 4);
                    break;
                case PieceDirection::WEST:
                    advancementBonus = min(numBoardCols, numBoardCols - 4);
                    break;
                default:
                    assert(false);
            }
            
            totalScore = pieceScore + advancementBonus;
            if (currentTeam == chessBoard.getTeamTwo()) {
                totalScore *= -1;
            }
        }
    }

    // Checkmate
    if (chessBoard.isInCheckMate(currentTeam)) {
        if (currentTeam == chessBoard.getTeamTwo()) {
            totalScore += KingScore;
        } else {
            totalScore -= KingScore;
        }
    }

    return totalScore;
}

std::vector<std::unique_ptr<BoardMove>> LevelFiveComputer::generateRankedMoves(ChessBoard const &currentChessBoard, Team currentTeam) const {
    std::vector<std::unique_ptr<BoardMove>> moves = currentChessBoard.generateAllLegalMoves(currentTeam);

    // Assign values to each move
    std::vector<ScoredBoardMove> scoredBoardMoves;
    for (std::unique_ptr<BoardMove> &move : moves) {
        int score = 0;
        std::optional<PieceInfo> capturedPieceInfo = chessBoard.getPieceInfoAt(move->getCaptureSquare());
        if (capturedPieceInfo.has_value()) {
            score += capturedPieceInfo.value().pieceScore;
        }
        scoredBoardMoves.emplace_back(ScoredBoardMove(score, std::move(move)));
    }

    // Sort moves by score in descending order
    std::sort(scoredBoardMoves.begin(), scoredBoardMoves.end(), [](ScoredBoardMove const &a, ScoredBoardMove const &b) {
        return a.score > b.score;
    });

    std::vector<std::unique_ptr<BoardMove>> rankedBoardMoves;

    // Randomize order of moves with the same score
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

    return rankedBoardMoves;
}
