// Game.h

#ifndef Game_h
#define Game_h

#include <iostream>
#include <memory>
#include <utility>
#include <tuple>

#include "Constants.h"
#include "Subject.h"
#include "Board.h"
#include "Input.h"
#include "ErrorReporter.h"
#include "ComputerPlayer.h"
#include "ChessBoard.h"
#include "ChessBoard.h"

// (Color, totalScore, ComputerPlayer)
using PlayerTuple = std::tuple<Team, double, std::unique_ptr<ComputerPlayer>>;

class Game : public Subject {
private:
    ChessBoard &board;      // TODO: Can be smart pointer too
    std::unique_ptr<Input> input;
    std::unique_ptr<ErrorReporter> errorReporter;
    std::ostream &out;

    GameState gameState = GameState::MAIN_MENU;
    

    bool showingStandardOpenings = false;

    std::tuple<PlayerTuple, PlayerTuple> players = std::make_tuple(
        std::make_tuple(Team::TEAM_ONE,  0,  nullptr),
        std::make_tuple(Team::TEAM_TWO,  0,  nullptr));
    

    void outputError(std::string const &errorMessage) const;
    int currentTurn = 0;
    void incrementTurn();
    void decrementTurn();

    void resetComputerPlayers();
    void applyStalematePoints();
    void applyWinPoints(Team team);

    PlayerTuple& getPlayerWithTurn(int i);

    void setGameState(GameState newGameState);
    bool isInMainMenu() const;
    bool isInSetupMode() const;
    bool isGameActive() const;

    void applyStandardSetup();
    bool isBoardInProperSetup() const;


public:
    Game(ChessBoard &board, std::istream &in, std::ostream &out, std::ostream &errorOut);
    void runGame();


    // Get state (observer pattern)
    GameState getGameState() const;
    const std::tuple<PlayerTuple, PlayerTuple>& getMainMenuState() const;
    std::tuple<const ChessBoard&, const std::tuple<PlayerTuple, PlayerTuple>&, int> getSetupState() const;
    std::tuple<const ChessBoard&, const std::tuple<PlayerTuple, PlayerTuple>&, int, bool> getActiveGameState() const;
};

#endif /* Game_h */
