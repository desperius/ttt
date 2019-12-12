#include "tttWindow.h"

#include <string.h>
#include <cmath>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <streambuf>
#include <iostream>

#include "tttOglFuncs.h"

void LoadShader(std::string &shader, GLenum type)
{
    std::string path;
    
    switch (type)
    {
        case GL_VERTEX_SHADER:
        {
            path = "../res/shaders/main.vs";
            break;
        }
        
        case GL_FRAGMENT_SHADER:
        {
            path = "../res/shaders/main.fs";
            break;
        }
        
        default:
        {
            break;
        }
    }
    
    std::ifstream file(path.c_str());
    
    if (!file.fail())
    {
        shader = std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        file.close();
    }
}

void LoadVertices(std::vector<GLfloat>& vertices)
{
    std::ifstream file("../res/models/vertices.csv");
    std::string line;
    std::string word;
    
    while (!file.eof())
    {
        std::getline(file, line);
        
        std::stringstream stream(line);
        
        while (std::getline(stream, word, ','))
        {
            vertices.push_back(std::stof(word));
        }
    }
}

class tttRenderer
{
public:
    GLuint mVAO;
    GLuint mVBO;
    GLuint mProgram;
};

tttWindow::~tttWindow()
{
    delete mRenderer;
    mRenderer = nullptr;
}

bool tttWindow::Create(const char* title, bool fullscreen, unsigned width, unsigned height)
{
    mFullscreen = fullscreen;
    mW = width;
    mH = height;
    strcpy(mTitle, title);
    
    mRenderer = new tttRenderer();
    
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
    std::vector<GLfloat> vertices;
    LoadVertices(vertices);
    
    glGenVertexArrays(1, &(mRenderer->mVAO));
    glBindVertexArray(mRenderer->mVAO);
    
    glGenBuffers(1, &(mRenderer->mVBO));
    glBindBuffer(GL_ARRAY_BUFFER, mRenderer->mVBO);
    //glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices.data(), GL_STATIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);
    
//    GLuint EBO = 0;
//    glGenBuffers(1, &EBO);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);
    
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    
    glBindVertexArray(0);

    // Create shaders
    std::string shader;
    LoadShader(shader, GL_VERTEX_SHADER);
    GLuint vertID = glCreateShader(GL_VERTEX_SHADER);
    auto c_str = shader.c_str();
    glShaderSource(vertID, 1, &c_str, nullptr);
    glCompileShader(vertID);

    GLint success = 0;
    glGetShaderiv(vertID, GL_COMPILE_STATUS, &success);

    if (GL_FALSE == success)
    {
        std::cout << "Vertex Shader compilation failed!\n";
    }
    
    LoadShader(shader, GL_FRAGMENT_SHADER);
    GLuint fragID = glCreateShader(GL_FRAGMENT_SHADER);
    c_str = shader.c_str();
    glShaderSource(fragID, 1, &c_str, nullptr);
    glCompileShader(fragID);
    
    glGetShaderiv(fragID, GL_COMPILE_STATUS, &success);
    
    if (GL_FALSE == success)
    {
        std::cout << "Fragment Shader compilation failed!\n";
    }
    
    mRenderer->mProgram = glCreateProgram();
    glAttachShader(mRenderer->mProgram, vertID);
    glAttachShader(mRenderer->mProgram, fragID);
    glLinkProgram(mRenderer->mProgram);
    
    glGetProgramiv(mRenderer->mProgram, GL_LINK_STATUS, &success);
    
    if (GL_FALSE == success)
    {
        std::cout << "Program linkage failed!\n";
    }
    
    glDeleteShader(vertID);
    glDeleteShader(fragID);
}

void tttWindow::Draw(unsigned long tick)
{
    (void)tick;
    glUseProgram(mRenderer->mProgram);
    
    glBindVertexArray(mRenderer->mVAO);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
