// Constants.h

#ifndef Constants_h
#define Constants_h

#include <limits>


/**
 * Global Constants
 */


/*
 * The score assigned to Pieces of PieceType KING
 */
static int const KING_SCORE = std::numeric_limits<int>::max();

/*
 * The different possible states the game can be in
 */
enum class GameState {
    MAIN_MENU,
    SETUP,
    GAME_ACTIVE
};

/*
 * The different types of Players
 */
enum class PlayerType {
    HUMAN,
    COMPUTER
};

/*
 * The different levels of computer players
 */
enum class ComputerPlayerLevel {
    ONE,
    TWO,
    THREE,
    FOUR,
    FIVE
};

/*
 * The different types of Pieces
 */
enum class PieceType {
    KING,
    QUEEN,
    ROOK,
    KNIGHT,
    BISHOP,
    PAWN,
};

/*
 * The different levels of Pieces
 */
enum class PieceLevel {
    BASIC,
    ADVANCED,
};

/*
 * The different teams involved in the game
 */
enum class Team {
    TEAM_ONE,
    TEAM_TWO,
};

/*
 * The different primary directions a Piece can travel in
 */
enum class PieceDirection {
    NORTH,
    SOUTH,
    EAST,
    WEST,
};


#endif /* Constants_h */
