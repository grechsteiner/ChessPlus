// PieceInfo.cc

#include <string>
#include <utility>

#include "PieceInfo.h"
#include "Constants.h"
#include "PieceData.h"


// Basic ctor
PieceInfo::PieceInfo(int pieceScore, char32_t image) :
    pieceScore(pieceScore), image(image) {}

// Move ctor
PieceInfo::PieceInfo(PieceInfo &&other) noexcept : 
    pieceScore(other.pieceScore), image(other.image) {}

// Move assignment
PieceInfo& PieceInfo::operator=(PieceInfo&& other) noexcept {
    if (this != &other) {
        pieceScore = other.pieceScore;
        image = other.image;
    }
    return *this;
}

// Equality operator
bool PieceInfo::operator==(PieceInfo const &other) const {
    return
        pieceScore == other.pieceScore &&
        image == other.image;
}
