// Observer.cc

#include "Observer.h"


/*
 * Basic ctor
 */
Observer::Observer() { }

/*
 * Copy ctor
 */
Observer::Observer(Observer const &other) { }

/*
 * Move ctor
 */
Observer::Observer(Observer &&other) noexcept { }

/*
 * Copy assignment
 */
Observer& Observer::operator=(Observer const &other) {
    if (this != &other) {
        return *this;
    }
    return *this;
}

/*
 * Move assignment
 */
Observer& Observer::operator=(Observer &&other) noexcept {
    if (this != &other) {
        return *this;
    }
    return *this;
}

/* Public Virtual Methods */
void Observer::notify() { notifyImpl(); }
