// LevelFiveComputer.h

#ifndef LevelFiveComputer_h
#define LevelFiveComputer_h

#include <utility>
#include <optional>

#include "BoardMove.h"
#include "ComputerPlayer.h"
#include "Cloneable.h"


class LevelFiveComputer final : public Cloneable<ComputerPlayer, LevelFiveComputer> {
private:
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
    std::unique_ptr<BoardMove> generateMoveImpl() const override;

    ScoredAlphaBetaMove getBestAlphaBetaMove(ChessBoard &tempChessBoard, Team currentTeam, int currentDepth, int alpha, int beta) const;
    int getAlphaBetaBoardScore(ChessBoard const &currentChessBoard, Team currentTeam) const;
    std::vector<std::unique_ptr<BoardMove>> generateRankedMoves(ChessBoard const &currentChessBoard, Team currentTeam) const;

public:
    explicit LevelFiveComputer(ChessBoard const &chessBoard, Team team);
    LevelFiveComputer(LevelFiveComputer const &other);
    LevelFiveComputer(LevelFiveComputer &&other) noexcept;
    // Copy and move assignment disabled
    virtual ~LevelFiveComputer() = default;
};


#endif /* LevelFiveComputer_h */
