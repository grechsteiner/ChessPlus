// ConsoleInvalidCommandReporter.cc

#include <iostream>
#include <string>

#include "ConsoleInvalidCommandReporter.h"


// Basic ctor
ConsoleInvalidCommandReporter::ConsoleInvalidCommandReporter(std::ostream &out) : out(out) {}

void ConsoleInvalidCommandReporter::reportErrorImpl(std::string const &errorMessage) {
    out << "Error: " << errorMessage << std::endl;
}
