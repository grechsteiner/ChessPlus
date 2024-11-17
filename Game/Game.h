// Game.h

#ifndef Game_h
#define Game_h

#include <memory>
#include <optional>
#include <regex>
#include <string>
#include <utility>

#include "ChessBoard.h"
#include "CommandRetriever.h"
#include "Constants.h"
#include "IllegalCommandReporter.h"
#include "MoveInputDetails.h"
#include "Player.h"
#include "State.h"
#include "Subject.h"


/**
 * Game Subject Class
 * Represents the game logic itself
 */
class Game final : public Subject {
private:
    GameState gameState;

    std::unique_ptr<ChessBoard> chessBoard;
    std::pair<Player, Player> players;
    Team currentTurn;

    std::unique_ptr<CommandRetriever> commandRetriever;
    std::unique_ptr<IllegalCommandReporter> illegalCommandReporter;
    
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
    void processApplyStandardSetupCommand(std::optional<std::string> const &pieceLevelStr);
    void processSetBoardSizeCommand(std::string const &numRowsStr, std::string const &numColsStr);
    void processExitSetupModeCommand();

    void processStartGameCommand(std::string const &teamOneStr, std::string const &teamTwoStr);
    void processMakeHumanMoveCommand(MoveInputDetails const &moveInputDetails);
    void processMakeComputerMoveCommand();
    void processUndoMoveCommand();
    void processRedoMoveCommand();
    void processResignGameCommand();

public:
    explicit Game(std::unique_ptr<CommandRetriever> const &commandRetriever, std::unique_ptr<IllegalCommandReporter> const &illegalCommandReporter);
    Game(Game const &other);
    Game(Game &&other) noexcept;
    Game& operator=(Game &other);
    Game& operator=(Game &&other) noexcept;
    virtual ~Game() = default;
    
    void runGame();

    State getState() const;
};


#endif /* Game_h */
