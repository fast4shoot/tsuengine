#ifndef MATERIAL_H
#define MATERIAL_H

#include <gl/gl.h>
#include "typedefs.h"

class Material{
  public:

  protected:
    Material(String name);
    virtual ~Material();

    String _name;
    GLuint _glName;

  friend class CMaterialMgr;

};

#endif // MATERIAL_H
