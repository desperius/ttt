#ifdef __linux__

#include "tttLinWindow.h"

#include <iostream>

tttLinWindow::~tttLinWindow()
{
    XDestroyWindow(mDisplay, mWindow);
    XFree(mScreen);
    XCloseDisplay(mDisplay);
}

bool tttLinWindow::Create(const char* title, bool fullscreen, unsigned width, unsigned height)
{
    (void)title;
    (void)fullscreen;
    (void)width;
    (void)height;
    
    mDisplay = XOpenDisplay(nullptr);
    
    if (!mDisplay)
    {
        std::cout << "Could not open display\n";
    }
    
    mScreen = DefaultScreenOfDisplay(mDisplay);
    mScreenID = DefaultScreen(mDisplay);
    Window parent = RootWindowOfScreen(mScreen);
    ulong border = BlackPixel(mDisplay, mScreenID);
    ulong background = WhitePixel(mDisplay, mScreenID);
    
    // Open the window
    mWindow = XCreateSimpleWindow(mDisplay, parent, 0, 0, 400, 300, 1, border, background);
    
    // Show the window
    XClearWindow(mDisplay, mWindow);
    XMapRaised(mDisplay, mWindow);
    
    return true;
}

int tttLinWindow::Exec()
{
    // Enter message loop
    while (true)
    {
        XNextEvent(mDisplay, mEvent);
    }
    
    return 0;
}

#endif /* __linux__ */
