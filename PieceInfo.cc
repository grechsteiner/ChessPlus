// PieceInfo.cc

#include "PieceInfo.h"
#include "Constants.h"

PieceInfo::PieceInfo(Team team, PieceType pieceType, PieceDirection pieceDirection, bool hasMoved, std::string const &image, std::string const &display, int pieceScore) :
    team(team), pieceType(pieceType), pieceDirection(pieceDirection), hasMoved(hasMoved), image(image), display(display), pieceScore(pieceScore) {}

bool PieceInfo::operator==(PieceInfo const &other) const {
    return
        team == other.team &&
        pieceType == other.pieceType &&
        pieceDirection == other.pieceDirection &&
        hasMoved == other.hasMoved &&
        image == other.image &&
        display == other.display &&
        pieceScore == other.pieceScore;
}
