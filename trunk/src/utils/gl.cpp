#include "utils/gl.h"
#include "glew/glew.h"
#include "utils/stringUtils.h"
#include <stdexcept>

void checkGl(){
  GLenum err;
  if((err = glGetError())!=GL_NO_ERROR){
    throw std::runtime_error(sformat("GL error %d: %s",err,gluErrorString(err)));
  }
}

