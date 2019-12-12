#ifndef _TTT_WINDOW_H_
#define _TTT_WINDOW_H_

#include <memory>

class tttRenderer;

class tttWindow
{
public:
    tttWindow()
        : mTitle("")
        , mFullscreen(false)
        , mW(0)
        , mH(0)
        , mRenderer(nullptr)
    {}
    
    virtual ~tttWindow();
    
    virtual bool Create(const char* title, bool fullscreen, unsigned width, unsigned height);
    
    virtual int Exec() = 0;
    virtual void RenderBegin() = 0;
    virtual void RenderEnd() = 0;
    
protected:
    void PrintInfo();
    void TestGL();
    void Draw(unsigned long tick);
    
private:
    virtual void SetTitleFPS() = 0;
    virtual void ResizeWindow(unsigned width, unsigned height) = 0;
    
protected:
    char mTitle[255];
    bool mFullscreen;
    unsigned mW;
    unsigned mH;
    tttRenderer* mRenderer;
};

#endif /* _TTT_WINDOW_H_ */
