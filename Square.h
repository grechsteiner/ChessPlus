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

};


#endif /* Square_h */
