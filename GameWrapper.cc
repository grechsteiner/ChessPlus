// GameWrapper.cc

#include "GameWrapper.h"

#include <iostream>
#include <memory>
#include <vector>

#include "ConsoleCommandRetriever.h"
#include "ConsoleIllegalCommandReporter.h"
#include "Game.h"
#include "Observer.h"
#include "TextObserver.h"


// Basic ctor
GameWrapper::GameWrapper(std::istream &in, std::ostream &out, std::ostream &illegalCommandOut) : 
    game(std::make_unique<ConsoleCommandRetriever>(in), std::make_unique<ConsoleIllegalCommandReporter>(illegalCommandOut)) {

    observers.push_back(std::make_unique<TextObserver>(&game, out));
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

/*
 * Run the game
 */
void GameWrapper::runGame() {
    game.runGame();
}
