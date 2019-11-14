#ifndef _TTT_OGL_FUNCS_H_
#define _TTT_OGL_FUNCS_H_

#ifdef __WIN32__

#include <gl/gl.h>
#include <gl/glext.h>
#include <gl/wglext.h>

extern PFNGLCREATEPROGRAMPROC glCreateProgram;
extern PFNGLDELETEPROGRAMPROC glDeleteProgram;
//extern PFNGLUSEPROGRAMPROC glUseProgram;
//extern PFNGLATTACHSHADERPROC glAttachShader;
//extern PFNGLDETACHSHADERPROC glDetachShader;
//extern PFNGLLINKPROGRAMPROC glLinkProgram;
//extern PFNGLGETPROGRAMIVPROC glGetProgramiv;
//extern PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;
//extern PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation;
//extern PFNGLUNIFORM1IPROC glUniform1i;
//extern PFNGLUNIFORM1IVPROC glUniform1iv;
//extern PFNGLUNIFORM2IVPROC glUniform2iv;
//extern PFNGLUNIFORM3IVPROC glUniform3iv;
//extern PFNGLUNIFORM4IVPROC glUniform4iv;
//extern PFNGLUNIFORM1FPROC glUniform1f;
//extern PFNGLUNIFORM1FVPROC glUniform1fv;
//extern PFNGLUNIFORM2FVPROC glUniform2fv;
//extern PFNGLUNIFORM3FVPROC glUniform3fv;
//extern PFNGLUNIFORM4FVPROC glUniform4fv;
//extern PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv;
//extern PFNGLGETATTRIBLOCATIONPROC glGetAttribLocation;
//extern PFNGLVERTEXATTRIB1FPROC glVertexAttrib1f;
//extern PFNGLVERTEXATTRIB1FVPROC glVertexAttrib1fv;
//extern PFNGLVERTEXATTRIB2FVPROC glVertexAttrib2fv;
//extern PFNGLVERTEXATTRIB3FVPROC glVertexAttrib3fv;
//extern PFNGLVERTEXATTRIB4FVPROC glVertexAttrib4fv;
//extern PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;
//extern PFNGLDISABLEVERTEXATTRIBARRAYPROC glDisableVertexAttribArray;
//extern PFNGLBINDATTRIBLOCATIONPROC glBindAttribLocation;
//extern PFNGLGETACTIVEUNIFORMPROC glGetActiveUniform;
//
//// Shader
//extern PFNGLCREATESHADERPROC glCreateShader;
//extern PFNGLDELETESHADERPROC glDeleteShader;
//extern PFNGLSHADERSOURCEPROC glShaderSource;
//extern PFNGLCOMPILESHADERPROC glCompileShader;
//extern PFNGLGETSHADERIVPROC glGetShaderiv;
//
//// VBO
//extern PFNGLGENBUFFERSPROC glGenBuffers;
//extern PFNGLBINDBUFFERPROC glBindBuffer;
//extern PFNGLBUFFERDATAPROC glBufferData;
//extern PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;
//extern PFNGLDELETEBUFFERSPROC glDeleteBuffers;
//extern PFNGLMULTIDRAWELEMENTSPROC glMultiDrawElements;
//extern PFNGLBUFFERSUBDATAPROC glBufferSubData;
//extern PFNGLMAPBUFFERPROC glMapBuffer;
//extern PFNGLUNMAPBUFFERPROC glUnmapBuffer;
//
//// VAO
//extern PFNGLGENVERTEXARRAYSPROC glGenVertexArrays;
//extern PFNGLBINDVERTEXARRAYPROC glBindVertexArray;
//extern PFNGLDELETEVERTEXARRAYSPROC glDeleteVertexArrays;
//
//extern PFNGLACTIVETEXTUREPROC glActiveTexture;
//extern PFNGLGENERATEMIPMAPPROC glGenerateMipmap;

#define TTT_STR(str) #str

void* GetGLProcAddress(const char* name);
void LoadGLExtensions();

#endif /* __WIN32__ */

#endif /* _TTT_OGL_FUNCS_H_ */
