#include "tttWindow.h"

#include <string.h>
#include <iostream>

#include "tttOglFuncs.h"

const GLchar* vsrc = "#version 330 core\n void main()\n {\n gl_Position = vec4(1.0, 0.0, 0.0, 1.0);\n }\n";
const GLchar* fsrc = "#version 330 core\n out vec4 fragColor;\n void main()\n {\n fragColor = vec4(1.0, 0.5, 0.2, 1.0);\n }\n";

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
    GLuint vertID = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertID, 1, &vsrc, nullptr);
    glCompileShader(vertID);

    GLint success = 0;
    glGetShaderiv(vertID, GL_COMPILE_STATUS, &success);

    if (GL_FALSE == success)
    {
        std::cout << "Vertex Shader compilation failed!\n";
    }
    
    GLuint fragID = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragID, 1, &fsrc, nullptr);
    glCompileShader(fragID);
    
    glGetShaderiv(fragID, GL_COMPILE_STATUS, &success);
    
    if (GL_FALSE == success)
    {
        std::cout << "Fragment Shader compilation failed!\n";
    }
}
