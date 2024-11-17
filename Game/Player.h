// Player.h

#ifndef Player_h
#define Player_h

#include <memory>

#include "ComputerPlayer.h"
#include "Constants.h"


/**
 * Player Class
 * Represents a Player in the game
 */
struct Player final {
private:
    PlayerType playerType;
    Team team;
    std::unique_ptr<ComputerPlayer> computerPlayer;

public:
    Player(PlayerType playerType, Team team, std::unique_ptr<ComputerPlayer> const &computerPlayer);
    Player(Player const &other);
    Player(Player &&other) noexcept;
    Player& operator=(Player &other);
    Player& operator=(Player &&other) noexcept;
    virtual ~Player() = default;

    PlayerType getPlayerType() const;
    Team getTeam() const;
    std::unique_ptr<ComputerPlayer> const& getComputerPlayer() const;

    void setComputerPlayer(std::unique_ptr<ComputerPlayer> const &computerPlayer);
};


#endif /* Player_h */
