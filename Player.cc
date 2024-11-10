// Player.cc

#include "Player.h"

// Basic ctor
Player::Player(Team team, std::unique_ptr<ComputerPlayer> const &computerPlayer) :
    team(team), computerPlayer(computerPlayer->clone()) {}

// Copy ctor
Player::Player(Player const &other) :
    team(other.team), computerPlayer(other.computerPlayer->clone()) {}

// Move ctor
Player::Player(Player &&other) noexcept :
    team(other.team), computerPlayer(std::move(other.computerPlayer)) {}

// Copy assignment
Player& Player::operator=(Player &other) {
    if (this != &other) {
        team = other.team;
        computerPlayer = other.computerPlayer->clone();
    }
    return *this;
}

// Move assignment
Player& Player::operator=(Player &&other) noexcept {
    if (this != &other) {
        team = other.team;
        computerPlayer = std::move(other.computerPlayer);
    }
    return *this;
}


Team Player::getTeam() const { return team; }
std::unique_ptr<ComputerPlayer> const& Player::getComputerPlayer() const { return computerPlayer; }
void Player::setComputerPlayer(std::unique_ptr<ComputerPlayer> const &computerPlayer) { this->computerPlayer = computerPlayer->clone(); }
