// TextObserver.h

#ifndef TextObserver_h
#define TextObserver_h

#include <boost/locale.hpp>

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
    // Copy assignment not enabled (can't copy streams)
    // Move assignment not enabled (can't move streams)
    virtual ~TextObserver();
};


#endif /* TextObserver_h */
