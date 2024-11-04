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
std::unique_ptr<ComputerPlayer> ComputerPlayerFactory::createComputerPlayer(ComputerPlayerLevel computerPlayerLevel) {
    switch (computerPlayerLevel) {
        case ComputerPlayerLevel::ONE:
            return std::make_unique<LevelOneComputer>();
        case ComputerPlayerLevel::TWO:
            return std::make_unique<LevelTwoComputer>();
        case ComputerPlayerLevel::THREE:
            return std::make_unique<LevelThreeComputer>();
        case ComputerPlayerLevel::FOUR:
            return std::make_unique<LevelFourComputer>();
        case ComputerPlayerLevel::FIVE:
            return std::make_unique<LevelFiveComputer>();
        default:
            assert(false);
    }
}
