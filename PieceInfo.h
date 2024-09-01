// PieceInfo.h

#ifndef PieceInfo_h
#define PieceInfo_h

#include "Constants.h"


// TODO: Move piece enums in here from constants

struct PieceInfo {

public:
    PieceType pieceType;
    Team team;
    PieceDirection pieceDirection;
    bool hasMoved;
    int pieceScore;
    std::string image;
    std::string display;

    PieceInfo(PieceType pieceType, Team team, PieceDirection pieceDirection, bool hasMoved, int pieceScore, std::string const &image, std::string const &display);

    bool operator==(PieceInfo const &other) const;
};



#endif /* PieceInfo_h */
