// PieceInfo.cc

#include "PieceInfo.h"
#include "Constants.h"

PieceInfo::PieceInfo(Color pieceColor, PieceType pieceType, PieceDirection pieceDirection, bool hasMoved, std::string const &image, std::string const &display, int pieceScore) :
    pieceColor(pieceColor), pieceType(pieceType), pieceDirection(pieceDirection), hasMoved(hasMoved), image(image), display(display), pieceScore(pieceScore) {}

Color PieceInfo::getPieceColor() const { return pieceColor; }
PieceType PieceInfo::getPieceType() const { return pieceType; }
PieceDirection PieceInfo::getPieceDirection() const { return pieceDirection; }
int PieceInfo::getPieceScore() const { return pieceScore; }
bool PieceInfo::getHasMoved() const { return hasMoved; }
void PieceInfo::setHasMoved(bool newHasMoved) { hasMoved = newHasMoved; }
const std::string& PieceInfo::getImage() const { return image; }
const std::string& PieceInfo::getDisplay() const { return display; }
