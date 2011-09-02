#include "Program.h"

#include "CBaseEngine.h"
#include <stdexcept>

Program::Program(GLuint program):
  m_program(program)
{}

void Program::findUniform(const String& name){
  GLint unf = glGetUniformLocation(m_program, name.c_str());
  m_uniformMap[name] = unf;
  if(unf == -1){
    throw std::invalid_argument((format("Can't find uniform '%s' with location %d in program %d") % name % unf % m_program).str());
  }else{
    engine->log((format("Found uniform '%s' with location %d in program %d") % name % unf % m_program).str());
  }
}
