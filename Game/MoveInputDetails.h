// MoveInputDetails.h

#ifndef MoveInputDetails_h
#define MoveInputDetails_h

#include <optional>
#include <string>


/**
 * MoveInputDetails Struct
 * Represents the data inputted by a Human to make a move
 */
struct MoveInputDetails final {
    std::string fromSquareStr;
    std::string toSquareStr;
    std::optional<std::string> promotionPieceTypeStr;

    MoveInputDetails(std::string const &fromSquareStr, std::string const &toSquareStr, std::optional<std::string> const &promotionPieceTypeStr);
    MoveInputDetails(MoveInputDetails const &other);
    MoveInputDetails(MoveInputDetails &&other) noexcept;
    MoveInputDetails& operator=(MoveInputDetails &other);
    MoveInputDetails& operator=(MoveInputDetails &&other) noexcept;
    virtual ~MoveInputDetails() = default;

    bool operator==(MoveInputDetails const &other) const;
    bool operator!=(MoveInputDetails const &other) const;
};


#endif /* MoveInputDetails_h */
