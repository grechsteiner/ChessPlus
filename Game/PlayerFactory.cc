// PlayerFactory.cc

#include "PlayerFactory.h"

#include <memory>

#include "Player.h"
#include "ComputerPlayer.h"
#include "Constants.h"


/*
 * Static
 *
 * Return an instance of Player with type Human
 */
Player PlayerFactory::createHumanPlayer(Team team) {
    return Player(PlayerType::HUMAN, team, nullptr);
}

/*
 * Static
 *
 * Return an instance of a Player with type Computer
 */
Player PlayerFactory::createComputerPlayer(Team team, std::unique_ptr<ComputerPlayer> const &computerPlayer) {
    return Player(PlayerType::COMPUTER, team, computerPlayer);
}
