// ComputerPlayerFactory.h

#ifndef ComputerPlayerFactory_h
#define ComputerPlayerFactory_h

#include <memory>

#include "ComputerPlayer.h"
#include "ChessBoard.h"
#include "Constants.h"


class ComputerPlayerFactory {
public:
    static std::unique_ptr<ComputerPlayer> createComputerPlayer(ComputerPlayerLevel computerPlayerLevel, ChessBoard const &chessBoard, Team team);
};


#endif /* ComputerPlayerFactory_h */
