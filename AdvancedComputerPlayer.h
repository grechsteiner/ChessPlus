// AdvancedComputerPlayer.h

#ifndef AdvancedComputerPlayer_h
#define AdvancedComputerPlayer_h

#include <utility>
#include <optional>

#include "ComputerPlayer.h"
#include "Constants.h"
#include "Board.h"



class AdvancedComputerPlayer : public ComputerPlayer {
private:
    int getAlphaBetaBoardScore(ChessBoard& board, Team team) const;
    std::vector<BoardMove> rankMoves(ChessBoard& board, std::vector<BoardMove> const &moves) const;
    BoardMove getMoveImplementation(ChessBoard &board, Team team) const override;
    int depth = 4;


    struct ScoredBoardMove {
        int score;
        std::optional<BoardMove> boardMove;

        ScoredBoardMove(int score, std::optional<BoardMove> boardMove = std::nullopt) : score(score), boardMove(boardMove) {}
    };

    ScoredBoardMove alphaBetaSearch(ChessBoard &board, int currentDepth, Team team, int alpha, int beta) const;
public:
    AdvancedComputerPlayer() = default;
};


#endif /* AdvancedComputerPlayer_h */
