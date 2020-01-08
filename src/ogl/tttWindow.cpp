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
#include "tttProgram.h"

#include "stb_image.h"

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
    GLuint mTex0;
    GLuint mTex1;
    std::unique_ptr<tttProgram> mProgram;
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
    
    // Create texture
    stbi_set_flip_vertically_on_load(true);
    int w = 0;
    int h = 0;
    int chnls = 0;
    unsigned char* data = stbi_load("../res/images/container.jpg", &w, &h, &chnls, 0);
    
    glGenTextures(1, &(mRenderer->mTex0));
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, mRenderer->mTex0);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    
    stbi_image_free(data);
    
    data = stbi_load("../res/images/awesomeface.png", &w, &h, &chnls, 0);
    glGenTextures(1, &(mRenderer->mTex1));
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, mRenderer->mTex1);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    
    stbi_image_free(data);
    
    // Generate buffers
    glGenVertexArrays(1, &(mRenderer->mVAO));
    glBindVertexArray(mRenderer->mVAO);
    
    glGenBuffers(1, &(mRenderer->mVBO));
    glBindBuffer(GL_ARRAY_BUFFER, mRenderer->mVBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);
    
    unsigned int indices[] = 
    {
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };
    
    GLuint EBO = 0;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);
    
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);
    
    glBindVertexArray(0);

    // Create shaders
    const GLchar* vPath = "../res/shaders/main.vs";
    const GLchar* fPath = "../res/shaders/main.fs";
    mRenderer->mProgram = std::unique_ptr<tttProgram>(new tttProgram(vPath, fPath));
    mRenderer->mProgram->Use();
    mRenderer->mProgram->SetInt("aTex0", 0);
    mRenderer->mProgram->SetInt("aTex1", 1);
    glUseProgram(0);
}

void tttWindow::Draw(unsigned long tick)
{
    (void)tick;
    mRenderer->mProgram->Use();
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, mRenderer->mTex0);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, mRenderer->mTex1);
    
    glBindVertexArray(mRenderer->mVAO);
    
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //glDrawArrays(GL_TRIANGLES, 0, 3);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glUseProgram(0);
}
