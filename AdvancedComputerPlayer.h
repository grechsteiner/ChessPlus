// AdvancedComputerPlayer.h

#ifndef AdvancedComputerPlayer_h
#define AdvancedComputerPlayer_h

#include <utility>
#include <optional>

#include "ComputerPlayer.h"
#include "Constants.h"
#include "IChessBoard.h"

struct ScoredBoardMove {
    int score;
    std::optional<BoardMove> boardMove;

    ScoredBoardMove(int score, std::optional<BoardMove> boardMove = std::nullopt) : score(score), boardMove(boardMove) {}
};

class AdvancedComputerPlayer : public ComputerPlayer {
private:
    BoardMove getMoveImplementation(IChessBoard const &chessBoard, Team team) const override;

    ScoredBoardMove alphaBetaSearch(IChessBoard &chessBoard, int currentDepth, Team team, int alpha, int beta) const;
    int getAlphaBetaBoardScore(IChessBoard const &chessBoard, Team team) const;
    std::vector<BoardMove> rankMoves(IChessBoard const &chessBoard, std::vector<BoardMove> const &moves) const;
    
    int depth = 4;
   
public:
    AdvancedComputerPlayer() = default;
};


#endif /* AdvancedComputerPlayer_h */
