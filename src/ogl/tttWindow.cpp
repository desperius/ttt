#include "tttWindow.h"

#include <string.h>

bool tttWindow::Create(const char* title, bool fullscreen, unsigned width, unsigned height)
{
    mFullscreen = fullscreen;
    mW = width;
    mH = height;
    strcpy(mTitle, title);
    
    return true;
}