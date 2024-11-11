// PlayerFactory.cc

#include "PlayerFactory.h"
#include "Player.h"
#include "Constants.h"
#include "ComputerPlayer.h"

// Static
Player PlayerFactory::createHumanPlayer(Team team) {
    return Player(PlayerType::HUMAN, team, nullptr);
}

// Static
Player PlayerFactory::createComputerPlayer(Team team, std::unique_ptr<ComputerPlayer> const &computerPlayer) {
    return Player(PlayerType::COMPUTER, team, computerPlayer);
}
