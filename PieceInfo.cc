// PieceInfo.cc

#include <string>
#include <utility>

#include "PieceInfo.h"
#include "Constants.h"
#include "PieceData.h"


// Basic ctor
PieceInfo::PieceInfo(PieceData const &pieceData, int pieceScore, std::string const &image, std::string const &display) :
    pieceData(pieceData), pieceScore(pieceScore), image(image), display(display) {}

// Move ctor
PieceInfo::PieceInfo(PieceInfo &&other) noexcept : 
    pieceData(std::move(other.pieceData)), pieceScore(other.pieceScore), image(std::move(other.image)), display(std::move(other.display)) {}

// Move assignment
PieceInfo& PieceInfo::operator=(PieceInfo&& other) noexcept {
    if (this != &other) {
        pieceData = std::move(other.pieceData);
        pieceScore = other.pieceScore;
        image = std::move(other.image);
        display = std::move(other.display);
    }
    return *this;
}

// Equality operator
bool PieceInfo::operator==(PieceInfo const &other) const {
    return
        pieceData == other.pieceData &&
        pieceScore == other.pieceScore &&
        image == other.image &&
        display == other.display;
}
