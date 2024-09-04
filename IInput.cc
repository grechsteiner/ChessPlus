// Input.cc

#include <string>

#include "Input.h"


bool Input::isInputAvailable() const { return isInputAvailableImpl(); }
std::string Input::getInput() const { return getInputImpl(); }
