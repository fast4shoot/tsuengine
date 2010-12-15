#ifndef PLANE_H
#define PLANE_H

#include "vec2d.h"

class Plane{
  public:
    void fromVertices(Vertex a, Vertex b, Vertex c);
  protected:
    vec2d _normal;
    double _d;
  private:
};

#endif // PLANE_H
