// CommandLineErrorReporter.cc

#include <iostream>
#include <string>

#include "CommandLineErrorReporter.h"


// Basic ctor
CommandLineErrorReporter::CommandLineErrorReporter(std::ostream &out) : out(out) {}

void CommandLineErrorReporter::reportErrorImpl(std::string const &errorMessage) {
    out << "Error: " << errorMessage << std::endl;
}
