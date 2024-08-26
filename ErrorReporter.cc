// ErrorReporter.cc

#include <string>

#include "ErrorReporter.h"

void ErrorReporter::reportError(std::string const &errorMessage) {
    outputError(errorMessage);
}
