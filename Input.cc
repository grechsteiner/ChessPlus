// Input.cc

#include <string>

#include "Input.h"

std::string Input::getInput() {
    return getInputImpl();
}

bool Input::isInputAvailable() const {
    return isInputAvailableImpl();
}
