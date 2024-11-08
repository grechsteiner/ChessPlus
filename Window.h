// Window.h

#ifndef Window_h
#define Window_h

#include <X11/Xlib.h>
#include <iostream>
#include <string>


class Xwindow {

private:
    Display *display;
    Window window;
    int screen;
    GC gc;
    unsigned long colours[10];

public:
    Xwindow(int width = 600, int height = 600);       
    ~Xwindow();                                   
    // Xwindow(Xwindow const &xwindow) = delete; // TODO: Does this need to be deleted for some reason
    // Xwindow &operator=(Xwindow const &xwindow) = delete; // TODO: Does this need to be deleted for some reason

    enum {
        White=0, 
        Black, 
        Red, 
        Green, 
        Blue
    };

    // Draws a rectangle
    void fillRectangle(int x, int y, int width, int height, int colour=Black);

    // Draws a string
    void drawString(int x, int y, std::string msg, int colour=Black);

};

#endif /* Window_h */
