#ifndef MATERIAL_H
#define MATERIAL_H

#include "glew/glew.h"
#include "typedefs.h"

class Material{
  public:
    void bind();
    bool isPersistent();
    void setPersistent(bool persistent);
    bool getTransparent();
  protected:
    Material(const String& name);
    virtual ~Material();

    String _name;
    GLuint _glName;
    bool m_persistent;
    bool m_transparent;

  friend class CMaterialMgr;

};

inline void Material::bind(){
  glBindTexture(GL_TEXTURE_2D,_glName);
}

inline bool Material::isPersistent(){
  return m_persistent;
}

inline void Material::setPersistent(bool persistent){
  m_persistent = persistent;
}

inline bool Material::getTransparent(){
  return m_transparent;
}
#endif // MATERIAL_H
