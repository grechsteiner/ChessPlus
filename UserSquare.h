// UserSquare.h

#ifndef UserSquare_h
#define UserSquare_h

#include <string>
#include <regex>
#include <utility>

class BoardSquare;


class UserSquare {

private:
    std::string userSquare;

    // For convenience: userSquare = userCol + to_string(userRow)
    int userRow;
    std::string userCol;
    
public:
    UserSquare(std::string const &squareStr);
    bool operator==(UserSquare const &other) const;
    static bool isValidUserSquare(std::string const &squareStr);

    std::string toString() const;
    int getUserRow() const;
    std::string getUserCol() const;

    int getBoardRow(int numRowsOnBoard) const;
    int getBoardCol(int numColsOnBoard) const;

    bool isEqualToBoardSquare(BoardSquare const &boardSquare, int numRowsOnBoard, int numColsOnBoard) const;
    BoardSquare toBoardSquare(int numRowsOnBoard, int numColOnBoard) const;
};


#endif /* Square_h */
