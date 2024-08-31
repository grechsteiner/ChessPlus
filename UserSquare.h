// UserSquare.h

#ifndef UserSquare_h
#define UserSquare_h

#include <string>
#include <regex>
#include <utility>


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
};


#endif /* Square_h */
