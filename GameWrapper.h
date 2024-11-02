// GameWrapper.h

#ifndef GameWrapper_h
#define GameWrapper_h

#include <iostream>
#include <memory>

#include "Game.h"
#include "Observer.h"
#include "ChessBoardImpl.h"

class GameWrapper {
private:
    Game game;                                                  // Subject    
    std::vector<std::unique_ptr<Observer>> observers;           // Observers  

public:
    GameWrapper(std::istream &in, std::ostream &out, std::ostream &errorOut);
    void runGame();
};

#endif /* GameWrapper_h */
