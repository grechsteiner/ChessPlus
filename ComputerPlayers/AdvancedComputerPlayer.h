// AdvancedComputerPlayer.h

#ifndef AdvancedComputerPlayer_h
#define AdvancedComputerPlayer_h

#include <utility>
#include <optional>

#include "ComputerPlayer.h"
#include "Constants.h"
#include "ChessBoard.h"
#include "BoardMove.h"
#include "PieceData.h"


struct ScoredBoardMove {
    int score;
    std::optional<std::unique_ptr<BoardMove>> boardMove;

    ScoredBoardMove(int score, std::optional<std::unique_ptr<BoardMove>> const &boardMove = std::nullopt) : score(score) {
        if (boardMove.has_value()) {
            this->boardMove = boardMove.value()->clone();
        } else {
            this->boardMove = std::nullopt;
        }
    }
};

class AdvancedComputerPlayer : public ComputerPlayer {
private:
    std::unique_ptr<BoardMove> getMoveImpl(ChessBoard const &chessBoard, Team team) const override;

    ScoredBoardMove alphaBetaSearch(ChessBoard &chessBoard, int currentDepth, Team team, int alpha, int beta) const;
    int getAlphaBetaBoardScore(ChessBoard const &chessBoard, Team team) const;
    std::vector<std::unique_ptr<BoardMove>> rankMoves(ChessBoard const &chessBoard, std::vector<std::unique_ptr<BoardMove>> const &moves) const;
    
    int depth = 4;
   
public:
    AdvancedComputerPlayer() = default;
};


#endif /* AdvancedComputerPlayer_h */
