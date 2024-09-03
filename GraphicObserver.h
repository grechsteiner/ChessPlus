// GraphicObserver.h

#ifndef GraphicObserver_h
#define GraphicObserver_h

#include "Observer.h"
#include "Game.h"
#include "Window.h"

#include "IChessBoard.h"

class GraphicObserver : public Observer {
private:
    Game *game;
    Xwindow window;
    void notifyImpl() override;
    void printPiece(const std::string& str, Team team, int x, int y);
    void printBoard(const IChessBoard& chessBoard, int turn);

public:
    GraphicObserver(Game *game);
    ~GraphicObserver();
};


#endif /* GraphicObserver_h */
