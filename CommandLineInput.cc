// CommandLineInput.cc

#include <string>

#include "CommandLineInput.h"

CommandLineInput::CommandLineInput(std::istream &in) : Input(), in(in) {}

std::string CommandLineInput::acceptInput() {
    std::string input;
    std::getline(in, input);
    return input;
}

bool CommandLineInput::isInputAvailableImplementation() const {
    return !in.eof();
}
