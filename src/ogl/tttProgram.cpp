#include "tttProgram.h"

#include <iostream>
#include <fstream>

tttProgram::tttProgram(const GLchar* vPath, const GLchar* fPath)
{
    std::ifstream vFile;
    std::ifstream fFile;
    
    vFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    
    std::string vCode;
    std::string fCode;
    
    try
    {
        vFile.open(vPath);
        fFile.open(fPath);
        vCode = std::string((std::istreambuf_iterator<char>(vFile)), std::istreambuf_iterator<char>());
        fCode = std::string((std::istreambuf_iterator<char>(fFile)), std::istreambuf_iterator<char>());
        vFile.close();
        fFile.close();
    }
    catch (std::ifstream::failure& e)
    {
        std::cout << "Failed to load a shader from file: " << e.what() << std::endl;
    }
    
    const GLchar* vSource = vCode.c_str();
    const GLchar* fSource = fCode.c_str();
    
    GLint success = 0;
    GLuint vertID = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertID, 1, &vSource, nullptr);
    glCompileShader(vertID);
    
    glGetShaderiv(vertID, GL_COMPILE_STATUS, &success);
    
    if (GL_FALSE == success)
    {
        std::cout << "Vertex Shader compilation failed!\n";
    }
    
    GLuint fragID = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragID, 1, &fSource, nullptr);
    glCompileShader(fragID);
    
    glGetShaderiv(fragID, GL_COMPILE_STATUS, &success);
    
    if (GL_FALSE == success)
    {
        std::cout << "Fragment Shader compilation failed!\n";
    }
    
    mProgramID = glCreateProgram();
    glAttachShader(mProgramID, vertID);
    glAttachShader(mProgramID, fragID);
    glLinkProgram(mProgramID);
    
    glGetProgramiv(mProgramID, GL_LINK_STATUS, &success);
    
    if (GL_FALSE == success)
    {
        std::cout << "Program linkage failed!\n";
    }
    
    glDeleteShader(vertID);
    glDeleteShader(fragID);
}

tttProgram::~tttProgram()
{
    glUseProgram(0);
    glDeleteProgram(mProgramID);
}

void tttProgram::Use()
{
    glUseProgram(mProgramID);
}

void tttProgram::SetBool(const std::string& name, bool value)
{
    glUniform1i(glGetUniformLocation(mProgramID, name.c_str()), static_cast<GLint>(value));
}

void tttProgram::SetInt(const std::string& name, int value)
{
    glUniform1i(glGetUniformLocation(mProgramID, name.c_str()), value);
}

void tttProgram::SetFloat(const std::string& name, float value)
{
    glUniform1f(glGetUniformLocation(mProgramID, name.c_str()), value);
}