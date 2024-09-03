// AdvancedComputerPlayer.h

#ifndef AdvancedComputerPlayer_h
#define AdvancedComputerPlayer_h

#include <utility>
#include <optional>

#include "ComputerPlayer.h"
#include "Constants.h"
#include "IChessBoard.h"



class AdvancedComputerPlayer : public ComputerPlayer {
private:
    int getAlphaBetaBoardScore(IChessBoard& chessBoard, Team team) const;
    std::vector<BoardMove> rankMoves(IChessBoard& chessBoard, std::vector<BoardMove> const &moves) const;
    BoardMove getMoveImplementation(IChessBoard &chessBoard, Team team) const override;
    int depth = 4;


    struct ScoredBoardMove {
        int score;
        std::optional<BoardMove> boardMove;

        ScoredBoardMove(int score, std::optional<BoardMove> boardMove = std::nullopt) : score(score), boardMove(boardMove) {}
    };

    ScoredBoardMove alphaBetaSearch(IChessBoard &chessBoard, int currentDepth, Team team, int alpha, int beta) const;
public:
    AdvancedComputerPlayer() = default;
};


#endif /* AdvancedComputerPlayer_h */
