// IllegalCommandReporter.cc

#include <string>

#include "IllegalCommandReporter.h"

// Basic ctor
IllegalCommandReporter::IllegalCommandReporter() {}

// Move ctor
IllegalCommandReporter::IllegalCommandReporter(IllegalCommandReporter &&other) noexcept {}

// Move assignment
IllegalCommandReporter& IllegalCommandReporter::operator=(IllegalCommandReporter &&other) noexcept {}

void IllegalCommandReporter::reportIllegalCommand(std::string const &illegalCommand) { reportIllegalCommandImpl(illegalCommand); }
