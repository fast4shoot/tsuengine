#ifndef VERTEX_H
#define VERTEX_H

#include "vec2d.h"
#include "vec3d.h"

#include "libs/json/json.h"

class Vertex{
  public:
    void fromJson(json::mValue& val);
    void addNormal(vec3d& normal);
  protected:
    vec3d _position;
    vec2d _texCoord;
    vec3d _normal;
    int _normalCnt;
    vec3d _normalSum;
  private:
};

void Vertex::fromJson(json::mValue& val){
  _position.fromJson(val.get_obj().find("position")->second);
  _texCoord.fromJson(val.get_obj().find("texCoord")->second);
}

void Vertex::addNormal(vec3d& normal){
  _normalSum += normal;
  _normal = _normalSum.normalized();
}



#endif // VERTEX_H
