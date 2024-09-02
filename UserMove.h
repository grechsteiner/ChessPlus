// UserMove.h

#ifndef UserMove_h
#define UserMove_h

#include <string>
#include <optional>

#include "Constants.h"
#include "UserSquare.h"


/**
 * UserMove Class
 * Represents a move entered by a user
 */
class UserMove final {

private:
    UserSquare fromSquare;
    UserSquare toSquare;
    std::optional<PieceType> promotionPieceType;

public:
    explicit UserMove(UserSquare const &fromSquare, UserSquare const &toSquare, std::optional<PieceType> promotionPieceType = std::nullopt);
    UserMove(UserMove const &other) = default;
    UserMove(UserMove &&other) noexcept;
    UserMove& operator=(UserMove const &other) = default;
    UserMove& operator=(UserMove &&other) noexcept;
    ~UserMove() = default;

    bool operator==(UserMove const &other) const;
    std::string toString() const;

    UserSquare const& getFromSquare() const;
    UserSquare const& getToSquare() const;
    std::optional<PieceType> getPromotionPieceType() const;
};


#endif /* UserMove_h */
