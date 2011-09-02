#ifndef PROGRAM_H
#define PROGRAM_H

#include "glew/glew.h"
#include "utils/gl.h"
#include "typedefs.h"
#include <map>

class Program
{
  public:
    Program(GLuint program);
    ~Program();
    void use();
    void unuse();
    void findUniform(const String& name);
    void setUniformi(const String& name, int v0);
    void setUniformi(const String& name, int v0, int v1);
    void setUniformf(const String& name, float v0);
    void setUniformf(const String& name, float v0, float v1, float v2);
  private:
    GLuint m_program;
    std::map<String, GLint> m_uniformMap;
};

inline void Program::use(){
  glUseProgram(m_program);
  //checkGl();
}

inline void Program::unuse(){
  glUseProgram(0);
  //checkGl();
}

inline Program::~Program(){
  glDeleteProgram(m_program);
}

inline void Program::setUniformi(const String& name, int v0){
  glUniform1i(m_uniformMap[name], v0);
}

inline void Program::setUniformi(const String& name, int v0, int v1){
  glUniform2i(m_uniformMap[name], v0, v1);
}

inline void Program::setUniformf(const String& name, float v0){
  glUniform1f(m_uniformMap[name], v0);
}

inline void Program::setUniformf(const String& name, float v0, float v1, float v2){
  glUniform3f(m_uniformMap[name], v0, v1, v2);
}






#endif // PROGRAM_H
