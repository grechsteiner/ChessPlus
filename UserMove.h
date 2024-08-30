// UserMove.h

#ifndef UserMove_h
#define UserMove_h

#include <string>

#include "Constants.h"
#include "UserSquare.h"

class BoardMove;


class UserMove {

private:
    UserSquare fromSquare;
    UserSquare toSquare;
    PieceType promotionPieceType;

public:
    UserMove(UserSquare const &fromSquare, UserSquare const &toSquare, PieceType promotionPieceType = PieceType::EMPTY);

    UserMove(UserMove const &other);
    //UserMove(UserMove &&other);
    UserMove& operator=(UserMove const &other);
    //UserMove& operator=(UserMove &&other);
    ~UserMove() = default;

    std::string toString() const;
    UserSquare const& getFromSquare() const;
    UserSquare const& getToSquare() const;
    PieceType getPromotionPieceType() const;
};


#endif /* UserMove_h */
