// Player.cc

#include "Player.h"

#include <memory>

#include "ComputerPlayer.h"
#include "Constants.h"


// Basic ctor
Player::Player(PlayerType playerType, Team team, std::unique_ptr<ComputerPlayer> const &computerPlayer) :
    playerType(playerType), team(team), computerPlayer(computerPlayer == nullptr ? nullptr : computerPlayer->clone()) {}

// Copy ctor
Player::Player(Player const &other) :
    playerType(other.playerType), team(other.team), computerPlayer(other.computerPlayer == nullptr ? nullptr : other.computerPlayer->clone()) {}

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

// Getters
PlayerType Player::getPlayerType() const { return playerType; }
Team Player::getTeam() const { return team; }
std::unique_ptr<ComputerPlayer> const& Player::getComputerPlayer() const { return computerPlayer; }

// Setters
void Player::setComputerPlayer(std::unique_ptr<ComputerPlayer> const &computerPlayer) { this->computerPlayer = computerPlayer->clone(); }
