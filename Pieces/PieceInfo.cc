// PieceInfo.cc

#include "PieceInfo.h"


/*
 * Basic ctor
 */
PieceInfo::PieceInfo(int pieceScore, char32_t image) :
    pieceScore(pieceScore), image(image) { }

/*
 * Copy ctor
 */
PieceInfo::PieceInfo(PieceInfo const &other) :
    pieceScore(other.pieceScore), image(other.image) { } 

/*
 * Move ctor
 */
PieceInfo::PieceInfo(PieceInfo &&other) noexcept : 
    pieceScore(other.pieceScore), image(other.image) { }

/*
 * Copy assignment
 */
PieceInfo& PieceInfo::operator=(const PieceInfo& other) {
    if (this != &other) {
        pieceScore = other.pieceScore;
        image = other.image;
    }
    return *this;
}

/*
 * Move assignment
 */
PieceInfo& PieceInfo::operator=(PieceInfo&& other) noexcept {
    if (this != &other) {
        pieceScore = other.pieceScore;
        image = other.image;
    }
    return *this;
}

/*
 * Equality
 */
bool PieceInfo::operator==(PieceInfo const &other) const {
    return
        pieceScore == other.pieceScore &&
        image == other.image;
}

/*
 * Inequality
 */
bool PieceInfo::operator!=(PieceInfo const &other) const {
    return !(*this == other);
}
