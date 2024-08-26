// CommandLineErrorReporter.cc

#include <string>

#include "CommandLineErrorReporter.h"

CommandLineErrorReporter::CommandLineErrorReporter(std::ostream &out) : ErrorReporter(), out(out) {}

void CommandLineErrorReporter::outputError(std::string const &errorMessage) {
    out << "Error: " << errorMessage << std::endl;
}
