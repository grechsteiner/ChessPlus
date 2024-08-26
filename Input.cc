// Input.cc

#include <string>

#include "Input.h"

std::string Input::getInput() {
    return acceptInput();
}

bool Input::isInputAvailable() const {
    return isInputAvailableImplementation();
}
