// UserSquare.h

#ifndef UserSquare_h
#define UserSquare_h

#include <string>
#include <regex>
#include <utility>


class UserSquare {

private:
    static std::regex const regexPattern;
    std::string userSquare;
    
public:
    UserSquare(std::string const &squareStr);
    static bool isValidUserSquare(std::string const &squareStr);

    std::string toString() const;
    int getUserRow() const;
    std::string getUserCol() const;

    int getGridRow(int numRowsOnGrid) const;
    int getGridCol(int numColsOnGrid) const;
};


#endif /* Square_h */
