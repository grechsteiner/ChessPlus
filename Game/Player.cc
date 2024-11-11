// Player.cc

#include "Player.h"

// Basic ctor
Player::Player(PlayerType playerType, Team team, std::unique_ptr<ComputerPlayer> const &computerPlayer) :
    playerType(playerType), team(team), computerPlayer(computerPlayer->clone()) {}

// Copy ctor
Player::Player(Player const &other) :
    playerType(other.playerType), team(other.team), computerPlayer(other.computerPlayer->clone()) {}

// Move ctor
Player::Player(Player &&other) noexcept :
    playerType(other.playerType), team(other.team), computerPlayer(std::move(other.computerPlayer)) {}

// Copy assignment
Player& Player::operator=(Player &other) {
    if (this != &other) {
        playerType = other.playerType;
        team = other.team;
        computerPlayer = other.computerPlayer->clone();
    }
    return *this;
}

// Move assignment
Player& Player::operator=(Player &&other) noexcept {
    if (this != &other) {
        playerType = other.playerType;
        team = other.team;
        computerPlayer = std::move(other.computerPlayer);
    }
    return *this;
}

PlayerType Player::getPlayerType() const { return playerType; }
Team Player::getTeam() const { return team; }
std::unique_ptr<ComputerPlayer> const& Player::getComputerPlayer() const { return computerPlayer; }
void Player::setComputerPlayer(std::unique_ptr<ComputerPlayer> const &computerPlayer) { this->computerPlayer = computerPlayer->clone(); }
