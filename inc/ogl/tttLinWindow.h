#ifndef _TTT_LIN_WINDOW_H_
#define _TTT_LIN_WINDOW_H_

#include "tttWindow.h"

#include <X11/Xlib.h>

#include "tttOglFuncs.h"

class tttLinWindow : public tttWindow
{
public:
    tttLinWindow() = default;
    virtual ~tttLinWindow();
    
    bool Create(const char* title, bool fullscreen, unsigned width, unsigned height) override;
    int Exec() override;
    void RenderBegin() override;
    void RenderEnd() override;
    
private:
    void SetTitleFPS() override;
    void ResizeWindow(unsigned width, unsigned height) override;
    
private:
    Display* mDisplay = nullptr;
    Screen* mScreen = nullptr;
    int mScreenID = 0;
    Window mWindow;
    GLXContext mContext;
    
    static int mX;
    static int mY;
};

#endif /* _TTT_LIN_WINDOW_H_ */