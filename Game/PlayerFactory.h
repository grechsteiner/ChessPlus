// PlayerFactory.h

#ifndef PlayerFactory_h
#define PlayerFactory_h

#include <memory>

#include "Player.h"
#include "ComputerPlayer.h"
#include "Constants.h"


/**
 * Factory for creating Player instances
 */
class PlayerFactory final {
public:
    static Player createHumanPlayer(Team team);
    static Player createComputerPlayer(Team team, std::unique_ptr<ComputerPlayer> const &computerPlayer);
};


#endif /* PlayerFactory_h */
