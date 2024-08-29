// AdvancedComputerPlayer.h

#ifndef AdvancedComputerPlayer_h
#define AdvancedComputerPlayer_h

#include <utility>

#include "ComputerPlayer.h"
#include "Constants.h"
#include "Board.h"
#include "Move.h"


class AdvancedComputerPlayer : public ComputerPlayer {
private:
    std::vector<FullMove> rank_moves(ChessBoard& board, const std::vector<FullMove>& moves) const;
    FullMove getMoveImplementation(ChessBoard &board, Color color) const override;
    int depth = 4;

    std::tuple<int, FullMove> alphaBetaSearch(ChessBoard &board, int currentDepth, Color color, int beta, int alpha) const;
public:
    AdvancedComputerPlayer() = default;
};


#endif /* AdvancedComputerPlayer_h */
