// GameWrapper.cc

#include <memory>

#include "Game.h"
#include "GameWrapper.h"
#include "TextObserver.h"
#include "GraphicObserver.h"
#include "ConsoleCommandRetriever.h"
#include "ConsoleIllegalCommandReporter.h"

GameWrapper::GameWrapper(std::istream &in, std::ostream &out, std::ostream &errorOut) : 
    game(std::make_unique<ChessBoardImpl>(8, 8), std::make_unique<ConsoleCommandRetriever>(), std::make_unique<ConsoleIllegalCommandReporter>()) {

    observers.push_back(std::make_unique<TextObserver>(out, &game));
    // observers.push_back(std::make_unique<GraphicObserver>(&game));
}

void GameWrapper::runGame() {
    game.runGame();
}
