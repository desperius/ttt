#ifdef __linux__

#include "tttLinWindow.h"

#include <X11/Xutil.h>
#include <X11/keysymdef.h>

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
    
    XSelectInput(mDisplay, mWindow, KeyPressMask | KeyReleaseMask | KeymapStateMask);
    
    // Show the window
    XClearWindow(mDisplay, mWindow);
    XMapRaised(mDisplay, mWindow);
    
    return true;
}

int tttLinWindow::Exec()
{
    char str[32] = {0};
    KeySym keysym = 0;
    int len = 0;
    bool running = true;
    XEvent ev;
    
    // Enter message loop
    while (running)
    {
        XNextEvent(mDisplay, &ev);
        
        switch (ev.type)
        {
            case KeymapNotify:
            {
                XRefreshKeyboardMapping(&ev.xmapping);
                break;
            }
            
            case KeyPress:
            {
                len = XLookupString(&ev.xkey, str, sizeof(str), &keysym, nullptr);
                
                if (len > 0)
                {
                    std::cout << "Key pressed: " << str << " - " << keysym << std::endl;
                }
                
                if (XK_Up == keysym)
                {
                    std::cout << "Arrow Up\n";
                }
                
                if (XK_Down == keysym)
                {
                    std::cout << "Arrow Down\n";
                }
                
                if (XK_Escape == keysym)
                {
                    running = false;
                }
                
                break;
            }
            
            case KeyRelease:
            {
                len = XLookupString(&ev.xkey, str, sizeof(str), &keysym, nullptr);
                
                if (len > 0)
                {
                    std::cout << "Key released: " << str << " - " << keysym << std::endl;
                }
                
                break;
            }
            
            default:
            {
                break;
            }
        }
    }
    
    return 0;
}

#endif /* __linux__ */
