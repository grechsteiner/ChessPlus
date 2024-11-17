// Observer.cc

#include "Observer.h"

/*
 * Basic ctor
 */
Observer::Observer() {}

/*
 * Move ctor
 */
Observer::Observer(Observer &&other) noexcept {}

/*
 * Move assignment
 */
Observer& Observer::operator=(Observer &&other) noexcept {
    if (this != &other) {
        // Update if needed
        return *this;
    }
    return *this;
}

void Observer::notify() { notifyImpl(); }
std::unique_ptr<Observer> Observer::clone() const { return cloneImpl(); }
