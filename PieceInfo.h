// PieceInfo.h

#ifndef PieceInfo_h
#define PieceInfo_h

#include <string>

#include "Constants.h"


/**
 * PieceInfo Class
 * Represents all the data pertaining to a piece
 */
class PieceInfo final {

private:
    PieceType pieceType;
    Team team;
    PieceDirection pieceDirection;
    bool hasMoved;
    int pieceScore;
    std::string image;
    std::string display;

public:
    explicit PieceInfo(PieceType pieceType, Team team, PieceDirection pieceDirection, bool hasMoved, int pieceScore, std::string const &image, std::string const &display);
    PieceInfo(PieceInfo const &other) = default;
    PieceInfo(PieceInfo &&other) noexcept;
    PieceInfo& operator=(const PieceInfo& other) = default;
    PieceInfo& operator=(PieceInfo&& other) noexcept;
    ~PieceInfo() = default;

    bool operator==(PieceInfo const &other) const;

    PieceType getPieceType() const;
    Team getTeam() const;
    PieceDirection getPieceDirection() const;
    bool getHasMoved() const;
    int getPieceScore() const;
    std::string const& getImage() const;
    std::string const& getDisplay() const;
};


#endif /* PieceInfo_h */
