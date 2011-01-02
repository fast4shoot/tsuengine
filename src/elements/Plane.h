#ifndef PLANE_H
#define PLANE_H

#include "vec3d.h"
#include "Vertex.h"

class Plane{
  public:
    void fromVertices(const Vertex& a, const Vertex& b, const Vertex& c);
    vec3d getNormal(){return _normal;}
    double getD(){return _d;}
  protected:
    vec3d _normal;
    double _d;
  private:
};

void Plane::fromVertices(const Vertex& a, const Vertex& b, const Vertex& c){
  _normal = (b.getPosition()-a.getPosition()).cross(c.getPosition()-a.getPosition());
  _normal.normalize();
  _d = -(_normal.dot(a.getPosition()));
}

#endif // PLANE_H
