// Constants.h

#ifndef Constants_h
#define Constants_h

#include <string>
#include <utility>
#include <vector>

struct BoardSquare;
class BoardMove;
class UserSquare;
class UserMove;


// TODO
enum class PieceLevel {
    BASIC,
    ADVANCED,
};


// TODO
enum class ComputerPlayerLevel {
    ONE,
    TWO,
    THREE,
    FOUR,
    FIVE
};


static int const KingScore = 1000;

enum class GameState {
    MAIN_MENU,
    SETUP,
    GAME_ACTIVE
};

enum class Team {
    TEAM_ONE,
    TEAM_TWO,
};
extern const std::vector<std::pair<Team, std::string>> colorStringMap;
bool isValidColor(std::string const &str);
Team stringToColor(std::string const &str);
std::string colorToString(Team color);

enum class PieceType {
    KING,
    QUEEN,
    ROOK,
    KNIGHT,
    BISHOP,
    PAWN,
};
extern const std::vector<std::pair<PieceType, std::string>> pieceTypeStringMap;
bool isValidPieceType(std::string const &str);
PieceType stringToPieceType(std::string const &str);
std::string pieceTypeToString(PieceType pieceType);

enum class PieceDirection {
    NORTH,
    SOUTH,
    EAST,
    WEST,
};
extern const std::vector<std::pair<PieceDirection, std::string>> pieceDirectionStringMap;
bool isValidPieceDirection(std::string const &str);
PieceDirection stringToPieceDirection(std::string const &str);
std::string pieceDirectionToString(PieceDirection pieceDirection);


std::string toLower(std::string const &str);
std::string toUpper(std::string const &str);
bool isInt(std::string const &str);

int min(int a, int b);



extern int const base;
BoardSquare createBoardSquare(UserSquare const &userSquare, int numRowsOnBoard, int numColsOnBoard);
UserSquare createUserSquare(BoardSquare const &boardSquare, int numRowsOnBoard, int numColsOnBoard);
bool areEqual(UserSquare const &userSquare, BoardSquare const &boardSquare, int numRowsOnBoard, int numColsOnBoard);
bool areEqual(UserMove const &userMove, std::unique_ptr<BoardMove> const &boardMove, int numRowsOnBoard, int numColsOnBoard);


#endif /* Constants_h */
