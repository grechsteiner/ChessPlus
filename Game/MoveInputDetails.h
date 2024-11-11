// MoveInputDetails.h

#ifndef MoveInputDetails_h
#define MoveInputDetails_h

#include <optional>
#include <string>


struct MoveInputDetails final {
public:
    std::string fromSquareStr;
    std::string toSquareStr;
    std::optional<std::string> promotionPieceTypeStr;

    MoveInputDetails(std::string const &fromSquareStr, std::string const &toSquareStr, std::optional<std::string> const &promotionPieceTypeStr);
    MoveInputDetails(MoveInputDetails const &other);
    MoveInputDetails(MoveInputDetails &&other) noexcept;
    MoveInputDetails& operator=(MoveInputDetails &other);
    MoveInputDetails& operator=(MoveInputDetails &&other) noexcept;
    virtual ~MoveInputDetails() = default;
};


#endif /* MoveInputDetails_h */
