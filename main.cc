// main.cc

#include <iostream>

#include "GameWrapper.h"

int main () {
    GameWrapper gameWrapper(std::cin, std::cout, std::cout);
    gameWrapper.runGame();
}
