// CommandRetriever.cc

#include <string>

#include "CommandRetriever.h"


// Basic ctor
CommandRetriever::CommandRetriever() {}

// Move ctor
CommandRetriever::CommandRetriever(CommandRetriever &&other) noexcept {}

// Move assignment
CommandRetriever& CommandRetriever::operator=(CommandRetriever &&other) noexcept {}

bool CommandRetriever::isCommandAvailable() const { return isCommandAvailableImpl(); }
std::string CommandRetriever::retrieveCommand() const { return retrieveCommandImpl(); }
