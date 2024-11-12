// ConsoleCommandRetriever.cc

#include <string>
#include <iostream>

#include "ConsoleCommandRetriever.h"


// Basic ctor
ConsoleCommandRetriever::ConsoleCommandRetriever(std::istream &in) : in(in) {}

// Copy ctor
ConsoleCommandRetriever::ConsoleCommandRetriever(ConsoleCommandRetriever const &other) : Cloneable<CommandRetriever, ConsoleCommandRetriever>(), in(other.in) {}

// Move ctor
ConsoleCommandRetriever::ConsoleCommandRetriever(ConsoleCommandRetriever &&other) noexcept : Cloneable<CommandRetriever, ConsoleCommandRetriever>(), in(other.in) {}

bool ConsoleCommandRetriever::isCommandAvailableImpl() const {
    return !in.eof();
}

std::optional<std::string> ConsoleCommandRetriever::retrieveCommandImpl() const {
    std::string input;
    if (std::getline(in, input)) {
        return std::make_optional<std::string>(input);
    } else {
        return std::nullopt;
    }
}
