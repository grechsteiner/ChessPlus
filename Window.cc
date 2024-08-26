#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include <unistd.h>

#include "Window.h"


Xwindow::Xwindow(int width, int height) {

    display = XOpenDisplay(NULL);
    if (display == NULL) {
        std::cerr << "Cannot open display" << std::endl;
        exit(1);
    }
    screen = DefaultScreen(display);
    window = XCreateSimpleWindow(display, RootWindow(display, screen), 10, 10, width, height, 1, BlackPixel(display, screen), WhitePixel(display, screen));
    XSelectInput(display, window, ExposureMask | KeyPressMask);
    XMapRaised(display, window);

    Pixmap pixmap = XCreatePixmap(display, window, width, height, DefaultDepth(display, DefaultScreen(display)));
    gc = XCreateGC(display, pixmap, 0,(XGCValues *)0);

    XFlush(display);
    XFlush(display);

    // Set up colours.
    XColor xcolour;
    Colormap cmap;
    char color_vals[7][10] = {"white", "black", "red", "green", "blue"};

    cmap = DefaultColormap(display , DefaultScreen(display));
    for(int i=0; i < 5; ++i) {
        XParseColor(display, cmap, color_vals[i], &xcolour);
        XAllocColor(display, cmap, &xcolour);
        colours[i] = xcolour.pixel;
    }

    XSetForeground(display, gc,colours[Black]);

    // Make window non-resizeable.
    XSizeHints hints;
    hints.flags = (USPosition | PSize | PMinSize | PMaxSize );
    hints.height = hints.base_height = hints.min_height = hints.max_height = height;
    hints.width = hints.base_width = hints.min_width = hints.max_width = width;
    XSetNormalHints(display, window, &hints);

    XSynchronize(display,True);

    usleep(1000);
}

Xwindow::~Xwindow() {
    XFreeGC(display, gc);
    XCloseDisplay(display);
}

void Xwindow::fillRectangle(int x, int y, int width, int height, int colour) {
    XSetForeground(display, gc, colours[colour]);
    XFillRectangle(display, window, gc, x, y, width, height);
    XSetForeground(display, gc, colours[Black]);
}

void Xwindow::drawString(int x, int y, std::string msg, int colour) {
    XSetForeground(display, gc, colours[colour]);
    XDrawString(display, window, gc, x, y, msg.c_str(), msg.length());
}
