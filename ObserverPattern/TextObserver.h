// TextObserver.h

#ifndef TextObserver_h
#define TextObserver_h

#include <iostream>
#include <memory>
#include <string>
#include <utility>

#include "ChessBoard.h"
#include "Constants.h"
#include "Game.h"
#include "Observer.h"
#include "Player.h"


/**
 * TextObserver Observer Class
 */
class TextObserver final : public Observer {
private:
    Game *game;
    std::ostream &out;

    void notifyImpl() override;

    void displayMainMenu();
    void displaySetupMode(std::unique_ptr<ChessBoard> const &chessBoard, std::pair<Player, Player> const &players, Team currentTurn);
    void displayGame(std::unique_ptr<ChessBoard> const &chessBoard, std::pair<Player, Player> const &players, Team currentTurn);

    std::vector<std::u32string> buildMainMenuText();
    std::vector<std::u32string> buildSetupText();
    std::vector<std::u32string> buildGameOnText();

    std::vector<std::u32string> buildChessBoard(std::unique_ptr<ChessBoard> const &chessBoard);
    std::vector<std::u32string> buildBoardDataText(std::unique_ptr<ChessBoard> const &chessBoard, Team currentTurn);
    std::vector<std::u32string> buildBoardStatusText(std::unique_ptr<ChessBoard> const &chessBoard, Team currentTurn);

    std::u32string stringToU32(std::string const &str) const;
    std::string u32ToString(std::u32string const &str) const;
    void outputLine(std::u32string const &line) const;

public:
    explicit TextObserver(Game *game, std::ostream &out);
    TextObserver(TextObserver const &other);
    TextObserver(TextObserver &&other) noexcept;
    TextObserver& operator=(TextObserver const &other) = delete;
    TextObserver& operator=(TextObserver &&other) = delete;
    virtual ~TextObserver();
};


#endif /* TextObserver_h */
