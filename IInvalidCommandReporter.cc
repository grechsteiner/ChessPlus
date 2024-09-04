// IInvalidCommandReporter.cc

#include <string>

#include "IInvalidCommandReporter.h"


void IInvalidCommandReporter::reportError(std::string const &errorMessage) { reportErrorImpl(errorMessage); }
