#ifndef VERTEX_H
#define VERTEX_H

#include "vec2d.h"
#include "vec3d.h"

#include "libs/json/json.h"

class Vertex{
  public:
    Vertex(json::mValue& val);
    void addNormal(const vec3d& normal);
    vec3d getPosition() const;
    vec2d getTexCoord() const;
    vec3d getNormal() const;
  protected:
    vec3d m_position;
    vec2d m_texCoord;
    vec3d m_normal;
    int m_normalCnt;
    vec3d m_normalSum;
};

inline Vertex::Vertex(json::mValue& val){
  m_position.fromJson(val.get_obj().find("position")->second);
  m_texCoord.fromJson(val.get_obj().find("texCoord")->second);
}

inline void Vertex::addNormal(const vec3d& normal){
  m_normalSum += normal;
  m_normal = m_normalSum.normalized();
}

inline vec3d Vertex::getPosition() const{
  return m_position;
}

inline vec2d Vertex::getTexCoord() const{
  return m_texCoord;
}

inline vec3d Vertex::getNormal() const{
  return m_normal;
}

#endif // VERTEX_H
