// UserSquare.h

#ifndef UserSquare_h
#define UserSquare_h

#include <string>
#include <regex>


/**
 * UserSquare Class
 * Represents a square as seen by a user on a typical chessboard
 */
class UserSquare final {

private:
    std::string userSquare;     // The UserSquare itself as entered by the user
    int userRow;                // The row parsed from the string (parse once at creation so not repeatedly parsing userSquare for getUserRow())
    std::string userCol;        // The col parsed from the string (parse once at creation so not repeatedly parsing userSquare for getUserCol())
    
public:
    explicit UserSquare(std::string const &squareStr);
    UserSquare(UserSquare const &other) = default;
    UserSquare(UserSquare &&other) noexcept;
    UserSquare& operator=(UserSquare const &other) = default;
    UserSquare& operator=(UserSquare &&other) noexcept;
    ~UserSquare() = default;

    bool operator==(UserSquare const &other) const;

    static bool isValidUserSquare(std::string const &squareStr);
    static std::regex getRegexPattern();

    std::string const& getUserSquare() const;
    int getUserRow() const;
    std::string const& getUserCol() const;
};


#endif /* Square_h */
