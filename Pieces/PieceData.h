// PieceData.h

#ifndef PieceData_h
#define PieceData_h

#include <string>

#include "Constants.h"


/**
 * PieceData Struct
 * Represents all the data pertaining to a piece that is modifiable at construction time
 */
struct PieceData final {
    PieceType pieceType;
    PieceLevel pieceLevel;
    Team team;
    PieceDirection pieceDirection;
    bool hasMoved;

    explicit PieceData(PieceType pieceType, PieceLevel pieceLevel, Team team, PieceDirection pieceDirection, bool hasMoved);
    PieceData(PieceData const &other) = default;
    PieceData(PieceData &&other) noexcept;
    PieceData& operator=(const PieceData& other) = default;
    PieceData& operator=(PieceData&& other) noexcept;
    ~PieceData() = default;

    bool operator==(PieceData const &other) const;
};


#endif /* PieceData_h */
