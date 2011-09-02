#ifndef RGBA_H
#define RGBA_H

#include "vecBase.h"

class rgba: public vecBase<float,4,rgba>{
  public:
    float& r;
    float& g;
    float& b;
    float& a;
           rgba(const rgba& rhs);
           rgba(float r=0., float g=0., float b=0., float a=0.);
    void   set(float r, float g, float b, float a);

    rgba& operator=(const rgba& rhs);

    static rgba white;
};

inline rgba::rgba(float r, float g, float b, float a):
  r(data[0]),
  g(data[1]),
  b(data[2]),
  a(data[3])
{
  set(r,g,b,a);
}

inline rgba::rgba(const rgba& rhs):
  r(data[0]),
  g(data[1]),
  b(data[2]),
  a(data[3]),
  vecBase<float,4,rgba>(rhs)
{}

inline void rgba::set(float r, float g, float b, float a){
  data[0]=r;
  data[1]=g;
  data[2]=b;
  data[3]=a;
}

inline rgba& rgba::operator=(const rgba& rhs){
  return vecBase<float,4,rgba>::operator=(rhs);
}

#endif // RGBA_H
