// Move.h

#ifndef Move_h
#define Move_h

#include <string>

#include "Constants.h"


class Move {

protected:
    int fromRow, toRow;
    char fromCol, toCol;
    PieceType promotionPieceType;

public:
    Move(std::string const &from, std::string const &to, std::string const &promotion = "");
    Move(int fromRow, char fromCol, int toRow, char toCol, std::string const &promotion = "");

    // ints are reflective of spot on board
    Move(int numVectorRows, int fromRow, int fromCol, int toRow, int toCol, PieceType promotionPieceType = PieceType::EMPTY);
                                                                                                          
    static bool isValidMoveSyntax(std::string const &from, std::string const &to, std::string const &promotion = "");

    std::string toString() const;

    // Alpha beta sentinel
    static const Move DEFAULT;

    // Getters
    int getFromRow() const;
    char getFromCol() const;
    int getToRow() const;
    char getToCol() const;
    PieceType getPromotionPieceType() const;

    // TODO: Maybe make private/protected???
    // TODO: Should these be part of board???
    int getVectorRow(int numVectorRows, int moveRow) const;
    int getVectorCol(char moveCol) const;
    int getStandardRow(int numVectorRows, int vectorRow) const;
    char getStandardCol(int vectorCol) const;

    bool operator==(const Move& other) const;
};


#endif /* Move_h */
