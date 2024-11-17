// PieceData.cc

#include "PieceData.h"

#include "Constants.h"


/*
 * Basic ctor
 */
PieceData::PieceData(PieceType pieceType, PieceLevel pieceLevel, Team team, PieceDirection pieceDirection, bool hasMoved) :
    pieceType(pieceType), pieceLevel(pieceLevel), team(team), pieceDirection(pieceDirection), hasMoved(hasMoved) { }

/*
 * Copy ctor
 */
PieceData::PieceData(PieceData const &other) :
    pieceType(other.pieceType), pieceLevel(other.pieceLevel), team(other.team), pieceDirection(other.pieceDirection), hasMoved(other.hasMoved) { }

/*
 * Move ctor
 */
PieceData::PieceData(PieceData &&other) noexcept : 
    pieceType(other.pieceType), pieceLevel(other.pieceLevel), team(other.team), pieceDirection(other.pieceDirection), hasMoved(other.hasMoved) { }

/*
 * Copy assignment
 */
PieceData& PieceData::operator=(const PieceData& other) {
    if (this != &other) {
        pieceType = other.pieceType;
        pieceLevel = other.pieceLevel;
        team = other.team;
        pieceDirection = other.pieceDirection;
        hasMoved = other.hasMoved;
    }
    return *this;
}

/*
 * Move assignment
 */
PieceData& PieceData::operator=(PieceData&& other) noexcept {
    if (this != &other) {
        pieceType = other.pieceType;
        pieceLevel = other.pieceLevel;
        team = other.team;
        pieceDirection = other.pieceDirection;
        hasMoved = other.hasMoved;
    }
    return *this;
}

/*
 * Equality
 */
bool PieceData::operator==(PieceData const &other) const {
    return
        pieceType == other.pieceType &&
        pieceLevel == other.pieceLevel &&
        team == other.team &&
        pieceDirection == other.pieceDirection &&
        hasMoved == other.hasMoved;
}

/*
 * Inequality
 */
bool PieceData::operator!=(PieceData const &other) const {
    return !(*this == other);
}
