// GameWrapper.h

#ifndef GameWrapper_h
#define GameWrapper_h

#include <iostream>
#include <memory>
#include <vector>

#include "Game.h"
#include "Observer.h"


/**
 * Game Wrapper Class
 * Entry point to the program
 */
class GameWrapper final {
private:
    Game game;                                          // Subject    
    std::vector<std::unique_ptr<Observer>> observers;   // Observers  

public:
    explicit GameWrapper(std::istream &in, std::ostream &out, std::ostream &illegalCommandOut);
    GameWrapper(GameWrapper const &other) = delete;
    GameWrapper(GameWrapper &&other) = delete;
    GameWrapper& operator=(GameWrapper &other) = delete;
    GameWrapper& operator=(GameWrapper &&other) = delete;
    virtual ~GameWrapper() = default;

    void runGame();
};


#endif /* GameWrapper_h */
