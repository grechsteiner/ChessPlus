// PieceData.h

#ifndef PieceData_h
#define PieceData_h

#include <string>

#include "Constants.h"


/**
 * PieceData Class
 * Represents all the data pertaining to a piece
 */
class PieceData final {

private:
    PieceType pieceType;
    Team team;
    PieceDirection pieceDirection;
    bool hasMoved;
    int pieceScore;
    std::string image;
    std::string display;

public:
    explicit PieceData(PieceType pieceType, Team team, PieceDirection pieceDirection, bool hasMoved, int pieceScore, std::string const &image, std::string const &display);
    PieceData(PieceData const &other) = default;
    PieceData(PieceData &&other) noexcept;
    PieceData& operator=(const PieceData& other) = default;
    PieceData& operator=(PieceData&& other) noexcept;
    ~PieceData() = default;

    bool operator==(PieceData const &other) const;

    PieceType getPieceType() const;
    Team getTeam() const;
    PieceDirection getPieceDirection() const;
    bool getHasMoved() const;
    int getPieceScore() const;
    std::string const& getImage() const;
    std::string const& getDisplay() const;
};


#endif /* PieceData_h */
