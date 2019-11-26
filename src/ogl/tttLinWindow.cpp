#ifdef __linux__

#include "tttLinWindow.h"

#include <X11/Xutil.h>
#include <X11/keysymdef.h>

#include <iostream>

int tttLinWindow::mX = 0;
int tttLinWindow::mY = 0;

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
    
    long keyboard = KeyPressMask | KeyReleaseMask | KeymapStateMask;
    long mouse = PointerMotionMask | ButtonPressMask | ButtonReleaseMask | EnterWindowMask | LeaveWindowMask;
    XSelectInput(mDisplay, mWindow, keyboard | mouse);
    
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
    int x = 0;
    int y = 0;
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
            
            case ButtonPress:
            {
                if (ev.xbutton.button == 1)
                {
                    mX = ev.xbutton.x;
                    mY = ev.xbutton.y;
                    std::cout << "Left button: ";
                    std::cout << "(" << mX << ", " << mY << ")\n";
                }
                else if (ev.xbutton.button == 3)
                {
                    std::cout << "Right button\n";
                }
                
                break;
            }
            
            case ButtonRelease:
            {
                if (ev.xbutton.button == 1)
                {
                    std::cout << "Left button release\n";
                }
                
                break;
            }
            
            case MotionNotify:
            {
                x = ev.xmotion.x;
                y = ev.xmotion.y;
                std::cout << "Move: " << "(" << x << ", " << y << ")\n";
                break;
            }
            
            case EnterNotify:
            {
                std::cout << "Mouse in\n";
                break;
            }
            
            case LeaveNotify:
            {
                std::cout << "Mouse out\n";
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
