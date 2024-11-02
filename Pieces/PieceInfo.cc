// PieceInfo.cc

#include <string>
#include <utility>

#include "PieceInfo.h"
#include "Constants.h"
#include "PieceData.h"


// Basic ctor
PieceInfo::PieceInfo(int pieceScore, std::string const &image, std::string const &display) :
    pieceScore(pieceScore), image(image), display(display) {}

// Move ctor
PieceInfo::PieceInfo(PieceInfo &&other) noexcept : 
    pieceScore(other.pieceScore), image(std::move(other.image)), display(std::move(other.display)) {}

// Move assignment
PieceInfo& PieceInfo::operator=(PieceInfo&& other) noexcept {
    if (this != &other) {
        pieceScore = other.pieceScore;
        image = std::move(other.image);
        display = std::move(other.display);
    }
    return *this;
}

// Equality operator
bool PieceInfo::operator==(PieceInfo const &other) const {
    return
        pieceScore == other.pieceScore &&
        image == other.image &&
        display == other.display;
}
