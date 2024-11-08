// ConsoleCommandRetriever.cc

#include <string>
#include <iostream>

#include "ConsoleCommandRetriever.h"


// Basic ctor
ConsoleCommandRetriever::ConsoleCommandRetriever(std::istream &in) : in(in) {}

// Copy ctor
ConsoleCommandRetriever::ConsoleCommandRetriever(ConsoleCommandRetriever const &other) : CommandRetriever(), in(other.in) {}

// Move ctor
ConsoleCommandRetriever::ConsoleCommandRetriever(ConsoleCommandRetriever &&other) noexcept : CommandRetriever(), in(other.in) {}

bool ConsoleCommandRetriever::isCommandAvailableImpl() const {
    return !in.eof();
}

std::string ConsoleCommandRetriever::retrieveCommandImpl() const {
    std::string input;
    return std::getline(in, input) ? input : "";
}
