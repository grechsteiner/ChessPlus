// PieceInfo.cc

#include <string>
#include <utility>

#include "PieceInfo.h"
#include "Constants.h"


// Basic ctor
PieceInfo::PieceInfo(PieceType pieceType, Team team, PieceDirection pieceDirection, bool hasMoved, int pieceScore, std::string const &image, std::string const &display) :
    pieceType(pieceType), team(team), pieceDirection(pieceDirection), hasMoved(hasMoved), pieceScore(pieceScore), image(image), display(display) {}

// Move ctor
PieceInfo::PieceInfo(PieceInfo &&other) noexcept : 
    pieceType(other.pieceType), team(other.team), pieceDirection(other.pieceDirection), hasMoved(other.hasMoved), pieceScore(other.pieceScore), image(std::move(other.image)), display(std::move(other.display)) {}

// Move assignment
PieceInfo& PieceInfo::operator=(PieceInfo&& other) noexcept {
    if (this != &other) {
        pieceType = other.pieceType;
        team = other.team;
        pieceDirection = other.pieceDirection;
        hasMoved = other.hasMoved;
        pieceScore = other.pieceScore;
        image = std::move(other.image);
        display = std::move(other.display);
    }
    return *this;
}

// Equality operator
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

PieceType PieceInfo::getPieceType() const { return pieceType; }
Team PieceInfo::getTeam() const { return team; }
PieceDirection PieceInfo::getPieceDirection() const { return pieceDirection; }
bool PieceInfo::getHasMoved() const { return hasMoved; }
int PieceInfo::getPieceScore() const { return pieceScore; }
std::string const& PieceInfo::getImage() const { return image; }
std::string const& PieceInfo::getDisplay() const { return display; }
