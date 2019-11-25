#ifndef _TTT_WIN_WINDOW_H_
#define _TTT_WIN_WINDOW_H_

#include <windows.h>
#include "tttWindow.h"

class tttWinWindow : public tttWindow
{
public:
    tttWinWindow() = default;
    ~tttWinWindow() = default;
    
    bool Create(const char* title, bool fullscreen, unsigned width, unsigned height) override;
    int Exec() override;
    void RenderBegin() override;
    void RenderEnd() override;
    
private:
    void SetTitleFPS() override;
    void ResizeWindow(unsigned width, unsigned height) override;
    
    static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
    
    static void OnWindowCreate(HWND hWnd, WPARAM wParam, LPARAM lParam);
    static void OnWindowResize(HWND hWnd, WPARAM wParam, LPARAM lParam);
    static void OnKeyPressed(WPARAM wParam, LPARAM lParam);
    
private:
    static HDC mDC;
    static HWND mWnd;
    static POINTS mBgn;
    static POINTS mEnd;
    HGLRC mGL;
};

#endif /* _TTT_WIN_WINDOW_H_ */
