// GameWrapper.h

#ifndef GameWrapper_h
#define GameWrapper_h

#include <iostream>
#include <memory>

#include "Game.h"
#include "Observer.h"


class GameWrapper {
private:
    Game game;                                                  // Subject    
    std::vector<std::unique_ptr<Observer>> observers;           // Observers  

public:
    explicit GameWrapper(std::istream &in, std::ostream &out, std::ostream &errorOut);
    GameWrapper(GameWrapper const &other);
    GameWrapper(GameWrapper &&other) noexcept;
    GameWrapper& operator=(GameWrapper &other);
    GameWrapper& operator=(GameWrapper &&other) noexcept;
    virtual ~GameWrapper() = default;
    
    void runGame();
};


#endif /* GameWrapper_h */
