// ComputerPlayerFactory.cc

#include <memory>
#include <cassert>

#include "ComputerPlayerFactory.h"
#include "ComputerPlayer.h"
#include "LevelOneComputer.h"
#include "LevelTwoComputer.h"
#include "LevelThreeComputer.h"
#include "LevelFourComputer.h"
#include "LevelFiveComputer.h"

// Static
std::unique_ptr<ComputerPlayer> ComputerPlayerFactory::createComputerPlayer(ComputerPlayerLevel computerPlayerLevel, Team team) {
    switch (computerPlayerLevel) {
        case ComputerPlayerLevel::ONE:
            return std::make_unique<LevelOneComputer>(team);
        case ComputerPlayerLevel::TWO:
            return std::make_unique<LevelTwoComputer>(team);
        case ComputerPlayerLevel::THREE:
            return std::make_unique<LevelThreeComputer>(team);
        case ComputerPlayerLevel::FOUR:
            return std::make_unique<LevelFourComputer>(team);
        case ComputerPlayerLevel::FIVE:
            return std::make_unique<LevelFiveComputer>(team);
        default:
            assert(false);
    }
}
