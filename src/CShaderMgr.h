#ifndef CSHADERMGR_H
#define CSHADERMGR_H

#include <map>
#include "typedefs.h"
#include "GL/glew.h"

class Program;

class CShaderMgr{
  public:
    Program* getProgram(const String& name);
    void cleanup();
  private:
    typedef std::map<String, Program*> ProgramMap;
    ProgramMap m_programs;
    typedef std::map<String, GLuint> ShaderMap;
    ShaderMap m_shaders;
    GLuint loadShader(String fileName, GLuint type );
};

#endif // CSHADERMGR_H
