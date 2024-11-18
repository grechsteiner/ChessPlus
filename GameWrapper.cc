// GameWrapper.cc

#include "GameWrapper.h"

#include <iostream>
#include <memory>

#include "ConsoleCommandRetriever.h"
#include "ConsoleIllegalCommandReporter.h"
#include "Game.h"
#include "Observer.h"
#include "TextObserver.h"


/*
 * Basic ctor
 */
GameWrapper::GameWrapper(std::istream &in, std::ostream &out, std::ostream &illegalCommandOut) : 
    game(std::make_unique<ConsoleCommandRetriever>(in), std::make_unique<ConsoleIllegalCommandReporter>(illegalCommandOut)) {

    observers.push_back(std::make_unique<TextObserver>(&game, out));
}

/*
 * Run the game
 */
void GameWrapper::runGame() {
    game.runGame();
}
