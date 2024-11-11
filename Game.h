// Game.h

#ifndef Game_h
#define Game_h

#include <iostream>
#include <memory>
#include <utility>
#include <tuple>

#include "Constants.h"
#include "Subject.h"
#include "ChessBoardImpl.h"
#include "CommandRetriever.h"
#include "IllegalCommandReporter.h"
#include "ComputerPlayer.h"
#include "Player.h"
#include "ChessBoard.h"


class Game : public Subject {
private:

    GameState gameState;
    std::unique_ptr<ChessBoard> chessBoard;

    std::unique_ptr<CommandRetriever> commandRetriever;
    std::unique_ptr<IllegalCommandReporter> illegalCommandReporter;
    
    std::pair<Player, Player> players;
    Team currentTurn;

    void switchTurn();
    Player const& getPlayer(Team team) const;
    void resetGame();

    void setGameState(GameState newGameState);
    bool isInMainMenuGameState() const;
    bool isInSetupGameState() const;
    bool isInActiveGameState() const;

    void reportIllegalCommand(std::string const &message) const;



    bool showingStandardOpenings = false;


public:
    explicit Game(std::unique_ptr<CommandRetriever> commandRetriever, std::unique_ptr<IllegalCommandReporter> illegalCommandReporter);
    Game(Game const &other);
    Game(Game &&other) noexcept;
    Game& operator=(Game &other);
    Game& operator=(Game &&other) noexcept;
    virtual ~Game() = default;
    
    void runGame();

    using State = std::tuple<GameState, std::unique_ptr<ChessBoard> const&, std::pair<Player, Player> const&, Team>;
    State getGameState() const;
};

#endif /* Game_h */
