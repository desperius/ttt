#ifndef _TTT_WINDOW_H_
#define _TTT_WINDOW_H_

class tttWindow
{
public:
    tttWindow()
        : mTitle("")
        , mFullscreen(false)
        , mW(0)
        , mH(0)
    {}
    ~tttWindow() = default;
    
    virtual bool Create(const char* title, bool fullscreen, unsigned width, unsigned height) = 0;
    virtual void RenderBegin() = 0;
    virtual void RenderEnd() = 0;
    
private:
    virtual void SetTitleFPS() = 0;
    virtual void ResizeWindow(unsigned width, unsigned height) = 0;
    
protected:
    char mTitle[255];
    bool mFullscreen;
    unsigned mW;
    unsigned mH;
};

#endif /* _TTT_WINDOW_H_ */
