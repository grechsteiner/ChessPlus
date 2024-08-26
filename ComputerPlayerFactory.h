// ComputerPlayerFactory.h

#ifndef ComputerPlayerFactory_h
#define ComputerPlayerFactory_h

#include <memory>

#include "ComputerPlayer.h"


class ComputerPlayerFactory {
public:
    static std::unique_ptr<ComputerPlayer> createComputerPlayer(int computerPlayerLevel);
};


#endif /* ComputerPlayerFactory_h */
