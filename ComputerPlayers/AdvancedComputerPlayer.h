// AdvancedComputerPlayer.h

#ifndef AdvancedComputerPlayer_h
#define AdvancedComputerPlayer_h

#include <utility>
#include <optional>

#include "ComputerPlayer.h"
#include "Constants.h"
#include "ChessBoard.h"

struct ScoredBoardMove {
    int score;
    std::optional<OldBoardMove> boardMove;

    ScoredBoardMove(int score, std::optional<OldBoardMove> boardMove = std::nullopt) : score(score), boardMove(boardMove) {}
};

class AdvancedComputerPlayer : public ComputerPlayer {
private:
    OldBoardMove getMoveImpl(ChessBoard const &chessBoard, Team team) const override;

    ScoredBoardMove alphaBetaSearch(ChessBoard &chessBoard, int currentDepth, Team team, int alpha, int beta) const;
    int getAlphaBetaBoardScore(ChessBoard const &chessBoard, Team team) const;
    std::vector<OldBoardMove> rankMoves(ChessBoard const &chessBoard, std::vector<OldBoardMove> const &moves) const;
    
    int depth = 4;
   
public:
    AdvancedComputerPlayer() = default;
};


#endif /* AdvancedComputerPlayer_h */
