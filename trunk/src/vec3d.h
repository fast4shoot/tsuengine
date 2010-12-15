#ifndef VEC3D_H
#define VEC3D_H

#include "vecOpBase.h"
#include "libs/json/json.h"


class vec3d: public vecOpBase<double,3,vec3d>{
  public:
    double& x;
    double& y;
    double& z;

    vec3d& operator=(const vec3d& rhs);

    vec3d(const vec3d& rhs);
    vec3d(double x=0., double y=0., double z=0.);
    void   set(double x, double y, double z);

    void   fromJson(json::mValue& val);

};

inline vec3d::vec3d(double x, double y, double z):
  x(data[0]),
  y(data[1]),
  z(data[2])
{
  data[0]=x;
  data[1]=y;
  data[2]=z;
}

inline vec3d::vec3d(const vec3d& rhs):
  x(data[0]),
  y(data[1]),
  z(data[2]),
  vecOpBase<double,3,vec3d>(rhs)
{}

inline void vec3d::set(double x, double y, double z){
  data[0]=x;
  data[1]=y;
  data[2]=z;
}

inline void vec3d::fromJson(json::mValue& val){
  json::mObject::iterator it;
  json::mObject& obj=val.get_obj();
  if((it=obj.find("x"))!=obj.end()){
    x = it->second.get_real();
  }
  if((it=obj.find("y"))!=obj.end()){
    y = it->second.get_real();
  }
  if((it=obj.find("z"))!=obj.end()){
    z = it->second.get_real();
  }
}

inline vec3d& vec3d::operator=(const vec3d& rhs){
  return vecBase<double,3,vec3d>::operator=(rhs);
}

/*
inline vec3d& vec3d::operator+=(const vec3d& rhs){
  x+=rhs.x;
  y+=rhs.y;
  z+=rhs.z;
  return *this;
}

inline vec3d& vec3d::operator-=(const vec3d& rhs){
  x-=rhs.x;
  y-=rhs.y;
  z-=rhs.z;
  return *this;
}

inline vec3d& vec3d::operator*=(const double& rhs){
  x*=rhs;
  y*=rhs;
  z*=rhs;
  return *this;
}

inline vec3d& vec3d::operator/=(const double& rhs){
  x/=rhs;
  y/=rhs;
  z/=rhs;
  return *this;
}

inline const vec3d vec3d::operator+(const vec3d& rhs) const {
  return (vec3d(*this) += rhs);
}

inline const vec3d vec3d::operator-(const vec3d& rhs) const {
  return (vec3d(*this) -= rhs);
}

inline const vec3d vec3d::operator*(const double& rhs) const {
  return (vec3d(*this) *= rhs);
}

inline const vec3d vec3d::operator/(const double& rhs) const {
  return (vec3d(*this) /= rhs);
}

inline double vec3d::length() const {
  return sqrt(lengthSqr());
}

inline double vec3d::lengthSqr() const {
  return x*x+y*y+z*z;
}*/
#endif
