// TextObserver.h

#ifndef TextObserver_h
#define TextObserver_h

#include <iostream>

#include "Observer.h"
#include "Game.h"

#include "IChessBoard.h"

class TextObserver : public Observer {
private:
    std::ostream& out;
    Game *game;
    void notifyImpl() override;
    void printPiece(const std::string& str, Team color);
    void printBoard(IChessBoard const &chessBoard, int turn);
public:
    TextObserver(std::ostream &out, Game *game);
    ~TextObserver();
};

#endif /* TextObserver_h */
