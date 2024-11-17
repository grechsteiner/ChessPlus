// ConsoleIllegalCommandReporter.cc

#include "ConsoleIllegalCommandReporter.h"

#include <iostream>
#include <string>

#include "Cloneable.h"
#include "IllegalCommandReporter.h"


// Basic ctor
ConsoleIllegalCommandReporter::ConsoleIllegalCommandReporter(std::ostream &out) : 
    Cloneable<IllegalCommandReporter,ConsoleIllegalCommandReporter>(), out(out) {}

// Copy ctor
ConsoleIllegalCommandReporter::ConsoleIllegalCommandReporter(ConsoleIllegalCommandReporter const &other) : 
    Cloneable<IllegalCommandReporter,ConsoleIllegalCommandReporter>(other), out(other.out) {}

// Move ctor
ConsoleIllegalCommandReporter::ConsoleIllegalCommandReporter(ConsoleIllegalCommandReporter &&other) noexcept : 
    Cloneable<IllegalCommandReporter,ConsoleIllegalCommandReporter>(std::move(other)), out(other.out) {}


/*
 * Output the illegal command report
 */
void ConsoleIllegalCommandReporter::reportIllegalCommandImpl(std::string const &message) {
    out << "Illegal Command: " << message << std::endl;
}
