// GraphicObserver.h

#ifndef GraphicObserver_h
#define GraphicObserver_h

#include "Observer.h"
#include "Game.h"
#include "Window.h"
#include "Cloneable.h"
#include "ChessBoard.h"

class GraphicObserver : public Cloneable<Observer, GraphicObserver> {
private:
    Game *game;
    Xwindow window;
    void notifyImpl() override;
    void printPiece(const std::string& str, Team team, int x, int y);
    void printBoard(const ChessBoard& chessBoard, int turn);

public:
    explicit GraphicObserver(Game *game);
    GraphicObserver(GraphicObserver const &other);
    GraphicObserver(GraphicObserver &&other) noexcept;
    GraphicObserver& operator=(GraphicObserver const &other);
    GraphicObserver& operator=(GraphicObserver &&other) noexcept;
    ~GraphicObserver();
};


#endif /* GraphicObserver_h */
