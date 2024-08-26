// ComputerPlayerFactory.cc

#include <memory>

#include "ComputerPlayerFactory.h"
#include "ComputerPlayer.h"
#include "LevelOneComputer.h"
#include "LevelTwoComputer.h"
#include "LevelThreeComputer.h"
#include "AdvancedComputerPlayer.h"

// Static
std::unique_ptr<ComputerPlayer> ComputerPlayerFactory::createComputerPlayer(int computerPlayerLevel) {
    switch(computerPlayerLevel) {
        case 1:
            return std::make_unique<LevelOneComputer>();
        case 2:
            return std::make_unique<LevelTwoComputer>();
        case 3:
            return std::make_unique<LevelThreeComputer>();
        default:
            return std::make_unique<AdvancedComputerPlayer>();
    }
}
