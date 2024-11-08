// ComputerPlayer.h

#ifndef ComputerPlayer_h
#define ComputerPlayer_h

#include <memory>

#include "Constants.h"
#include "ChessBoardImpl.h"
#include "BoardMove.h"
#include "ChessBoard.h"

class ComputerPlayer {
private:
    virtual std::unique_ptr<BoardMove> generateMoveImpl() const = 0;
    virtual std::unique_ptr<ComputerPlayer> cloneImpl() const = 0;

protected:
    explicit ComputerPlayer(ChessBoard const &chessBoard, Team team);
    ComputerPlayer(ComputerPlayer const &other) = default;
    ComputerPlayer(ComputerPlayer &&other) noexcept;
    // Copy assignment disabled
    // Move assignment disabled

    ChessBoard const &chessBoard;
    Team team;

    void shuffle(std::vector<std::unique_ptr<BoardMove>> &moves) const;

public:
    virtual ~ComputerPlayer() = default;
   
    std::unique_ptr<BoardMove> generateMove() const;
    std::unique_ptr<ComputerPlayer> clone() const;

    Team getTeam() const;
};


#endif /* ComputerPlayer_h */
