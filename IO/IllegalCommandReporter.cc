// IllegalCommandReporter.cc

#include <string>

#include "IllegalCommandReporter.h"


void IllegalCommandReporter::reportError(std::string const &errorMessage) { reportErrorImpl(errorMessage); }
