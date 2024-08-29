// BoardSquare.h

#ifndef BoardSquare_h
#define BoardSquare_h

#include <string>


class BoardSquare {

private:
    int boardRow;
    int boardCol;

public:
    BoardSquare(int boardRow, int boardCol);

    std::string toString() const;
    int getBoardRow() const;
    int getBoardCol() const;

    int getUserRow(int numRowsOnBoard) const;
    std::string getUserCol(int numColsOnBoard) const;
};


#endif /* BoardSquare_h */
