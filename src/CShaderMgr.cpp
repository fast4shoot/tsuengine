#include "CShaderMgr.h"
#include "elements/modifiers/Modifier.h"
#include <boost/foreach.hpp>
#include "utils/gl.h"
#include "elements/Program.h"
#include "json/json.h"
#include <fstream>
#include "CBaseEngine.h"

Program* CShaderMgr::getProgram(const String& name){
  if(m_programs.find(name) != m_programs.end()) return m_programs[name];

  engine->log("Loading shader "+name);
  std::ifstream jsonFile(("shaders/"+name+".json").c_str());

  json::mValue data;
  json::read(jsonFile, data);
  jsonFile.close();

  PropertyMgr properties(data);

  GLuint program = glCreateProgram();

  BOOST_FOREACH(modifiers::Value vs, value_cast<modifiers::VectorValue>(properties.getValuePointer("vertex"))){
    glAttachShader(program, loadShader(value_cast<String>(vs), GL_VERTEX_SHADER) );
  }
  BOOST_FOREACH(modifiers::Value vs, value_cast<modifiers::VectorValue>(properties.getValuePointer("fragment"))){
    glAttachShader(program, loadShader(value_cast<String>(vs), GL_FRAGMENT_SHADER) );
  }
  glLinkProgram(program);
  GLint stat;
  glGetProgramiv(program, GL_LINK_STATUS, &stat);
  if(!stat){
    engine->log("glLinkProgram failed");
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &stat);
    char* infoLog = new char[stat];
    glGetProgramInfoLog(program, stat, NULL, infoLog);
    engine->log(std::string(infoLog));
  }
  engine->checkGl("Loading program "+name);
  Program* programObject = new Program(program);
  m_programs[name] = programObject;
  return programObject;
}

GLuint CShaderMgr::loadShader(String fileName, GLuint type){
  if(m_shaders.find(fileName) != m_shaders.end()) return m_shaders[fileName];

  GLuint shader = glCreateShader(type);

  fileName = "shaders/"+fileName;

  std::ifstream shaderFile(fileName.c_str());
  String source;

  shaderFile.seekg(0, std::ios::end);
  source.reserve(shaderFile.tellg());
  shaderFile.seekg(0, std::ios::beg);

  source.assign((std::istreambuf_iterator<char>(shaderFile)), std::istreambuf_iterator<char>());
  shaderFile.close();

  const char* c_source = source.c_str();

  glShaderSource(shader, 1, &c_source, NULL);
  glCompileShader(shader);

  GLint data;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &data);
  if(!data){
    engine->log("glCompileShader failed:");
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &data);
    char* infoLog = new char[data];
    glGetShaderInfoLog(shader, data, NULL, infoLog);
    engine->log(std::string(infoLog));
  }

  engine->checkGl("Loading shader");
  return shader;
}

void CShaderMgr::cleanup(){
  /*BOOST_FOREACH(ProgramMap::value_type& prog, m_programs){
    delete prog.second;
  }
  m_programs.clear();
  BOOST_FOREACH(ShaderMap::value_type& shdr, m_shaders){
    glDeleteShader(shdr.second);
  }
  m_shaders.clear();*/
}
