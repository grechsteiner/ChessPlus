// TextObserver.h

#ifndef TextObserver_h
#define TextObserver_h

#include <iostream>

#include "Observer.h"
#include "Game.h"
#include "ChessBoard.h"
#include "Cloneable.h"


class TextObserver final : public Cloneable<Observer, TextObserver> {
private:
    Game *game;
    std::ostream &out;

    void notifyImpl() override;

    void displayMainMenu();
    void displaySetupMode(std::unique_ptr<ChessBoard> const &chessBoard, std::pair<Player, Player> const &players, Team currentTurn);
    void displayGame(std::unique_ptr<ChessBoard> const &chessBoard, std::pair<Player, Player> const &players, Team currentTurn);

    std::vector<std::string> buildChessBoard(std::unique_ptr<ChessBoard> const &chessBoard);
    std::vector<std::string> buildSetupText();
    std::vector<std::string> buildBoardDataText(std::unique_ptr<ChessBoard> const &chessBoard, Team currentTurn);

public:
    explicit TextObserver(Game *game, std::ostream &out);
    TextObserver(TextObserver const &other);
    TextObserver(TextObserver &&other) noexcept;
    // Copy assignment not enabled (can't copy streams)
    // Move assignment not enabled (can't move streams)
    virtual ~TextObserver();
};

#endif /* TextObserver_h */
