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

enum MOVETYPE{
  NONE,
  LINEAR
};

enum DATATYPE{
  DT_STRING,
  DT_FLOAT,
  DT_INT
};

struct entParam{
  void*         memPointer;
  std::string   name;
  DATATYPE		type;
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
  STATIC,
  DYNAMIC
};

struct StaticVertexData{
  float x, y, z;  //position
  float nx, ny, nz;  //normal
  float u, v; //texture coordinates
};

#endif
