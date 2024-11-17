// LevelFiveComputer.h

#ifndef LevelFiveComputer_h
#define LevelFiveComputer_h

#include <memory>
#include <optional>
#include <utility>
#include <vector>

#include "BoardMove.h"
#include "Cloneable.h"
#include "ComputerPlayer.h"
#include "Constants.h"


/**
 * LevelFiveComputer ComputerPlayer Class
 */
class LevelFiveComputer final : public Cloneable<ComputerPlayer, LevelFiveComputer> {
private:

    /**
     * ScoredAlphaBetaMove Struct
     * Used by alpha-beta algorithm when determining best possible move
     */
    struct ScoredAlphaBetaMove final {
        int alphaBetaScore;
        std::optional<std::unique_ptr<BoardMove>> boardMove;

        explicit ScoredAlphaBetaMove(int alphaBetaScore, std::optional<std::unique_ptr<BoardMove>> const &boardMove = std::nullopt);
        ScoredAlphaBetaMove(ScoredAlphaBetaMove const &other);
        ScoredAlphaBetaMove(ScoredAlphaBetaMove &&other) noexcept;  
        ScoredAlphaBetaMove& operator=(ScoredAlphaBetaMove const &other);
        ScoredAlphaBetaMove& operator=(ScoredAlphaBetaMove &&other) noexcept;
        virtual ~ScoredAlphaBetaMove() = default;
    };
    static ScoredAlphaBetaMove const emptyScoredAlphaBetaMove;

    /**
     * ScoredBoardMove Struct
     * Used when ranking BoardMoves as part of alpha-beta algorithm
     */
    struct ScoredBoardMove final {
        int score;
        std::unique_ptr<BoardMove> boardMove;

        explicit ScoredBoardMove(int score, std::unique_ptr<BoardMove> const &boardMove);
        ScoredBoardMove(ScoredBoardMove const &other);
        ScoredBoardMove(ScoredBoardMove &&other) noexcept;  
        ScoredBoardMove& operator=(ScoredBoardMove const &other);
        ScoredBoardMove& operator=(ScoredBoardMove &&other) noexcept;
        virtual ~ScoredBoardMove() = default;
    };

    static int const depth = 4;
    std::unique_ptr<BoardMove> generateMoveImpl(std::unique_ptr<ChessBoard> const &chessBoard) const override;

    ScoredAlphaBetaMove getBestAlphaBetaMove(std::unique_ptr<ChessBoard> &tempChessBoard, Team currentTeam, int currentDepth, int alpha, int beta) const;
    int getAlphaBetaBoardScore(std::unique_ptr<ChessBoard> const &currentChessBoard, Team currentTeam) const;
    std::vector<std::unique_ptr<BoardMove>> generateRankedMoves(std::unique_ptr<ChessBoard> const &currentChessBoard, Team currentTeam) const;

public:
    explicit LevelFiveComputer(Team team);
    LevelFiveComputer(LevelFiveComputer const &other);
    LevelFiveComputer(LevelFiveComputer &&other) noexcept;
    LevelFiveComputer& operator=(LevelFiveComputer &other);
    LevelFiveComputer& operator=(LevelFiveComputer &&other) noexcept;
    virtual ~LevelFiveComputer() = default;
};


#endif /* LevelFiveComputer_h */
