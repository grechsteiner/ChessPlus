// PlayerFactory.h

#ifndef PlayerFactory_h
#define PlayerFactory_h

#include "Player.h"
#include "Constants.h"
#include "ComputerPlayer.h"


class PlayerFactory final {
public:
    static Player createHumanPlayer(Team team);
    static Player createComputerPlayer(Team team, std::unique_ptr<ComputerPlayer> const &computerPlayer);
};


#endif /* PlayerFactory_h */
