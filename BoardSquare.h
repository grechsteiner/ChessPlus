// BoardSquare.h

#ifndef BoardSquare_h
#define BoardSquare_h

#include <string>

class UserSquare;


class BoardSquare {

private:
    int boardRow;
    int boardCol;

public:
    BoardSquare(int boardRow, int boardCol);
    bool operator==(BoardSquare const &other) const;

    int getBoardRow() const;
    int getBoardCol() const;

    int getUserRow(int numRowsOnBoard) const;
    std::string getUserCol(int numColsOnBoard) const;

    bool isEqualToUserSquare(UserSquare const &userSquare, int numRowsOnBoard, int numColsOnBoard) const;
    UserSquare toUserSquare(int numRowsOnBoard, int numColOnBoard) const;
};


#endif /* BoardSquare_h */
