// State.cc

#include "State.h"


// Basic ctor
State::State(GameState gameState, std::unique_ptr<ChessBoard> const &chessBoard, std::pair<Player, Player> const &players, Team currentTurn) :
    gameState(gameState), chessBoard(chessBoard), players(players), currentTurn(currentTurn) {}

// Copy ctor
State::State(State const &other) :
    gameState(other.gameState), chessBoard(other.chessBoard), players(other.players), currentTurn(other.currentTurn) {}

// Move ctor
State::State(State &&other) noexcept :
    gameState(other.gameState), chessBoard(std::move(other.chessBoard)), players(std::move(other.players)), currentTurn(other.currentTurn) {}
