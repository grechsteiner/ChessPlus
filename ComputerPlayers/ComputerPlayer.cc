// ComputerPlayer.cc

#include "ComputerPlayer.h"

#include <algorithm>
#include <chrono>
#include <memory>
#include <random>
#include <vector>

#include "BoardMove.h"
#include "ChessBoard.h"
#include "Constants.h"


// Basic ctor
ComputerPlayer::ComputerPlayer(Team team) :
    team(team) { }

// Copy ctor
ComputerPlayer::ComputerPlayer(ComputerPlayer const &other) :
    team(other.team) { }

// Move ctor
ComputerPlayer::ComputerPlayer(ComputerPlayer &&other) noexcept :
    team(other.team) { }

// Copy assignment
ComputerPlayer& ComputerPlayer::operator=(ComputerPlayer &other) {
    if (this != &other) {
        team = other.team;
    }
    return *this;
}

// Move assignment
ComputerPlayer& ComputerPlayer::operator=(ComputerPlayer &&other) noexcept {
    if (this != &other) {
        team = other.team;
    }
    return *this;
}

/*
 * Shuffle the BoardMoves
 */
void ComputerPlayer::shuffle(std::vector<std::unique_ptr<BoardMove>> &moves) const {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(moves.begin(), moves.end(), std::default_random_engine(seed));
}

/* Public Virtual Methods */
std::unique_ptr<BoardMove> ComputerPlayer::generateMove(std::unique_ptr<ChessBoard> const &chessBoard) const { return generateMoveImpl(chessBoard); }
std::unique_ptr<ComputerPlayer> ComputerPlayer::clone() const { return cloneImpl(); }

/* Getters */
Team ComputerPlayer::getTeam() const { return team; }
