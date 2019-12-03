#include "tttOglFuncs.h"

#include <string.h>

PFNGLCREATEPROGRAMPROC glCreateProgram = nullptr;
PFNGLDELETEPROGRAMPROC glDeleteProgram = nullptr;
PFNGLUSEPROGRAMPROC glUseProgram = nullptr;
PFNGLATTACHSHADERPROC glAttachShader = nullptr;
PFNGLDETACHSHADERPROC glDetachShader = nullptr;
PFNGLLINKPROGRAMPROC glLinkProgram = nullptr;
PFNGLGETPROGRAMIVPROC glGetProgramiv = nullptr;
PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog = nullptr;
PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation = nullptr;
PFNGLUNIFORM1IPROC glUniform1i = nullptr;
PFNGLUNIFORM1IVPROC glUniform1iv = nullptr;
PFNGLUNIFORM2IVPROC glUniform2iv = nullptr;
PFNGLUNIFORM3IVPROC glUniform3iv = nullptr;
PFNGLUNIFORM4IVPROC glUniform4iv = nullptr;
PFNGLUNIFORM1FPROC glUniform1f = nullptr;
PFNGLUNIFORM1FVPROC glUniform1fv = nullptr;
PFNGLUNIFORM2FVPROC glUniform2fv = nullptr;
PFNGLUNIFORM3FVPROC glUniform3fv = nullptr;
PFNGLUNIFORM4FVPROC glUniform4fv = nullptr;
PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv = nullptr;
PFNGLGETATTRIBLOCATIONPROC glGetAttribLocation = nullptr;
PFNGLVERTEXATTRIB1FPROC glVertexAttrib1f = nullptr;
PFNGLVERTEXATTRIB1FVPROC glVertexAttrib1fv = nullptr;
PFNGLVERTEXATTRIB2FVPROC glVertexAttrib2fv = nullptr;
PFNGLVERTEXATTRIB3FVPROC glVertexAttrib3fv = nullptr;
PFNGLVERTEXATTRIB4FVPROC glVertexAttrib4fv = nullptr;
PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray = nullptr;
PFNGLDISABLEVERTEXATTRIBARRAYPROC glDisableVertexAttribArray = nullptr;
PFNGLBINDATTRIBLOCATIONPROC glBindAttribLocation = nullptr;
PFNGLGETACTIVEUNIFORMPROC glGetActiveUniform = nullptr;

// Shader
PFNGLCREATESHADERPROC glCreateShader = nullptr;
PFNGLDELETESHADERPROC glDeleteShader = nullptr;
PFNGLSHADERSOURCEPROC glShaderSource = nullptr;
PFNGLCOMPILESHADERPROC glCompileShader = nullptr;
PFNGLGETSHADERIVPROC glGetShaderiv = nullptr;

// VBO
PFNGLGENBUFFERSPROC glGenBuffers = nullptr;
PFNGLBINDBUFFERPROC glBindBuffer = nullptr;
PFNGLBUFFERDATAPROC glBufferData = nullptr;
PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer = nullptr;
PFNGLDELETEBUFFERSPROC glDeleteBuffers = nullptr;
PFNGLMULTIDRAWELEMENTSPROC glMultiDrawElements = nullptr;
PFNGLBUFFERSUBDATAPROC glBufferSubData = nullptr;
PFNGLMAPBUFFERPROC glMapBuffer = nullptr;
PFNGLUNMAPBUFFERPROC glUnmapBuffer = nullptr;

// VAO
PFNGLGENVERTEXARRAYSPROC glGenVertexArrays = nullptr;
PFNGLBINDVERTEXARRAYPROC glBindVertexArray = nullptr;
PFNGLDELETEVERTEXARRAYSPROC glDeleteVertexArrays = nullptr;

//PFNGLACTIVETEXTUREPROC glActiveTexture = nullptr;
//PFNGLGENERATEMIPMAPPROC glGenerateMipmap = nullptr;

#ifdef __WIN32__

static auto tttGetProcAddress = wglGetProcAddress;
typedef const char* charptr;

#elif __linux__

static auto tttGetProcAddress = glXGetProcAddressARB;
typedef const GLubyte* charptr;

#endif

void* GetProcAddress(const char* name)
{
    if ((nullptr == name) || (0 == strlen(name)))
    {
        return nullptr;
    }

    return reinterpret_cast<void*>(tttGetProcAddress(reinterpret_cast<charptr>(name)));
}

void LoadGLExtensions()
{
    glCreateProgram = reinterpret_cast<decltype(glCreateProgram)>(GetProcAddress(TTT_STR(glCreateProgram)));
    glDeleteProgram = reinterpret_cast<decltype(glDeleteProgram)>(GetProcAddress(TTT_STR(glDeleteProgram)));
    glGenBuffers = reinterpret_cast<decltype(glGenBuffers)>(GetProcAddress(TTT_STR(glGenBuffers)));
    glBindBuffer = reinterpret_cast<decltype(glBindBuffer)>(GetProcAddress(TTT_STR(glBindBuffer)));
    glCreateShader = reinterpret_cast<decltype(glCreateShader)>(GetProcAddress(TTT_STR(glCreateShader)));
    glShaderSource = reinterpret_cast<decltype(glShaderSource)>(GetProcAddress(TTT_STR(glShaderSource)));
    glCompileShader = reinterpret_cast<decltype(glCompileShader)>(GetProcAddress(TTT_STR(glCompileShader)));
    glGetShaderiv = reinterpret_cast<decltype(glGetShaderiv)>(GetProcAddress(TTT_STR(glGetShaderiv)));
    glGetShaderInfoLog = reinterpret_cast<decltype(glGetShaderInfoLog)>(GetProcAddress(TTT_STR(glGetShaderInfoLog)));
}

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
