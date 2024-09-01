// PieceInfo.cc

#include "PieceInfo.h"
#include "Constants.h"

PieceInfo::PieceInfo(PieceType pieceType, Team team, PieceDirection pieceDirection, bool hasMoved, int pieceScore, std::string const &image, std::string const &display) :
    pieceType(pieceType), team(team), pieceDirection(pieceDirection), hasMoved(hasMoved), pieceScore(pieceScore), image(image), display(display) {}

bool PieceInfo::operator==(PieceInfo const &other) const {
    return
        pieceType == other.pieceType &&
        team == other.team &&
        pieceDirection == other.pieceDirection &&
        hasMoved == other.hasMoved &&
        pieceScore == other.pieceScore &&
        image == other.image &&
        display == other.display;
}
