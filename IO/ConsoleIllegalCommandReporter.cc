// ConsoleIllegalCommandReporter.cc

#include <iostream>
#include <string>

#include "ConsoleIllegalCommandReporter.h"


// Basic ctor
ConsoleIllegalCommandReporter::ConsoleIllegalCommandReporter(std::ostream &out) : 
    out(out) {}

// Copy ctor
ConsoleIllegalCommandReporter::ConsoleIllegalCommandReporter(ConsoleIllegalCommandReporter const &other) : 
    Cloneable<IllegalCommandReporter,ConsoleIllegalCommandReporter>(), out(other.out) {}

// Move ctor
ConsoleIllegalCommandReporter::ConsoleIllegalCommandReporter(ConsoleIllegalCommandReporter &&other) noexcept : 
    Cloneable<IllegalCommandReporter,ConsoleIllegalCommandReporter>(), out(other.out) {}

void ConsoleIllegalCommandReporter::reportIllegalCommandImpl(std::string const &message) {
    out << "Illegal Command: " << message << std::endl;
}
