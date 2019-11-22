#ifdef __WIN32__

#include "tttWinWindow.h"

#include <string.h>
#include <stdio.h>

#include "tttOglFuncs.h"

static const char* MSG_TITLE = "ERROR";

bool tttWinWindow::Create(const char* title, bool fullscreen, unsigned width, unsigned height)
{
    mFullscreen = fullscreen;
    mW = width;
    mH = height;
    strcpy(mTitle, title);
    
    WNDCLASS wndClass;
    wndClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    wndClass.lpfnWndProc = tttWinWindow::WndProc;
    wndClass.cbClsExtra = 0;
    wndClass.cbWndExtra = 0;
    wndClass.hInstance = nullptr;
    wndClass.hIcon = ::LoadIcon(nullptr, IDI_WINLOGO);
    wndClass.hCursor = ::LoadCursor(nullptr, IDC_ARROW);
    wndClass.hbrBackground = nullptr;
    wndClass.lpszMenuName = nullptr;
    wndClass.lpszClassName = reinterpret_cast<LPCSTR>(mTitle);
    
    if (!::RegisterClass(&wndClass))
    {
        MessageBoxA(nullptr, "Failed to register window class", MSG_TITLE, MB_OK);
        return false;
    }
    
    DEVMODE devSettings;
    memset(&devSettings, 0, sizeof(devSettings));
    devSettings.dmSize = sizeof(devSettings);
    devSettings.dmPelsWidth = mW;
    devSettings.dmPelsHeight = mH;
    devSettings.dmBitsPerPel = 32;
    devSettings.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT | DM_BITSPERPEL;
    
    DWORD dwExStyle;
    DWORD dwStyle;
    
    // TODO: fix fullscreen mode
    if (mFullscreen)
    {
        dwExStyle = WS_EX_APPWINDOW;
        dwStyle = WS_POPUP;
        
        ::ChangeDisplaySettings(&devSettings, CDS_FULLSCREEN);
    }
    else
    {
        dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
        dwStyle = WS_OVERLAPPEDWINDOW;
    }
    
    mWnd = ::CreateWindowEx(
        dwExStyle,
        reinterpret_cast<LPCSTR>(mTitle),
        reinterpret_cast<LPCSTR>(mTitle),
        WS_CLIPSIBLINGS | WS_CLIPCHILDREN | dwStyle,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        mW,
        mH,
        nullptr,
        nullptr,
        nullptr,
        this); // Pass our class inside WndProc
        
    if (!mWnd)
    {
        ::MessageBoxA(nullptr, "Failed to create a base window", MSG_TITLE, MB_OK);
        return false;
    }
    
    mDC = GetDC(mWnd);
    
    PIXELFORMATDESCRIPTOR pfd;
    memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
    pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
    pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 32;
    pfd.cDepthBits = 32;
    pfd.iLayerType = PFD_MAIN_PLANE;
    
    int pixelFormat = ::ChoosePixelFormat(mDC, &pfd);
    
    if (0 == pixelFormat)
    {
        ::MessageBoxA(nullptr, "Failed to choose pixel format", MSG_TITLE, MB_OK);
        return false;
    }
    
    bool result = ::SetPixelFormat(mDC, pixelFormat, &pfd);
    
    if (!result)
    {
        ::MessageBoxA(nullptr, "Failed to set pixel format", MSG_TITLE, MB_OK);
        return false;
    }
    
    HGLRC tmpContext = wglCreateContext(mDC);
    wglMakeCurrent(mDC, tmpContext);
    
    int attributes[] =
    {
        WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
        WGL_CONTEXT_MINOR_VERSION_ARB, 3,
        WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
        0
    };
    
    PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = reinterpret_cast<decltype(wglCreateContextAttribsARB)>(GetGLProcAddress(TTT_STR(wglCreateContextAttribsARB)));
    
    if (wglCreateContextAttribsARB)
    {
        mGL = wglCreateContextAttribsARB(mDC, nullptr, attributes);
        wglMakeCurrent(nullptr, nullptr);
        wglDeleteContext(tmpContext);
        wglMakeCurrent(mDC, mGL);
        
        PFNWGLSWAPINTERVALEXTPROC wglSwapIntervalEXT = reinterpret_cast<decltype(wglSwapIntervalEXT)>(GetGLProcAddress(TTT_STR(wglSwapIntervalEXT)));
        wglSwapIntervalEXT(0);
    }
    else
    {
        mGL = tmpContext;
        ::MessageBoxA(nullptr, "No modern OpenGL support", MSG_TITLE, MB_OK);
    }
    
    int version[2];
    glGetIntegerv(GL_MAJOR_VERSION, &version[0]);
    glGetIntegerv(GL_MINOR_VERSION, &version[1]);
    
    char new_title[255];
    sprintf(new_title, "%s %i.%i", mTitle, version[0], version[1]);
    strcpy(mTitle, new_title);
    
    LoadGLExtensions();
    ::ShowWindow(mWnd, SW_SHOW);
    ::UpdateWindow(mWnd);
    
    glClearColor(0.5f, 0.f, 0.f, 1.f);
    glFrontFace(GL_CCW);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glEnable(GL_DEPTH_TEST);
    
    return true;
}

int tttWinWindow::Exec()
{
    MSG msg = {};
    
    while (WM_QUIT != msg.message)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            RenderBegin();
            RenderEnd();
        }
    }
    
    return static_cast<int>(msg.wParam);
}

void tttWinWindow::RenderBegin()
{
    SetTitleFPS();
    static float green = 0.f;
    ++green;
    
    if (green > 1.f)
    {
        green = 0.f;
    }
    
    glClearColor(0.f, green, 0.f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void tttWinWindow::RenderEnd()
{
    ::SwapBuffers(mDC);
}

void tttWinWindow::SetTitleFPS()
{
    static DWORD prevTick = ::GetTickCount();
    static unsigned fps = 0;
    
    char windowText[255];
    DWORD currTick = 0;
    
    ++fps;
    currTick = ::GetTickCount();
    
    if (currTick - prevTick > 1000)
    {
        sprintf(windowText, "%s %s %i", mTitle, "FPS: ", fps);
        ::SetWindowText(mWnd, windowText);
        fps = 0;
        prevTick = currTick;
    }
}

void tttWinWindow::ResizeWindow(unsigned width, unsigned height)
{
    mW = width;
    mH = height;
    
    glViewport(0, 0, mW, mH);
}

LRESULT CALLBACK tttWinWindow::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    tttWinWindow* wnd = nullptr;
    
    switch (message)
    {
        case WM_CREATE:
        {
            wnd = reinterpret_cast<tttWinWindow*>(((LPCREATESTRUCT)lParam)->lpCreateParams);
            
            if (!wnd)
            {
                ::MessageBoxA(nullptr, "Bad window pointer on create", MSG_TITLE, MB_OK);
            }
            
            SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(wnd));
            
            break;
        }
        
        case WM_SIZE:
        {
            wnd = reinterpret_cast<tttWinWindow*>(::GetWindowLongPtr(hWnd, GWLP_USERDATA));
            
            if (!wnd)
            {
                ::MessageBoxA(nullptr, "Bad window pointer on resize", MSG_TITLE, MB_OK);
            }
            
            wnd->ResizeWindow(LOWORD(lParam), HIWORD(lParam));
            break;
        }
        
        case WM_DESTROY:
        {
            PostQuitMessage(0);
            break;
        }
    }
    return ::DefWindowProc(hWnd, message, wParam, lParam);
}

#endif /* __WIN32__ */