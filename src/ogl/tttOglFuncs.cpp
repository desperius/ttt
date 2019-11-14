#include "tttOglFuncs.h"

#ifdef __WIN32__

PFNGLCREATEPROGRAMPROC glCreateProgram = nullptr;
PFNGLDELETEPROGRAMPROC glDeleteProgram = nullptr;

void* GetGLProcAddress(const char* name)
{
    if ((nullptr == name) || (0 == strlen(name)))
    {
        return nullptr;
    }
    
    return reinterpret_cast<void*>(wglGetProcAddress(name));
}

void LoadGLExtensions()
{
    glCreateProgram = reinterpret_cast<decltype(glCreateProgram)>(GetGLProcAddress(TTT_STR(glCreateProgram)));
    glDeleteProgram = reinterpret_cast<decltype(glDeleteProgram)>(GetGLProcAddress(TTT_STR(glDeleteProgram)));
}

#endif /* __WIN32__ */
