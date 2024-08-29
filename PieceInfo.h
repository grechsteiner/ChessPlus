// PieceInfo.h

#ifndef PieceInfo_h
#define PieceInfo_h

#include "Constants.h"


// TODO: Move piece enums in here from constants

class PieceInfo {

private:
    Color pieceColor;
    PieceType pieceType;
    PieceDirection pieceDirection;
    int pieceScore;
    bool hasMoved;
    std::string image;
    std::string display;

public:
    PieceInfo(Color pieceColor, PieceType pieceType, PieceDirection pieceDirection, bool hasMoved, std::string const &image, std::string const &display, int pieceScore);

    Color getPieceColor() const;
    PieceType getPieceType() const;
    PieceDirection getPieceDirection() const;
    int getPieceScore() const;
    bool getHasMoved() const;
    void setHasMoved(bool newHasMoved);
    const std::string& getImage() const;
    const std::string& getDisplay() const;

};



#endif /* PieceInfo_h */
