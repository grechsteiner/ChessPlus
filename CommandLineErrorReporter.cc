// CommandLineErrorReporter.cc

#include <string>

#include "CommandLineErrorReporter.h"

CommandLineErrorReporter::CommandLineErrorReporter(std::ostream &out) : ErrorReporter(), out(out) {}

void CommandLineErrorReporter::reportErrorImpl(std::string const &errorMessage) {
    out << "Error: " << errorMessage << std::endl;
}
