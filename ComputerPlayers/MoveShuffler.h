// MoveShuffler.h

#ifndef MoveShuffler_h
#define MoveShuffler_h

#include <vector>

#include "OldBoardMove.h"


class MoveShuffler {
public:
    static void shuffle(std::vector<OldBoardMove> &moves);
};


#endif /* MoveShuffler */
