// ConsoleIllegalCommandReporter.cc

#include <iostream>
#include <string>

#include "ConsoleIllegalCommandReporter.h"


// Basic ctor
ConsoleIllegalCommandReporter::ConsoleIllegalCommandReporter(std::ostream &out) : out(out) {}

// Copy ctor
ConsoleIllegalCommandReporter::ConsoleIllegalCommandReporter(ConsoleIllegalCommandReporter const &other) : IllegalCommandReporter(), out(other.out) {}

// Move ctor
ConsoleIllegalCommandReporter::ConsoleIllegalCommandReporter(ConsoleIllegalCommandReporter &&other) noexcept : IllegalCommandReporter(), out(other.out) {}

void ConsoleIllegalCommandReporter::reportIllegalCommandImpl(std::string const &illegalCommand) {
    out << "Illegal Command: " << illegalCommand << std::endl;
}
