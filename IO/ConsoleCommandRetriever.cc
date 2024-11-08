// ConsoleCommandRetriever.cc

#include <string>
#include <iostream>

#include "ConsoleCommandRetriever.h"


// Basic ctor
ConsoleCommandRetriever::ConsoleCommandRetriever(std::istream &in) : in(in) {}

bool ConsoleCommandRetriever::isInputAvailableImpl() const {
    return !in.eof();
}

std::string ConsoleCommandRetriever::getInputImpl() const {
    std::string input;
    std::getline(in, input);
    return input;
}
