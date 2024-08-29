// MoveShuffler.h

#ifndef MoveShuffler_h
#define MoveShuffler_h

#include <vector>

#include "BoardMove.h"


class MoveShuffler {
public:
    static void shuffle(std::vector<BoardMove> &moves);
};


#endif /* MoveShuffler */
