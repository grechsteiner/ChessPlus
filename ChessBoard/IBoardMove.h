// IBoardMove.h

#ifndef IBoardMove_H
#define IBoardMove_H

#include <memory>

#include "BoardSquare.h"
#include "Piece.h"


class IBoardMove {

private:
    BoardSquare fromSquare;
    BoardSquare toSquare;
    BoardSquare captureSquare;

    std::unique_ptr<Piece> movedPiece;
    std::unique_ptr<Piece> capturedPiece;

    bool enablesEnpassant;


public:

};


#endif /* IBoardMove_H */
