// MoveShuffler.h

#ifndef MoveShuffler_h
#define MoveShuffler_h

#include <vector>

#include "Move.h"


class MoveShuffler {
public:
    static void shuffle(std::vector<Move> &moves);
};


#endif /* MoveShuffler */
