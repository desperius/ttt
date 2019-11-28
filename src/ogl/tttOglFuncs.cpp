#include "tttOglFuncs.h"

#include <string.h>

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

#elif __linux__

bool IsExtensionSupported(const char* extList, const char* extension)
{
    (void)extList;
    (void)extension;
    const char* start = nullptr;
    const char* where = nullptr;
    const char* terminator = nullptr;
    
    where = strchr(extension, ' ');
    
    if (where || *extension == '\0')
    {
        return false;
    }
    
    for (start = extList; ; )
    {
        where = strstr(start, extension);
        
        if (!where)
        {
            break;
        }
        
        terminator = where + strlen(extension);
        
        if (where == start || *(where - 1) == ' ')
        {
            if (*terminator == ' ' || *terminator == '\0')
            {
                return true;
            }
        }
        
        start = terminator;
    }
    
    return false;
}

#endif
