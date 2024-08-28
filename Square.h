// Square.h

#ifndef Square_h
#define Square_h

#include <string>
#include <regex>
#include <utility>


class Square {

private:
    static std::regex const regexPattern;
    
public:

    // TODO: Many overloads
    static bool isValidSquare(std::string const &squareStr);

    // TODO: Many overloads
    static std::pair<int, std::string> getRowAndCol(std::string const &squareStr);

    // TODO: Many overloads
    static int getRow(std::string const &squareStr);

    // TODO: Many overloads
    static std::string getCol(std::string const &squareStr);

    // TODO: Many overloads
    static std::pair<int, int> getGridRowAndCol(std::string const &squareStr, int numRows, int numCols);

    static int getGridRow(int squareRow, int numRows);
    static int getGridCol(std::string const &squareStr, int numCols);

};


#endif /* Square_h */
