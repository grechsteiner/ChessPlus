// CommandRetriever.cc

#include <string>

#include "CommandRetriever.h"


bool CommandRetriever::isInputAvailable() const { return isInputAvailableImpl(); }
std::string CommandRetriever::getInput() const { return getInputImpl(); }
