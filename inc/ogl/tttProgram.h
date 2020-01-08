#ifndef _TTT_PROGRAM_
#define _TTT_PROGRAM_

#include "tttOglFuncs.h"

#include <string>

class tttProgram
{
public:
    tttProgram(const GLchar* vPath, const GLchar* fPath);
    ~tttProgram();
    
    tttProgram(const tttProgram&) = delete;
    tttProgram(tttProgram&&) = delete;
    
    tttProgram& operator= (const tttProgram&) = delete;
    tttProgram& operator= (tttProgram&) = delete;
    
    void Use();
    void SetBool(const std::string& name, bool value);
    void SetInt(const std::string& name, int value);
    void SetFloat(const std::string& name, float value);
    
private:
    GLuint mProgramID;
};

#endif /* _TTT_PROGRAM_ */