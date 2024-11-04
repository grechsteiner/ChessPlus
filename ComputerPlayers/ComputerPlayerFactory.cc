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
std::unique_ptr<ComputerPlayer> ComputerPlayerFactory::createComputerPlayer(ComputerPlayerLevel computerPlayerLevel, ChessBoard const &chessBoard, Team team) {
    switch (computerPlayerLevel) {
        case ComputerPlayerLevel::ONE:
            return std::make_unique<LevelOneComputer>(chessBoard, team);
        case ComputerPlayerLevel::TWO:
            return std::make_unique<LevelTwoComputer>(chessBoard, team);
        case ComputerPlayerLevel::THREE:
            return std::make_unique<LevelThreeComputer>(chessBoard, team);
        case ComputerPlayerLevel::FOUR:
            return std::make_unique<LevelFourComputer>(chessBoard, team);
        case ComputerPlayerLevel::FIVE:
            return std::make_unique<LevelFiveComputer>(chessBoard, team);
        default:
            assert(false);
    }
}
