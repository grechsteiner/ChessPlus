// IllegalCommandReporter.cc

#include <string>

#include "IllegalCommandReporter.h"

// Basic ctor
IllegalCommandReporter::IllegalCommandReporter() {}

// Move ctor
IllegalCommandReporter::IllegalCommandReporter(IllegalCommandReporter &&other) noexcept {}

// Move assignment
IllegalCommandReporter& IllegalCommandReporter::operator=(IllegalCommandReporter &&other) noexcept {
    if (this != &other) {
        // Update if needed
        return *this;
    }
    return *this;
}

void IllegalCommandReporter::reportIllegalCommand(std::string const &message) { reportIllegalCommandImpl(message); }
std::unique_ptr<IllegalCommandReporter> IllegalCommandReporter::clone() const { return cloneImpl(); }
