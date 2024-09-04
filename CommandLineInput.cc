// CommandLineInput.cc

#include <string>
#include <iostream>

#include "CommandLineInput.h"

// Basic ctor
CommandLineInput::CommandLineInput(std::istream &in) : in(in) {}

bool CommandLineInput::isInputAvailableImpl() const {
    return !in.eof();
}

std::string CommandLineInput::getInputImpl() const {
    std::string input;
    std::getline(in, input);
    return input;
}
