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
    bool operator==(BoardSquare const &other) const;

    int getBoardRow() const;
    int getBoardCol() const;
};


#endif /* BoardSquare_h */
