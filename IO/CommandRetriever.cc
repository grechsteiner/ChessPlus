// CommandRetriever.cc

#include "CommandRetriever.h"

#include <memory>
#include <optional>
#include <string>


// Basic ctor
CommandRetriever::CommandRetriever() { }

// Copy ctor
CommandRetriever::CommandRetriever(CommandRetriever const &other) { }

// Move ctor
CommandRetriever::CommandRetriever(CommandRetriever &&other) noexcept { }

// Copy assignment
CommandRetriever& CommandRetriever::operator=(CommandRetriever const &other) {
    if (this != &other) {
        return *this;
    }
    return *this;
}

// Move assignment
CommandRetriever& CommandRetriever::operator=(CommandRetriever &&other) noexcept {
    if (this != &other) {
        return *this;
    }
    return *this;
}

/* Public Virtual Methods */
bool CommandRetriever::isCommandAvailable() const { return isCommandAvailableImpl(); }
std::optional<std::string> CommandRetriever::retrieveCommand() const { return retrieveCommandImpl(); }
std::unique_ptr<CommandRetriever> CommandRetriever::clone() const { return cloneImpl(); }
