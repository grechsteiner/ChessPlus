// TextObserver.h

#ifndef TextObserver_h
#define TextObserver_h

#include <iostream>

#include "Observer.h"
#include "Game.h"
#include "ChessBoard.h"
#include "Cloneable.h"


class TextObserver : public Cloneable<Observer, TextObserver> {
private:
    std::ostream& out;
    Game *game;
    void notifyImpl() override;
    void printPiece(const std::string& str, Team color);
    void printBoard(ChessBoard const &chessBoard, int turn);
public:
    explicit TextObserver(std::ostream &out, Game *game);
    TextObserver(TextObserver const &other);
    TextObserver(TextObserver &&other) noexcept;
    // Copy assignment not enabled (can't copy streams)
    // Move assignment not enabled (can't move streams)
    ~TextObserver();
};

#endif /* TextObserver_h */
