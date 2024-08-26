// Constants.h

#ifndef Constants_h
#define Constants_h

#include <string>
#include <utility>
#include <vector>


enum class GameState {
    MAIN_MENU,
    SETUP,
    GAME_ACTIVE
};

enum class Color {
    WHITE,
    BLACK,
    NONE
};
extern const std::vector<std::pair<Color, std::string>> colorStringMap;
bool isValidColor(std::string const &str);
Color stringToColor(std::string const &str);
std::string colorToString(Color color);

enum class PieceType {
    KING,
    QUEEN,
    ROOK,
    KNIGHT,
    BISHOP,
    PAWN,
    EMPTY
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
    BLANK
};
extern const std::vector<std::pair<PieceDirection, std::string>> pieceDirectionStringMap;
bool isValidPieceDirection(std::string const &str);
PieceDirection stringToPieceDirection(std::string const &str);
std::string pieceDirectionToString(PieceDirection pieceDirection);


std::string toLower(std::string const &str);
std::string toUpper(std::string const &str);
bool isInt(std::string const &str);

int min(int a, int b);

// TODO: Can probably remove
enum class MoveType {
    STANDARD,
    CASTLE,
    ENPASSANT,
    DOUBLE_PAWN
};

#endif /* Constants_h */
