#ifdef __linux__

#include "tttLinWindow.h"

#include <stdio.h>

#include <iostream>
#include <chrono>

using namespace std::chrono;

typedef GLXContext (*glXCreateContextAttribsARBProc)(Display*, GLXFBConfig, GLXContext, Bool, const int*);

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
    tttWindow::Create(title, fullscreen, width, height);
    
    mDisplay = XOpenDisplay(nullptr);
    
    if (!mDisplay)
    {
        std::cout << "Could not open display\n";
    }
    
    mScreen = DefaultScreenOfDisplay(mDisplay);
    mScreenID = DefaultScreen(mDisplay);
    
    // Check GLX version
    GLint major = 0;
    GLint minor = 0;
    glXQueryVersion(mDisplay, &major, &minor);
    
    if (major <= 1 && minor < 2)
    {
        std::cout << "GLX 1.2 or greater is required\n";
        XCloseDisplay(mDisplay);
        return false;
    }
    else
    {
        std::cout << "GLX ver " << major << "." << minor << std::endl;
    }
    
    GLint glxattribs[] =
    {
        GLX_X_RENDERABLE  , True,
        GLX_DRAWABLE_TYPE , GLX_WINDOW_BIT,
        GLX_RENDER_TYPE   , GLX_RGBA_BIT,
        GLX_X_VISUAL_TYPE , GLX_TRUE_COLOR,
        GLX_RED_SIZE      , 8,
        GLX_GREEN_SIZE    , 8,
        GLX_BLUE_SIZE     , 8,
        GLX_ALPHA_SIZE    , 8,
        GLX_DEPTH_SIZE    , 24,
        GLX_STENCIL_SIZE  , 8,
        GLX_DOUBLEBUFFER  , True,
        None
    };
    
    int fbcount = 0;
    GLXFBConfig* fbc = glXChooseFBConfig(mDisplay, mScreenID, glxattribs, &fbcount);
    
    if (nullptr == fbc)
    {
        std::cout << "Failed to retrieve framebuffers\n";
        XCloseDisplay(mDisplay);
        return false;
    }
    
    // Pick the Framebuffer config/visual with the most samples per pixel
    int bestFbc = -1;
    int bestSamp = -1;
    
    for (int i = 0; i < fbcount; ++i)
    {
        XVisualInfo* visual = glXGetVisualFromFBConfig(mDisplay, fbc[i]);
        
        if (visual)
        {
            int sampBuf = 0;
            int sampNum = 0;
            glXGetFBConfigAttrib(mDisplay, fbc[i], GLX_SAMPLE_BUFFERS, &sampBuf);
            glXGetFBConfigAttrib(mDisplay, fbc[i], GLX_SAMPLES, &sampNum);
            
            if (bestFbc < 0 || (sampBuf && (sampNum > bestSamp)))
            {
                bestFbc = i;
                bestSamp = sampNum;
            }
        }
        
        XFree(visual);
    }
    
    GLXFBConfig newFbc = fbc[bestFbc];
    XFree(fbc);
    
    XVisualInfo* visualInfo = glXGetVisualFromFBConfig(mDisplay, newFbc);
    
    if (nullptr == visualInfo)
    {
        std::cout << "Could not create correct visual window\n";
        XCloseDisplay(mDisplay);
        return false;
    }
    
    if (mScreenID != visualInfo->screen)
    {
        std::cout << "Screen IDs do not match\n";
        XCloseDisplay(mDisplay);
        return false;
    }
    
    Window root = RootWindow(mDisplay, mScreenID);
    
    XSetWindowAttributes windowAttribs;
    windowAttribs.border_pixel = BlackPixel(mDisplay, mScreenID);
    windowAttribs.background_pixel = WhitePixel(mDisplay, mScreenID);
    windowAttribs.override_redirect = True;
    windowAttribs.colormap = XCreateColormap(mDisplay, root, visualInfo->visual, AllocNone);
    windowAttribs.event_mask = ExposureMask;
    
    // Open the window
    unsigned long valuemask = CWBackPixel | CWColormap | CWBorderPixel | CWEventMask;
    mWindow = XCreateWindow(mDisplay, root, 0, 0, mW, mH, 0, visualInfo->depth, InputOutput, visualInfo->visual, valuemask, &windowAttribs);

    Atom atomDeleteWindow = XInternAtom(mDisplay, "WM_DELETE_WINDOW", False);
    XSetWMProtocols(mDisplay, mWindow, &atomDeleteWindow, 1);
    
    // Create GLX OpenGL context
    glXCreateContextAttribsARBProc glXCreateContextAttribsARB = nullptr;
    glXCreateContextAttribsARB = (glXCreateContextAttribsARBProc)glXGetProcAddressARB((const GLubyte*)"glXCreateContextAttribsARB");
    
    if (!glXCreateContextAttribsARB)
    {
        std::cout << "glXCreateContextAttribsARB not found\n";
        XCloseDisplay(mDisplay);
    }
    
    const char* glxExts = glXQueryExtensionsString(mDisplay, mScreenID);
    
    int contextAttrs[] =
    {
        GLX_CONTEXT_MAJOR_VERSION_ARB, 3,
        GLX_CONTEXT_MINOR_VERSION_ARB, 3,
        GLX_CONTEXT_PROFILE_MASK_ARB, GLX_CONTEXT_CORE_PROFILE_BIT_ARB,
        GLX_CONTEXT_FLAGS_ARB, GLX_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
        None
    };
    
    GLXContext mContext = 0;
    
    if (!IsExtensionSupported(glxExts, "GLX_ARB_create_context"))
    {
        mContext = glXCreateNewContext(mDisplay, newFbc, GLX_RGBA_TYPE, 0, True);
    }
    else
    {
        mContext = glXCreateContextAttribsARB(mDisplay, newFbc, 0, True, contextAttrs);
    }
    
    XSync(mDisplay, False);
    
    if(!glXIsDirect(mDisplay, mContext))
    {
        std::cout << "Indirect GLX rendering context obtained\n";
    }
    else
    {
        std::cout << "Direct GLX rendering context obtained\n";
    }
    
    glXMakeCurrent(mDisplay, mWindow, mContext);
    
    long keyboard = KeyPressMask | KeyReleaseMask | KeymapStateMask;
    long mouse = PointerMotionMask | ButtonPressMask | ButtonReleaseMask | EnterWindowMask | LeaveWindowMask;
    XSelectInput(mDisplay, mWindow, keyboard | mouse | ExposureMask | StructureNotifyMask);
    
    // Show the window
    XClearWindow(mDisplay, mWindow);
    XMapRaised(mDisplay, mWindow);

    // Load OpenGL extensions
    LoadGLExtensions();
    
    PrintInfo();

    // Test OpenGL functions calls
    TestGL();
    
    // Set window title
    XStoreName(mDisplay, mWindow, mTitle);
    
    // Free useless resources
    XFree(visualInfo);
    XFreeColormap(mDisplay, windowAttribs.colormap);
    
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
            
            case Expose:
            {
                XWindowAttributes attribs;
                XGetWindowAttributes(mDisplay, mWindow, &attribs);
                ResizeWindow(attribs.width, attribs.height);
                break;
            }

            case ClientMessage:
            {
                running = false;
                break;
            }

            case DestroyNotify:
            {
                running = false;
                break;
            }
            
            
            default:
            {
                break;
            }
        }
        
        RenderBegin();
        RenderEnd();
    }
    
    return 0;
}

void tttLinWindow::RenderBegin()
{
    SetTitleFPS();
    
    float red = mX / static_cast<float>(mW);
    float green = mY / static_cast<float>(mH);
    
    glClearColor(red, green, 0.f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    Draw(0);
}

void tttLinWindow::RenderEnd()
{
    glXSwapBuffers(mDisplay, mWindow);
}

void tttLinWindow::SetTitleFPS()
{
    static milliseconds prevTick = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
    static unsigned fps = 0;
    
    char windowText[512] = {0};
    milliseconds currTick;
    ++fps;
    currTick = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
    
    if ((currTick - prevTick).count() > 1000)
    {
        sprintf(windowText, "%s %s %i", mTitle, "FPS: ", fps);
        XStoreName(mDisplay, mWindow, windowText);
        fps = 0;
        prevTick = currTick;
    }
}

void tttLinWindow::ResizeWindow(unsigned width, unsigned height)
{
    std::cout << "Resize: ";
    mW = width;
    mH = height;
    std::cout << "w: " << mW << " h: " << mH << std::endl;
    glViewport(0, 0, mW, mH);
}

#endif /* __linux__ */
