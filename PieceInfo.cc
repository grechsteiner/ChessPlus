// PieceInfo.cc

#include "PieceInfo.h"
#include "Constants.h"

PieceInfo::PieceInfo(Color pieceColor, PieceType pieceType, PieceDirection pieceDirection, bool hasMoved, std::string const &image, std::string const &display, int pieceScore) :
    pieceColor(pieceColor), pieceType(pieceType), pieceDirection(pieceDirection), hasMoved(hasMoved), image(image), display(display), pieceScore(pieceScore) {}

