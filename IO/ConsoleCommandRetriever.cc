// ConsoleInputGetter.cc

#include <string>
#include <iostream>

#include "ConsoleInputGetter.h"


// Basic ctor
ConsoleInputGetter::ConsoleInputGetter(std::istream &in) : in(in) {}

bool ConsoleInputGetter::isInputAvailableImpl() const {
    return !in.eof();
}

std::string ConsoleInputGetter::getInputImpl() const {
    std::string input;
    std::getline(in, input);
    return input;
}
