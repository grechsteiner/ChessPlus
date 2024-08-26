// Subject.cpp

#include <algorithm>
#include <vector>

#include "Subject.h"
#include "Observer.h"


void Subject::attach(Observer *observer) {
    observers.emplace_back(observer);
}

void Subject::detach(Observer *observer) {
    observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
}

void Subject::notifyObservers() {
    for (auto observer : observers) {
        observer->notify();
    }
}

Subject::~Subject() {}
