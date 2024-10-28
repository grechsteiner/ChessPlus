// PieceData.cc

#include <string>
#include <utility>

#include "PieceData.h"
#include "Constants.h"


// Basic ctor
PieceData::PieceData(PieceType pieceType, Team team, PieceDirection pieceDirection, bool hasMoved, int pieceScore, std::string const &image, std::string const &display) :
    pieceType(pieceType), team(team), pieceDirection(pieceDirection), hasMoved(hasMoved), pieceScore(pieceScore), image(image), display(display) {}

// Move ctor
PieceData::PieceData(PieceData &&other) noexcept : 
    pieceType(other.pieceType), team(other.team), pieceDirection(other.pieceDirection), hasMoved(other.hasMoved), pieceScore(other.pieceScore), image(std::move(other.image)), display(std::move(other.display)) {}

// Move assignment
PieceData& PieceData::operator=(PieceData&& other) noexcept {
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
bool PieceData::operator==(PieceData const &other) const {
    return
        pieceType == other.pieceType &&
        team == other.team &&
        pieceDirection == other.pieceDirection &&
        hasMoved == other.hasMoved &&
        pieceScore == other.pieceScore &&
        image == other.image &&
        display == other.display;
}

PieceType PieceData::getPieceType() const { return pieceType; }
Team PieceData::getTeam() const { return team; }
PieceDirection PieceData::getPieceDirection() const { return pieceDirection; }
bool PieceData::getHasMoved() const { return hasMoved; }
int PieceData::getPieceScore() const { return pieceScore; }
std::string const& PieceData::getImage() const { return image; }
std::string const& PieceData::getDisplay() const { return display; }
