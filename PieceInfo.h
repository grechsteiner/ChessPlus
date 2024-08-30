// PieceInfo.h

#ifndef PieceInfo_h
#define PieceInfo_h

#include "Constants.h"


// TODO: Move piece enums in here from constants

struct PieceInfo {

public:
    Team team;
    PieceType pieceType;
    PieceDirection pieceDirection;
    int pieceScore;
    bool hasMoved;
    std::string image;
    std::string display;

    PieceInfo(Team team, PieceType pieceType, PieceDirection pieceDirection, bool hasMoved, std::string const &image, std::string const &display, int pieceScore);
};



#endif /* PieceInfo_h */
