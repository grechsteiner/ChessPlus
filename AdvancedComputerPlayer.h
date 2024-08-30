// AdvancedComputerPlayer.h

#ifndef AdvancedComputerPlayer_h
#define AdvancedComputerPlayer_h

#include <utility>

#include "ComputerPlayer.h"
#include "Constants.h"
#include "Board.h"



class AdvancedComputerPlayer : public ComputerPlayer {
private:
    int getAlphaBetaBoardScore(ChessBoard& board, Team team) const;
    std::vector<BoardMove> rank_moves(ChessBoard& board, const std::vector<BoardMove>& moves) const;
    BoardMove getMoveImplementation(ChessBoard &board, Team team) const override;
    int depth = 4;

    std::tuple<int, BoardMove> alphaBetaSearch(ChessBoard &board, int currentDepth, Team team, int beta, int alpha) const;
public:
    AdvancedComputerPlayer() = default;
};


#endif /* AdvancedComputerPlayer_h */
