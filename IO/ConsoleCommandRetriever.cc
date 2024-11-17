// ConsoleCommandRetriever.cc

#include "ConsoleCommandRetriever.h"

#include <iostream>
#include <optional>
#include <string>
#include <utility>

#include "Cloneable.h"
#include "CommandRetriever.h"


/*
 * Basic ctor
 */
ConsoleCommandRetriever::ConsoleCommandRetriever(std::istream &in) : 
    Cloneable<CommandRetriever, ConsoleCommandRetriever>(), in(in) { }

/*
 * Copy ctor
 */
ConsoleCommandRetriever::ConsoleCommandRetriever(ConsoleCommandRetriever const &other) : 
    Cloneable<CommandRetriever, ConsoleCommandRetriever>(other), in(other.in) { }

/*
 * Move ctor
 */
ConsoleCommandRetriever::ConsoleCommandRetriever(ConsoleCommandRetriever &&other) noexcept : 
    Cloneable<CommandRetriever, ConsoleCommandRetriever>(std::move(other)), in(other.in) { }

/*
 * True if there is a command available to read, false otherwise
 */
bool ConsoleCommandRetriever::isCommandAvailableImpl() const {
    return !in.eof();
}

/*
 * Return Optional String representing current command
 */
std::optional<std::string> ConsoleCommandRetriever::retrieveCommandImpl() const {
    std::string input;
    return std::getline(in, input)
        ? std::make_optional<std::string>(input)
        : std::nullopt;
}
