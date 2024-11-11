// Constants.h

#ifndef Constants_h
#define Constants_h

static int const KING_SCORE = std::numeric_limits<int>::max();

enum class GameState {
    MAIN_MENU,
    SETUP,
    GAME_ACTIVE
};

enum class PlayerType {
    HUMAN,
    COMPUTER
};

enum class ComputerPlayerLevel {
    ONE,
    TWO,
    THREE,
    FOUR,
    FIVE
};

enum class PieceType {
    KING,
    QUEEN,
    ROOK,
    KNIGHT,
    BISHOP,
    PAWN,
};

enum class PieceLevel {
    BASIC,
    ADVANCED,
};

enum class Team {
    TEAM_ONE,
    TEAM_TWO,
};

enum class PieceDirection {
    NORTH,
    SOUTH,
    EAST,
    WEST,
};


#endif /* Constants_h */
