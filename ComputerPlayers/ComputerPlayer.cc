// ComputerPlayer.cc

#include <algorithm>
#include <random>
#include <chrono>

#include "Constants.h"
#include "ComputerPlayer.h"
#include "BoardMove.h"
#include "ChessBoard.h"

// Basic ctor
ComputerPlayer::ComputerPlayer(ChessBoard const &chessBoard, Team team) :
    chessBoard(chessBoard), team(team) {}

// Move ctor
ComputerPlayer::ComputerPlayer(ComputerPlayer &&other) noexcept :
    chessBoard(other.chessBoard), team(other.team) {}

void ComputerPlayer::shuffle(std::vector<std::unique_ptr<BoardMove>> &moves) const {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(moves.begin(), moves.end(), std::default_random_engine(seed));
}

std::unique_ptr<BoardMove> ComputerPlayer::generateMove() const { return generateMoveImpl(); }
std::unique_ptr<ComputerPlayer> ComputerPlayer::clone() const { return cloneImpl(); }

Team ComputerPlayer::getTeam() const { return team; }
