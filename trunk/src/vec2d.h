#ifndef VEC2D_H
#define VEC2D_H

#include <cmath>
#include "vecOpBase.h"
#include "json/json.h"

class vec2d: public vecOpBase<double,2,vec2d>{
  public:
    double& x;
    double& y;
    double& u;
    double& v;
           vec2d(const vec2d& rhs);
           vec2d(double x=0., double y=0.);
    void   set(double x, double y);

    vec2d& operator=(const vec2d& rhs);

    bool operator>(const vec2d& in) const;
    bool operator<(const vec2d& in) const;
    bool operator==(const vec2d& in) const;
    bool operator>=(const vec2d& in) const;
    bool operator<=(const vec2d& in) const;
};

inline vec2d::vec2d(double x, double y):
  x(data[0]),
  y(data[1]),
  u(data[0]),
  v(data[1])
{
  data[0]=x;
  data[1]=y;
}

inline vec2d::vec2d(const vec2d& rhs):
  x(data[0]),
  y(data[1]),
  u(data[0]),
  v(data[1]),
  vecOpBase<double,2,vec2d>(rhs)
{}

inline void vec2d::set(double x, double y){
  data[0]=x;
  data[1]=y;
}

inline vec2d& vec2d::operator=(const vec2d& rhs){
  return vecBase<double,2,vec2d>::operator=(rhs);
}

inline bool vec2d::operator>(const vec2d& in) const {
  return x>in.x && y>in.y;
}

inline bool vec2d::operator<(const vec2d& in) const {
  return x<in.x && y<in.y;
}

inline bool vec2d::operator==(const vec2d& in) const {
  return x==in.x && y==in.y;
}

inline bool vec2d::operator>=(const vec2d& in) const {
  return operator>(in) || operator==(in);
}

inline bool vec2d::operator<=(const vec2d& in) const {
  return operator<(in) || operator==(in);
}
/*
inline double vec2d::length() const {
  return sqrt(lengthSqr());
}

inline double vec2d::lengthSqr() const {
  return x*x+y*y;
}*/

#endif
