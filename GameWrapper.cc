// GameWrapper.cc

#include <memory>

#include "Game.h"
#include "GameWrapper.h"
#include "TextObserver.h"
#include "GraphicObserver.h"

GameWrapper::GameWrapper(std::istream &in, std::ostream &out, std::ostream &errorOut) : 
    game(board, in, out, errorOut), 
    observers() 
    {
        observers.push_back(std::make_unique<TextObserver>(out, &game));
        observers.push_back(std::make_unique<GraphicObserver>(&game));
    }

void GameWrapper::runGame() {
    game.runGame();
}
