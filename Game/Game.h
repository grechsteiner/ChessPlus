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
#include "MoveInputDetails.h"


class Game : public Subject {
private:

    GameState gameState;
    std::unique_ptr<ChessBoard> chessBoard;

    std::unique_ptr<CommandRetriever> commandRetriever;
    std::unique_ptr<IllegalCommandReporter> illegalCommandReporter;
    
    std::pair<Player, Player> players;
    Team currentTurn;

    Player const& getPlayer(Team team) const;
    void switchTurn();
    void resetGame();
    void setGameState(GameState newGameState);
    void reportIllegalCommand(std::string const &message) const;

    std::optional<std::string> matchToOptionalString(std::smatch const& matches, int index) const;

    void processEnterSetupModeCommand();
    void processPlacePieceCommand(std::string const &boardSquareStr, std::string const &pieceTypeStr, std::optional<std::string> const &pieceLevelStr, std::optional<std::string> const &pieceDirectionStr);
    void processRemovePieceCommand(std::string const &boardSquareStr);
    void processSwapFirstTurnCommand();
    void processApplyStandardSetupCommand();
    void processSetBoardSizeCommand(std::string const &numRowsStr, std::string const &numColsStr);
    void processExitSetupModeCommand();

    void processStartGameCommand(std::string const &teamOneStr, std::string const &teamTwoStr);
    void processMakeHumanMoveCommand(MoveInputDetails const &moveInputDetails);
    void processMakeComputerMoveCommand();
    void processUndoMoveCommand();
    void processResignGameCommand();

public:
    explicit Game(std::unique_ptr<CommandRetriever> commandRetriever, std::unique_ptr<IllegalCommandReporter> illegalCommandReporter);
    Game(Game const &other);
    Game(Game &&other) noexcept;
    Game& operator=(Game &other);
    Game& operator=(Game &&other) noexcept;
    virtual ~Game() = default;
    
    void runGame();

    using State = std::tuple<GameState, std::unique_ptr<ChessBoard> const&, std::pair<Player, Player> const&, Team>;
    State getState() const;
};

#endif /* Game_h */
