// UserEnteredMove.h

#ifndef UserEnteredMove_h
#define UserEnteredMove_h

#include <string>

#include "Constants.h"


class UserEnteredMove {

private:
    int const fromRow, toRow;                 // 1: bottom row
    std::string const fromCol, toCol;         // a: leftmost col
    std::string const promotionPiece;

public:
    UserEnteredMove(std::string const &fromSquare, std::string const &toSquare, std::string const &promotionPiece = "");

    UserEnteredMove(UserEnteredMove const &other);
    UserEnteredMove(UserEnteredMove &&other);
    UserEnteredMove& operator=(UserEnteredMove const &other) = delete;
    UserEnteredMove& operator=(UserEnteredMove &&other) = delete;
    ~UserEnteredMove() = default;

    static bool isValidSyntax(std::string const &fromSquare, std::string const &toSquare, std::string const &promotionPiece = "");
    std::string toString() const;   // TODO: Probably not needed


    /* Getters */

    // Squares
    int getFromRow() const;
    int getToRow() const;
    std::string const& getFromCol() const;
    std::string const& getToCol() const;

    // General Info
    std::string const& getPromotionPiece() const;
};


#endif /* UserEnteredMove_h */
