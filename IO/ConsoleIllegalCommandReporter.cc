// ConsoleIllegalCommandReporter.cc

#include <iostream>
#include <string>

#include "ConsoleIllegalCommandReporter.h"


// Basic ctor
ConsoleIllegalCommandReporter::ConsoleIllegalCommandReporter(std::ostream &out) : out(out) {}

void ConsoleIllegalCommandReporter::reportErrorImpl(std::string const &errorMessage) {
    out << "Error: " << errorMessage << std::endl;
}
