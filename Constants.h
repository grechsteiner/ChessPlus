// Constants.h

#ifndef Constants_h
#define Constants_h

#include <string>
#include <utility>
#include <vector>
#include <map>
#include <regex>

struct BoardSquare;
class BoardMove;
class UserMove;



// TODO
enum class CommandType {
    START_GAME,
    ENTER_SETUP_MODE,
    EXIT_SETUP_MODE,
    MAKE_MOVE,
    UNDO_MOVE,
    RESIGN_GAME,
    PLACE_PIECE,
    REMOVE_PIECE,
    SWITCH_TURN,
    APPLY_STANDARD_SETUP,
    CREATE_BOARD
};

std::map<CommandType, std::regex> commandPatterns = {
    { CommandType::START_GAME, std::regex(R"(\s*game\s*(human|computer[1-5])\s*(human|computer[1-5])\s*)") },
    { CommandType::ENTER_SETUP_MODE, std::regex(R"(\s*setup\s*)") },
    { CommandType::EXIT_SETUP_MODE, std::regex(R"(\s*done\s*)") },
    { CommandType::MAKE_MOVE, std::regex(R"(\s*move\s*(?:([a-z]+[1-9][0-9]*)\s*([a-z]+[1-9][0-9]*)\s*([a-z]?)\s*)?)") },
    { CommandType::UNDO_MOVE, std::regex(R"(\s*undo\s*)") },
    { CommandType::RESIGN_GAME, std::regex(R"(\s*resign\s*)") },
    { CommandType::PLACE_PIECE, std::regex(R"(\s*+\s*([a-z]+[1-9][0-9]*)\s*([a-zA-Z])\s*(basic|advanced)?\s*(north|south|west|east)?\s*)") },
    { CommandType::REMOVE_PIECE, std::regex(R"(\s*-\s*([a-z]+[1-9][0-9]*)\s*)") },
    { CommandType::SWITCH_TURN, std::regex(R"(\s*switch\s*)") },
    { CommandType::APPLY_STANDARD_SETUP, std::regex(R"(\s*standard\s*)") },
    { CommandType::CREATE_BOARD, std::regex(R"(\s*set\s*([1-9][0-9]*)\s*([1-9][0-9]*))") }
};


// TODO
enum class PieceLevel {
    BASIC,
    ADVANCED,
};

PieceLevel stringToPieceLevel(std::string const &str);


// TODO
enum class ComputerPlayerLevel {
    ONE,
    TWO,
    THREE,
    FOUR,
    FIVE
};

ComputerPlayerLevel stringToComputerPlayerLevel(std::string const &str);


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


#endif /* Constants_h */
