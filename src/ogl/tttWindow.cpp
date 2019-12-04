#include "tttWindow.h"

#include <string.h>
#include <iostream>

#include "tttOglFuncs.h"

#ifdef __WIN32__

const GLchar* vsource = "#version 330\n void main()\n {\n gl_Position = vec4(1.0, 0.0, 0.0, 1.0);\n }\n";

#elif __linux__

const GLchar* vsource = "#version 450\n void main()\n {\n gl_Position = vec4(1.0, 0.0, 0.0, 1.0);\n }\n";

#endif

bool tttWindow::Create(const char* title, bool fullscreen, unsigned width, unsigned height)
{
    mFullscreen = fullscreen;
    mW = width;
    mH = height;
    strcpy(mTitle, title);
    
    return true;
}

void tttWindow::PrintInfo()
{
    std::cout << "GL vendor: " << glGetString(GL_VENDOR) << std::endl;
    int version[2];
    glGetIntegerv(GL_MAJOR_VERSION, &version[0]);
    glGetIntegerv(GL_MINOR_VERSION, &version[1]);
    std::cout << "GL ver: " << version[0] << "." << version[1] << std::endl;
    std::cout << "GLSL ver: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
    
    char new_title[512];
    sprintf(new_title, "%s %i.%i", mTitle, version[0], version[1]);
    strcpy(mTitle, new_title);
}

void tttWindow::TestGL()
{
    unsigned vbo = 0;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    // Create shaders
    GLuint vertexID = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexID, 1, &vsource, nullptr);
    glCompileShader(vertexID);

    GLint success = 0;
    glGetShaderiv(vertexID, GL_COMPILE_STATUS, &success);

    if (GL_FALSE == success)
    {
        GLint maxlen = 0;
        glGetShaderiv(vertexID, GL_INFO_LOG_LENGTH, &maxlen);
        char* loginfo = new char[maxlen];
        glGetShaderInfoLog(vertexID, maxlen, nullptr, loginfo);
        std::cout << "Vertex Shader compilation failed: " << loginfo << std::endl;
    }
}
