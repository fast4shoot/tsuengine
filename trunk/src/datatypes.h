#ifndef DATATYPES_H
#define DATATYPES_H

#include <string>
#include "vec2d.h"
#include "vec3d.h"

typedef std::wstring Str;

struct rgb{
  float r;
  float g;
  float b;
};

class rgba{
  public:
    float r;
    float g;
    float b;
    float a;

    rgba();
    rgba(float r, float g, float b, float a);
    void set(float r, float g, float b, float a);
    rgba operator*(float rhs);
};





enum MouseButton{
  LMB =0,
  RMB,
  MMB,
  BUTTON4,
  BUTTON5,
  BUTTON6,
  BUTTON7,
  BUTTON8
};

enum ModelType{
  M_STATIC,
  M_DYNAMIC
};

enum PhysicsType{
  P_NONE,
  P_STATIC,
  P_KINEMATIC,
  P_DYNAMIC
};

struct StaticVertexData{
  float x, y, z;  //position
  float nx, ny, nz;  //normal
  float u, v; //texture coordinates
};

#endif
