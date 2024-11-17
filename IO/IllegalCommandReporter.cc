// IllegalCommandReporter.cc

#include "IllegalCommandReporter.h"

#include <memory>
#include <string>


// Basic ctor
IllegalCommandReporter::IllegalCommandReporter() { }

// Copy ctor
IllegalCommandReporter::IllegalCommandReporter(IllegalCommandReporter const &other) { }

// Move ctor
IllegalCommandReporter::IllegalCommandReporter(IllegalCommandReporter &&other) noexcept { }

// Copy assignment
IllegalCommandReporter& IllegalCommandReporter::operator=(IllegalCommandReporter const &other) {
    if (this != &other) {
        return *this;
    }
    return *this;
}

// Move assignment
IllegalCommandReporter& IllegalCommandReporter::operator=(IllegalCommandReporter &&other) noexcept {
    if (this != &other) {
        return *this;
    }
    return *this;
}

/* Public Virtual Methods */
void IllegalCommandReporter::reportIllegalCommand(std::string const &message) { reportIllegalCommandImpl(message); }
std::unique_ptr<IllegalCommandReporter> IllegalCommandReporter::clone() const { return cloneImpl(); }
