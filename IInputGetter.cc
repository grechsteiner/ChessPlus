// IInputGetter.cc

#include <string>

#include "IInputGetter.h"


bool IInputGetter::isInputAvailable() const { return isInputAvailableImpl(); }
std::string IInputGetter::getInput() const { return getInputImpl(); }
