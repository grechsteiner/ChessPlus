// State.h

#ifndef State_h
#define State_h

#include <memory>
#include <utility>

#include "Constants.h"
#include "ChessBoard.h"
#include "Player.h"


/**
 * State Struct
 * The data to be passed to observers
 */
struct State final {
    GameState gameState;
    std::unique_ptr<ChessBoard> const &chessBoard;
    std::pair<Player, Player> const &players;
    Team currentTurn;

    State(GameState gameState, std::unique_ptr<ChessBoard> const &chessBoard, std::pair<Player, Player> const &players, Team currentTurn);
    State(State const &other);
    State(State &&other) noexcept;
    State& operator=(State &other) = delete;
    State& operator=(State &&other) = delete;
    virtual ~State() = default;
};


#endif /* State_h */
    
