// GameWrapper.cc

#include <iostream>
#include <memory>

#include "GameWrapper.h"
#include "Game.h"
#include "TextObserver.h"
#include "GraphicObserver.h"
#include "ConsoleCommandRetriever.h"
#include "ConsoleIllegalCommandReporter.h"


// Basic ctor
GameWrapper::GameWrapper(std::istream &in, std::ostream &out, std::ostream &errorOut) : 
    game(std::make_unique<ChessBoardImpl>(8, 8), std::make_unique<ConsoleCommandRetriever>(), std::make_unique<ConsoleIllegalCommandReporter>()) {

    observers.push_back(std::make_unique<TextObserver>(out, &game));
    // observers.push_back(std::make_unique<GraphicObserver>(&game));
}

// Copy ctor
GameWrapper::GameWrapper(GameWrapper const &other) : game(other.game) {
    for (std::unique_ptr<Observer> const &observer : other.observers) {
        observers.push_back(observer->clone());
    }
}

// Move ctor
GameWrapper::GameWrapper(GameWrapper &&other) noexcept : 
    game(std::move(other.game)), observers(std::move(other.observers)) {}

// Copy assignment
GameWrapper& GameWrapper::operator=(GameWrapper &other) {
    if (this != &other) {
        game = other.game;

        observers.clear();
        for (std::unique_ptr<Observer> const &observer : other.observers) {
            observers.push_back(observer->clone());
        }
    }
    return *this;
}

// Move assignment
GameWrapper& GameWrapper::operator=(GameWrapper &&other) noexcept {
    if (this != &other) {
        game = std::move(other.game);
        observers = std::move(other.observers);
    }
    return *this;
}

void GameWrapper::runGame() {
    game.runGame();
}
