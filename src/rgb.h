#ifndef RGB_H
#define RGB_H

#include "vecBase.h"

class rgb: public vecBase<float,3,rgb>{
  public:
    float& r;
    float& g;
    float& b;
           rgb(const rgb& rhs);
           rgb(float r=0., float g=0., float b=0.);
    void   set(float r, float g, float b);

    rgb& operator=(const rgb& rhs);

};

inline rgb::rgb(float r, float g, float b):
  r(data[0]),
  g(data[1]),
  b(data[2])
{
  set(r,g,b);
}

inline rgb::rgb(const rgb& rhs):
  r(data[0]),
  g(data[1]),
  b(data[2]),
  vecBase<float,3,rgb>(rhs)
{}

inline void rgb::set(float r, float g, float b){
  data[0]=r;
  data[1]=g;
  data[2]=b;
}

inline rgb& rgb::operator=(const rgb& rhs){
  return vecBase<float,3,rgb>::operator=(rhs);
}


#endif // RGB_H
