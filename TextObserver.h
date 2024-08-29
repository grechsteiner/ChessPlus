// TextObserver.h

#ifndef TextObserver_h
#define TextObserver_h

#include <iostream>

#include "Observer.h"
#include "Game.h"

#include "ChessBoard.h"

class TextObserver : public Observer {
private:
    std::ostream& out;
    Game *game;
    void notifyImplementation() override;
    void printPiece(const std::string& str, Color color);
    void printBoard(ChessBoard const& board, int turn);
public:
    TextObserver(std::ostream &out, Game *game);
    ~TextObserver();
};

#endif /* TextObserver_h */
