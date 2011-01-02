#ifndef VERTEX_H
#define VERTEX_H

#include "vec2d.h"
#include "vec3d.h"

#include "libs/json/json.h"

class Vertex{
  public:
    void fromJson(json::mValue& val);
    void addNormal(vec3d& normal);
    vec3d getPosition() const;
    vec2d getTexCoord() const;
    vec3d getNormal() const;
  protected:
    vec3d _position;
    vec2d _texCoord;
    vec3d _normal;
    int _normalCnt;
    vec3d _normalSum;
  private:
};

inline void Vertex::fromJson(json::mValue& val){
  _position.fromJson(val.get_obj().find("position")->second);
  _texCoord.fromJson(val.get_obj().find("texCoord")->second);
}

inline void Vertex::addNormal(vec3d& normal){
  _normalSum += normal;
  _normal = _normalSum.normalized();
}

inline vec3d Vertex::getPosition() const{
  return _position;
}

inline vec2d Vertex::getTexCoord() const{
  return _texCoord;
}

inline vec3d Vertex::getNormal() const{
  return _normal;
}

#endif // VERTEX_H
