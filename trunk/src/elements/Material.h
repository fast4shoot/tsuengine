#ifndef MATERIAL_H
#define MATERIAL_H

#include "GL/glew.h"
#include "typedefs.h"
#include "modifiers/Modifier.h"
class Material{
  public:
    void bind();
    void unbind();
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

    modifiers::Value m_offset;
    modifiers::Value m_rotationCenter;
    modifiers::Value m_rotation;
    modifiers::Value m_scale;
  friend class CMaterialMgr;

};

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
