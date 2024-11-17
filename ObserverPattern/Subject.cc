// Subject.cpp

#include "Subject.h"

#include <algorithm>
#include <utility>
#include <vector>

#include "Observer.h"


/*
 * Basic ctor
 */
Subject::Subject() :
    observers() { }

/*
 * Copy ctor
 */
Subject::Subject(Subject const &other) :
    observers(other.observers) { }

/*
 * Move ctor
 */
Subject::Subject(Subject &&other) noexcept :
    observers(std::move(other.observers)) { }

/*
 * Copy assignment
 */
Subject& Subject::operator=(Subject const &other) {
    if (this != &other) {
        observers = other.observers;
    }
    return *this;
}

/*
 * Move assignment
 */
Subject& Subject::operator=(Subject &&other) noexcept {
    if (this != &other) {
        observers = std::move(other.observers);
    }
    return *this;
}

/*
 * Dtor
 */
Subject::~Subject() { }

/*
 * Attach observer 
 */
void Subject::attach(Observer *observer) {
    observers.emplace_back(observer);
}

/*
 * Detach observer
 */
void Subject::detach(Observer *observer) {
    observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
}

/*
 * Notify observers 
 */
void Subject::notifyObservers() {
    for (auto observer : observers) {
        observer->notify();
    }
}
