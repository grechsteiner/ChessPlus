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
    virtual std::unique_ptr<BoardMove> generateMoveImpl(std::unique_ptr<ChessBoard> const &chessBoard) const = 0;
    virtual std::unique_ptr<ComputerPlayer> cloneImpl() const = 0;

protected:
    explicit ComputerPlayer(Team team);
    ComputerPlayer(ComputerPlayer const &other);
    ComputerPlayer(ComputerPlayer &&other) noexcept;
    ComputerPlayer& operator=(ComputerPlayer &other);
    ComputerPlayer& operator=(ComputerPlayer &&other) noexcept;

    Team team;

    void shuffle(std::vector<std::unique_ptr<BoardMove>> &moves) const;

public:
    virtual ~ComputerPlayer() = default;
   
    std::unique_ptr<BoardMove> generateMove(std::unique_ptr<ChessBoard> const &chessBoard) const;
    std::unique_ptr<ComputerPlayer> clone() const;

    Team getTeam() const;
};


#endif /* ComputerPlayer_h */
