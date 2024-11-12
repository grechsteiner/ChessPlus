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

    void printPiece(const std::string& str, Team color);
    void printBoard(ChessBoard const &chessBoard, int turn);

public:
    explicit TextObserver(Game *game, std::ostream &out);
    TextObserver(TextObserver const &other);
    TextObserver(TextObserver &&other) noexcept;
    // Copy assignment not enabled (can't copy streams)
    // Move assignment not enabled (can't move streams)
    virtual ~TextObserver();
};

#endif /* TextObserver_h */
