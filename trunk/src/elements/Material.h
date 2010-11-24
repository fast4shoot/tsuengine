#ifndef MATERIAL_H
#define MATERIAL_H

#include <gl/gl.h>
#include "typedefs.h"

class Material{
  public:
    void bind();
  protected:
    Material(String name);
    virtual ~Material();

    String _name;
    GLuint _glName;

  friend class CMaterialMgr;

};

inline void Material::bind(){
  glBindTexture(GL_TEXTURE_2D,_glName);
}

#endif // MATERIAL_H
