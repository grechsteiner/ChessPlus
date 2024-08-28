// UserEnteredMove.h

#ifndef UserEnteredMove_h
#define UserEnteredMove_h

#include <string>

#include "Constants.h"


class UserEnteredMove {

private:
    int fromRow, toRow;                 // 1: bottom row
    std::string fromCol, toCol;         // a: leftmost col
    std::string promotionPiece;

public:
    UserEnteredMove(std::string const &fromSquare, std::string const &toSquare, std::string const &promotionPiece = "");

    UserEnteredMove(UserEnteredMove const &other);
    UserEnteredMove(UserEnteredMove &&other);
    UserEnteredMove& operator=(UserEnteredMove const &other);
    UserEnteredMove& operator=(UserEnteredMove &&other);
    ~UserEnteredMove() = default;

    static bool isValidSyntax(std::string const &fromSquare, std::string const &toSquare, std::string const &promotionPiece = "");
    std::string toString() const;   // TODO: Probably not needed --> Needed for trie


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
