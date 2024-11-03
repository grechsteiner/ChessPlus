// MoveShuffler.cc

#include <algorithm>
#include <random>
#include <chrono>

#include "MoveShuffler.h"


// Static
void MoveShuffler::shuffle(std::vector<std::unique_ptr<BoardMove>> &moves) {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(moves.begin(), moves.end(), std::default_random_engine(seed));
}

