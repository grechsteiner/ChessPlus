// UserMove.h

#ifndef UserMove_h
#define UserMove_h

#include <string>

#include "Constants.h"
#include "UserSquare.h"


class UserMove {

private:
    UserSquare fromSquare;
    UserSquare toSquare;
    std::optional<PieceType> promotionPieceType;

public:
    UserMove(UserSquare const &fromSquare, UserSquare const &toSquare, std::optional<PieceType> promotionPieceType = std::nullopt);

    UserMove(UserMove const &other);
    UserMove(UserMove &&other);
    UserMove& operator=(UserMove const &other);
    UserMove& operator=(UserMove &&other);
    ~UserMove() = default;

    std::string toString() const;
    UserSquare getFromSquare() const;
    UserSquare getToSquare() const;
    std::optional<PieceType> getPromotionPieceType() const;
};


#endif /* UserMove_h */
